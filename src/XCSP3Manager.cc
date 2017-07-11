/*=============================================================================
 * parser for CSP instances represented in XCSP3 Format
 *
 * Copyright (c) 2015 xcsp.org (contact <at> xcsp.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *=============================================================================*/

#include "XCSP3Manager.h"
#include "XCSP3Variable.h"
#include "XCSP3Constraint.h"
#include "XCSP3Constants.h"
#include "XCSP3Objective.h"
#include <string>
#include <regex>
#include <map>


using namespace XCSP3Core;


bool XCSP3Manager::recognizeXopY(string expr, string &op, XVariable **x, XVariable **y) {
    std::regex const rggt(R"((eq|le|lt|ge|gt|ne)\(([a-zA-Z][a-zA-Z0-Z\[\]]*),([a-zA-Z][a-zA-Z0-Z\[ \]]*)\))");
    std::smatch matchgt;
    if(std::regex_match(expr, matchgt, rggt)) {
        op = matchgt[1];
        *x = (XVariable *) mapping[matchgt[2]];
        *y = (XVariable *) mapping[matchgt[3]];
        return true;
    }
    return false;
}


bool XCSP3Manager::recognizeXopKopY(string expr, string &op, XVariable **x, int &k, XVariable **y) {
    std::regex const rggt(R"((le|eq)\((add|sub)\(([a-zA-Z][a-zA-Z0-Z\[\]]*),([+-]*\d+)\),([a-zA-Z][a-zA-Z0-Z\[ \]]*)\))");
    std::smatch matchgt;
    if(std::regex_match(expr, matchgt, rggt)) {
        op = matchgt[1];
        *x = (XVariable *) mapping[matchgt[3]];
        *y = (XVariable *) mapping[matchgt[5]];
        k = std::stoi(matchgt[4]);
        if(matchgt[2] == "sub") k = -k;
        return true;
    }
    return false;
}


void XCSP3Manager::buildVariable(XVariable *variable) {
    if(discardedClasses(variable->classes))
        return;

    if(variable->domain->values.size() == 1) {
        callback->buildVariableInteger(variable->id, variable->domain->values[0]->minimum(), variable->domain->values[0]->maximum());
        return;
    }
    std::vector<int> values;

    for(unsigned int i = 0; i < variable->domain->values.size(); i++) {
        for(int j = variable->domain->values[i]->minimum();
            j <= variable->domain->values[i]->maximum(); j++) {
            values.push_back(j);
        }
    }
    callback->buildVariableInteger(variable->id, values);
}


void XCSP3Manager::buildVariableArray(XVariableArray *variable) {
    if(discardedClasses(variable->classes))
        return;

    for(XVariable *v : variable->variables)
        if(v != nullptr)
            buildVariable(v);
}

//--------------------------------------------------------------------------------------
// Basic constraints
//--------------------------------------------------------------------------------------


void XCSP3Manager::newConstraintExtension(XConstraintExtension *constraint) {
    if(discardedClasses(constraint->classes))
        return;

    if(constraint->list.size() == 1) {
        std::vector<int> tuples;
        for(vector<int> &tpl : constraint->tuples)
            tuples.push_back(tpl[0]);
        callback->buildConstraintExtension(constraint->id, constraint->list[0], tuples, constraint->isSupport,
                                           constraint->containsStar);
    } else
        callback->buildConstraintExtension(constraint->id, constraint->list, constraint->tuples,
                                           constraint->isSupport, constraint->containsStar);
}


void XCSP3Manager::newConstraintExtensionAsLastOne(XConstraintExtension *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    callback->buildConstraintExtensionAs(constraint->id, constraint->list,
                                         constraint->isSupport, constraint->containsStar);
}


void XCSP3Manager::newConstraintIntension(XConstraintIntension *constraint) {
    XVariable *x = NULL, *y = NULL;
    string op = "";
    int k;
    OrderType order;
    if(discardedClasses(constraint->classes))
        return;
    if(callback->recognizeSpecialIntensionCases) {
        if(recognizeXopY(constraint->function, op, &x, &y)) { // Recognize x op y
            if(op == "eq") order = OrderType::EQ;
            if(op == "ne") order = NE;
            if(op == "le") order = LE;
            if(op == "lt") order = LT;
            if(op == "ge") order = GE;
            if(op == "gt") order = GT;
            callback->buildConstraintPrimitive(constraint->id, order, x, 0, y);
            return;
        }
        if(recognizeXopKopY(constraint->function, op, &x, k, &y)) { // Recognize x +-k op y
            if(op == "eq") order = OrderType::EQ;
            if(op == "ne") order = NE;
            if(op == "le") order = LE;
            if(op == "lt") order = LT;
            if(op == "ge") order = GE;
            if(op == "gt") order = GT;

            callback->buildConstraintPrimitive(constraint->id, order, x, k, y);
            return;
        }
    }
    callback->buildConstraintIntension(constraint->id, constraint->function);
}

//--------------------------------------------------------------------------------------
// Languages constraints
//--------------------------------------------------------------------------------------


void XCSP3Manager::newConstraintRegular(XConstraintRegular *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    callback->buildConstraintRegular(constraint->id, constraint->list, constraint->start, constraint->final,
                                     constraint->transitions);
}


void XCSP3Manager::newConstraintMDD(XConstraintMDD *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    callback->buildConstraintMDD(constraint->id, constraint->list, constraint->transitions);
}

//--------------------------------------------------------------------------------------
// Comparison constraints
//--------------------------------------------------------------------------------------

void XCSP3Manager::newConstraintAllDiff(XConstraintAllDiff *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    if(constraint->except.size() == 0)
        callback->buildConstraintAlldifferent(constraint->id, constraint->list);
    else
        callback->buildConstraintAlldifferentExcept(constraint->id, constraint->list, constraint->except);
}


void XCSP3Manager::newConstraintAllDiffMatrix(XConstraintAllDiffMatrix *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    callback->buildConstraintAlldifferentMatrix(constraint->id, constraint->matrix);
}


void XCSP3Manager::newConstraintAllDiffList(XConstraintAllDiffList *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    callback->buildConstraintAlldifferentList(constraint->id, constraint->matrix);
}


void XCSP3Manager::newConstraintAllEqual(XConstraintAllEqual *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    callback->buildConstraintAllEqual(constraint->id, constraint->list);
}


void XCSP3Manager::newConstraintOrdered(XConstraintOrdered *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    callback->buildConstraintOrdered(constraint->id, constraint->list, constraint->op);
}


void XCSP3Manager::newConstraintLex(XConstraintLex *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    callback->buildConstraintLex(constraint->id, constraint->lists, constraint->op);
}


void XCSP3Manager::newConstraintLexMatrix(XConstraintLexMatrix *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    callback->buildConstraintLexMatrix(constraint->id, constraint->matrix, constraint->op);
}


//--------------------------------------------------------------------------------------
// Summin and Counting constraints
//--------------------------------------------------------------------------------------

void XCSP3Manager::normalizeSum(vector<XVariable *> &list, vector<int> &coefs) {
    // merge
    for(unsigned  int i = 0; i < list.size() - 1; i++) {
        if(coefs[i] == 0) continue;
        for(auto j = i + 1; j < list.size(); j++) {
            if(coefs[j] != 0 && list[i]->id == list[j]->id) {
                coefs[i] += coefs[j];
                coefs[j] = 0;
            }
        }
    }
    vector<int> tmpc;
    vector<XVariable *> tmpv;
    // remove coef=0
    for(unsigned int i = 0; i < list.size(); i++)
        if(coefs[i] != 0) {
            tmpv.push_back(list[i]);
            tmpc.push_back(coefs[i]);
        }

    list.clear();
    list.assign(tmpv.begin(), tmpv.end());
    coefs.clear();
    coefs.assign(tmpc.begin(), tmpc.end());
}


void XCSP3Manager::newConstraintSum(XConstraintSum *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    XCondition xc;
    constraint->extractCondition(xc);
    if(constraint->values.size() == 0) {
        bool toModify = false;
        if(callback->normalizeSum) {
            // Check if a variable appears two times
            for(unsigned  int i = 0; i < constraint->list.size() - 1; i++)
                for(auto j = i + 1; j < constraint->list.size(); j++) {
                    if(constraint->list[i]->id == constraint->list[j]->id)
                        toModify = true;
                }
            if(toModify)
                constraint->values.assign(constraint->list.size(), new XInteger("", 1));
        }
        if(!toModify) {
            callback->buildConstraintSum(constraint->id, constraint->list, xc);
            return;
        }
    }

    int v;
    if(isInteger(constraint->values[0], v)) {
        vector<int> coefs;
        vector<XVariable *> list;
        for(XEntity *xe : constraint->values) {
            isInteger(xe, v);
            coefs.push_back(v);
        }
        list.assign(constraint->list.begin(), constraint->list.end());

        if(callback->normalizeSum)
            normalizeSum(list, coefs);

        callback->buildConstraintSum(constraint->id, list, coefs, xc);
        return;
    }

    std::vector<XVariable *> xvalues;
    for(XEntity *xe : constraint->values) {
        xvalues.push_back((XVariable *) mapping[xe->id]);
    }
    callback->buildConstraintSum(constraint->id, constraint->list, xvalues, xc);
}


void XCSP3Manager::newConstraintCount(XConstraintCount *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    int value;
    XCondition xc;
    constraint->extractCondition(xc);
    std::vector<int> values;


    // One integer value
    // Special cases AtLeastK, ATMostK, ..
    if(callback->recognizeSpecialCountCases && constraint->values.size() == 1 && isInteger(constraint->values[0], value)) {
        if(xc.operandType == INTEGER && xc.op == OrderType::LE) {
            callback->buildConstraintAtMost(constraint->id, constraint->list, value, xc.val);
            return;
        }
        if(xc.operandType == INTEGER && xc.op == OrderType::LT) {
            callback->buildConstraintAtMost(constraint->id, constraint->list, value, xc.val - 1);
            return;
        }
        if(xc.operandType == INTEGER && xc.op == OrderType::GE) {
            callback->buildConstraintAtLeast(constraint->id, constraint->list, value, xc.val);
            return;
        }
        if(xc.operandType == INTEGER && xc.op == OrderType::LT) {
            callback->buildConstraintAtLeast(constraint->id, constraint->list, value, xc.val + 1);
            return;
        }
        if(xc.operandType == INTEGER && xc.op == OrderType::EQ) {
            callback->buildConstraintExactlyK(constraint->id, constraint->list, value, xc.val);
            return;
        }
        if(xc.operandType == VARIABLE && xc.op == OrderType::EQ) {
            callback->buildConstraintExactlyVariable(constraint->id, constraint->list, value, (XVariable *) mapping[xc.var]);
            return;
        }
    }

    // Among
    if(callback->recognizeSpecialCountCases && xc.op == OrderType::EQ && xc.operandType == INTEGER &&
       isInteger(constraint->values[0], value)) {
        for(XEntity *xe : constraint->values) {
            isInteger(xe, value);
            values.push_back(value);
        }
        callback->buildConstraintAmong(constraint->id, constraint->list, values, xc.val);
        return;
    }


    if(isInteger(constraint->values[0], value)) {
        // Iterate and get integers
        for(XEntity *xe : constraint->values) {
            isInteger(xe, value);
            values.push_back(value);
        }
        callback->buildConstraintCount(constraint->id, constraint->list, values, xc);
    } else {
        std::vector<XVariable *> values;
        for(XEntity *xe : constraint->values) {
            values.push_back((XVariable *) mapping[xe->id]);
        }
        callback->buildConstraintCount(constraint->id, constraint->list, values, xc);
    }
}


void XCSP3Manager::newConstraintNValues(XConstraintNValues *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    XCondition xc;
    constraint->extractCondition(xc);

    // Special NotAllEqual case
    if(callback->recognizeNValuesCases && xc.operandType == INTEGER && constraint->except.size() == 0
       && ((xc.op == GE && xc.val == 2) || (xc.op == GT && xc.val == 1))) {
        callback->buildConstraintNotAllEqual(constraint->id, constraint->list);
        return;
    }

    // Special AllEqual case
    if(callback->recognizeNValuesCases && xc.operandType == INTEGER &&
       constraint->except.size() == 0 && (xc.op == OrderType::EQ && xc.val == 1)) {
        callback->buildConstraintAllEqual(constraint->id, constraint->list);
        return;
    }

    // Special AllDiff case
    if(callback->recognizeNValuesCases && xc.operandType == INTEGER && constraint->except.size() == 0
       && (xc.op == OrderType::EQ && ((unsigned int) xc.val) == constraint->list.size())) {
        callback->buildConstraintAlldifferent(constraint->id, constraint->list);
        return;
    }

    if(constraint->except.size() == 0) {
        callback->buildConstraintNValues(constraint->id, constraint->list, xc);
        return;
    }
    callback->buildConstraintNValues(constraint->id, constraint->list, constraint->except, xc);
}


void XCSP3Manager::newConstraintCardinality(XConstraintCardinality *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    std::vector<int> intValues;
    std::vector<XVariable *> varValues;
    int v;
    for(XEntity *xe : constraint->values) {
        if(isInteger(xe, v))
            intValues.push_back(v);
        else {
            XVariable *xv = (XVariable *) xe;
            varValues.push_back(xv);
        }
    }

    std::vector<int> intOccurs;
    std::vector<XVariable *> varOccurs;
    std::vector<XInterval> intervalOccurs;

    for(XEntity *xe : constraint->occurs) {
        if(isInteger(xe, v))
            intOccurs.push_back(v);
        else {
            int min, max;
            if(isInterval(xe, min, max))
                intervalOccurs.push_back(XInterval(min, max));
            else {
                XVariable *xv = (XVariable *) xe;
                varOccurs.push_back(xv);
            }
        }
    }

    if(intValues.size() > 0 && intOccurs.size() > 0) {
        callback->buildConstraintCardinality(constraint->id, constraint->list, intValues, intOccurs, constraint->closed);
        return;
    }
    if(intValues.size() > 0 && varOccurs.size() > 0) {
        callback->buildConstraintCardinality(constraint->id, constraint->list, intValues, varOccurs, constraint->closed);
        return;
    }
    if(intValues.size() > 0 && intervalOccurs.size() > 0) {
        callback->buildConstraintCardinality(constraint->id, constraint->list, intValues, intervalOccurs, constraint->closed);
        return;
    }
    if(varValues.size() > 0 && intOccurs.size() > 0) {
        callback->buildConstraintCardinality(constraint->id, constraint->list, varValues, intOccurs, constraint->closed);
        return;
    }
    if(varValues.size() > 0 && varOccurs.size() > 0) {
        callback->buildConstraintCardinality(constraint->id, constraint->list, varValues, varOccurs, constraint->closed);
        return;
    }
    if(varValues.size() > 0 && intervalOccurs.size() > 0) {
        callback->buildConstraintCardinality(constraint->id, constraint->list, varValues, intervalOccurs, constraint->closed);
        return;
    }
}


//--------------------------------------------------------------------------------------
// Connection constraints
//--------------------------------------------------------------------------------------


void XCSP3Manager::newConstraintMinimum(XConstraintMinimum *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    XCondition xc;
    constraint->extractCondition(xc);

    if(constraint->index == NULL) {
        callback->buildConstraintMinimum(constraint->id, constraint->list, xc);
        return;
    }
    callback->buildConstraintMinimum(constraint->id, constraint->list, constraint->index, constraint->startIndex, constraint->rank, xc);
}


void XCSP3Manager::newConstraintMaximum(XConstraintMaximum *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    XCondition xc;
    constraint->extractCondition(xc);

    if(constraint->index == NULL) {
        callback->buildConstraintMaximum(constraint->id, constraint->list, xc);
        return;
    }
    callback->buildConstraintMaximum(constraint->id, constraint->list, constraint->index, constraint->startIndex, constraint->rank, xc);
}


void XCSP3Manager::newConstraintElement(XConstraintElement *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    int v;
    vector<int> listOfIntegers;
    if(isInteger(constraint->list[0], v)) {
        for(XEntity *xe : constraint->list) {
            isInteger(xe, v);
            listOfIntegers.push_back(v);
        }
    }


    if(isInteger(constraint->value, v)) {
        if(constraint->index == NULL) {
            if(listOfIntegers.size() > 0)
                throw runtime_error("Not yet supported");
            else
                callback->buildConstraintElement(constraint->id, constraint->list, v);
        } else {
            if(listOfIntegers.size() > 0)
                throw runtime_error("Not yet supported");
            else
                callback->buildConstraintElement(constraint->id, constraint->list, constraint->startIndex, constraint->index, constraint->rank, v);
        }
        return;
    }
    // Is variable
    XVariable *xv = (XVariable *) constraint->value;
    if(constraint->index == NULL) {
        if(listOfIntegers.size() > 0)
            throw runtime_error("Not yet supported");
        else
            callback->buildConstraintElement(constraint->id, constraint->list, xv);
    } else {
        if(listOfIntegers.size() > 0)
            callback->buildConstraintElement(constraint->id, listOfIntegers, constraint->startIndex, constraint->index, constraint->rank, xv);
        else
            callback->buildConstraintElement(constraint->id, constraint->list, constraint->startIndex, constraint->index, constraint->rank, xv);
    }
}


void XCSP3Manager::newConstraintChannel(XConstraintChannel *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    if(constraint->secondList.size() == 0 && constraint->value == NULL) {
        callback->buildConstraintChannel(constraint->id, constraint->list, constraint->startIndex1);
        return;
    }

    if(constraint->secondList.size() > 0 && constraint->value == NULL) {
        callback->buildConstraintChannel(constraint->id, constraint->list, constraint->startIndex1, constraint->secondList,
                                         constraint->startIndex2);
        return;
    }
    callback->buildConstraintChannel(constraint->id, constraint->list, constraint->startIndex1, constraint->value);
}

//--------------------------------------------------------------------------------------
// packing and scheduling constraints
//--------------------------------------------------------------------------------------

void XCSP3Manager::newConstraintStretch(XConstraintStretch *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    if(constraint->patterns.size() == 0)
        callback->buildConstraintStretch(constraint->id, constraint->list, constraint->values, constraint->widths);
    else
        callback->buildConstraintStretch(constraint->id, constraint->list, constraint->values, constraint->widths, constraint->patterns);
}


void XCSP3Manager::newConstraintNoOverlap(XConstraintNoOverlap *constraint) {
    if(discardedClasses(constraint->classes))
        return;

    if(constraint->origins[0] == NULL) {
        newConstraintNoOverlapKDim(constraint);
        return;
    }

    int v;
    vector<int> intLengths;
    vector<XVariable *> varLengths;

    for(XEntity *xe : constraint->lengths) {
        if(isInteger(xe, v))
            intLengths.push_back(v);
        else {
            XVariable *xv = (XVariable *) xe;
            varLengths.push_back(xv);
        }
    }

    if(intLengths.size() > 0)
        callback->buildConstraintNoOverlap(constraint->id, constraint->origins, intLengths, constraint->zeroIgnored);
    else
        callback->buildConstraintNoOverlap(constraint->id, constraint->origins, varLengths, constraint->zeroIgnored);
}


void XCSP3Manager::newConstraintNoOverlapKDim(XConstraintNoOverlap *constraint) {
    if(discardedClasses(constraint->classes))
        return;

    int v;
    bool isInt = false;
    vector<vector<int>> intLengths;
    vector<vector<XVariable *>> varLengths;
    vector<vector<XVariable *>> origins;
    for(XEntity *xe : constraint->lengths) {
        if(xe == NULL) {
            varLengths.push_back(vector<XVariable *>());
            intLengths.push_back(vector<int>());
            continue;
        }
        if(isInteger(xe, v)) {
            intLengths.back().push_back(v);
            isInt = true;
        } else {
            XVariable *xv = (XVariable *) xe;
            varLengths.back().push_back(xv);
        }
    }
    for(XVariable *xe : constraint->origins) {
        if(xe == NULL) {
            origins.push_back(vector<XVariable *>());
            continue;
        }
        origins.back().push_back(xe);
    }


    if(isInt > 0)
        callback->buildConstraintNoOverlap(constraint->id, origins, intLengths, constraint->zeroIgnored);
    else
        callback->buildConstraintNoOverlap(constraint->id, origins, varLengths, constraint->zeroIgnored);
}


void XCSP3Manager::newConstraintCumulative(XConstraintCumulative *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    int v;
    vector<int> intLengths;
    vector<XVariable *> varLengths;

    for(XEntity *xe : constraint->lengths) {
        if(isInteger(xe, v))
            intLengths.push_back(v);
        else {
            XVariable *xv = (XVariable *) xe;
            varLengths.push_back(xv);
        }
    }

    vector<int> intHeights;
    vector<XVariable *> varHeights;

    for(XEntity *xe : constraint->heights) {
        if(isInteger(xe, v))
            intHeights.push_back(v);
        else {
            XVariable *xv = (XVariable *) xe;
            varHeights.push_back(xv);
        }
    }
    XCondition xc;
    constraint->extractCondition(xc);

    if(constraint->ends.size() == 0) {
        if(intLengths.size() > 0 && intHeights.size() > 0)
            callback->buildConstraintCumulative(constraint->id, constraint->origins, intLengths, intHeights, xc);
        if(intLengths.size() > 0 && varHeights.size() > 0)
            callback->buildConstraintCumulative(constraint->id, constraint->origins, intLengths, varHeights, xc);
        if(varLengths.size() > 0 && intHeights.size() > 0)
            callback->buildConstraintCumulative(constraint->id, constraint->origins, varLengths, intHeights, xc);
        if(varLengths.size() > 0 && varHeights.size() > 0)
            callback->buildConstraintCumulative(constraint->id, constraint->origins, varLengths, varHeights, xc);
        return;
    }
    if(intLengths.size() > 0 && intHeights.size() > 0)
        callback->buildConstraintCumulative(constraint->id, constraint->origins, intLengths, intHeights, constraint->ends, xc);
    if(intLengths.size() > 0 && varHeights.size() > 0)
        callback->buildConstraintCumulative(constraint->id, constraint->origins, intLengths, varHeights, constraint->ends, xc);
    if(varLengths.size() > 0 && intHeights.size() > 0)
        callback->buildConstraintCumulative(constraint->id, constraint->origins, varLengths, intHeights, constraint->ends, xc);
    if(varLengths.size() > 0 && varHeights.size() > 0)
        callback->buildConstraintCumulative(constraint->id, constraint->origins, varLengths, varHeights, constraint->ends, xc);
}

//--------------------------------------------------------------------------------------
// Instantiation  constraint
//--------------------------------------------------------------------------------------

void XCSP3Manager::newConstraintInstantiation(XConstraintInstantiation *constraint) {
    if(discardedClasses(constraint->classes))
        return;
    callback->buildConstraintInstantiation(constraint->id, constraint->list, constraint->values);
}


//--------------------------------------------------------------------------------------
// Graph  constraints
//--------------------------------------------------------------------------------------

void XCSP3Manager::newConstraintCircuit(XConstraintCircuit *constraint) {
    if(discardedClasses(constraint->classes))
        return;

    if(constraint->value== nullptr)
        callback->buildConstraintCircuit(constraint->id, constraint->list, constraint->startIndex);
    else {
        int value;
        if(isInteger(constraint->value, value))
            callback->buildConstraintCircuit(constraint->id, constraint->list, constraint->startIndex, value);
        else
            callback->buildConstraintCircuit(constraint->id, constraint->list, constraint->startIndex, (XVariable *)constraint->value);
    }

}


//--------------------------------------------------------------------------------------
// group constraints
//--------------------------------------------------------------------------------------


template<class T>
void XCSP3Manager::unfoldConstraint(XConstraintGroup *group, int i, void (XCSP3Manager::*newConstraint)(T *)) {
    T *constraint = new T(group->constraint->id, group->constraint->classes);
    group->unfoldArgumentNumber(i, constraint);
    (this->*newConstraint)(constraint);
    delete constraint;
}


void XCSP3Manager::newConstraintGroup(XConstraintGroup *group) {
    if(discardedClasses(group->classes))
        return;

    vector<XVariable *> previousArguments; // Used to check if extension arguments have same domains
    for(unsigned int i = 0; i < group->arguments.size(); i++) {
        if(group->type == INTENSION)
            unfoldConstraint<XConstraintIntension>(group, i, &XCSP3Manager::newConstraintIntension);
        if(group->type == EXTENSION) {
            XConstraintExtension *ce = new XConstraintExtension(group->constraint->id, group->constraint->classes);
            group->unfoldArgumentNumber(i, ce);

            if(i > 0) {
                // Check previous arguments
                bool same = true;
                for(unsigned int j = 0; j < previousArguments.size(); j++)
                    if(previousArguments[j]->domain->equals(ce->list[j]->domain) == false) {
                        same = false;
                        break;
                    }
                if(same == false)
                    previousArguments.clear();
            }


            if(i > 0 && previousArguments.size() > 0)
                newConstraintExtensionAsLastOne(ce);
            else {
                vector<XVariable *> list;
                list.assign(group->constraint->list.begin(), group->constraint->list.end());
                group->constraint->list.assign(ce->list.begin(), ce->list.end());
                previousArguments.assign(ce->list.begin(), ce->list.end());
                newConstraintExtension((XConstraintExtension *) group->constraint);
                group->constraint->list.assign(list.begin(), list.end());
            }
            delete ce;
        }

        if(group->type == INSTANTIATION)
            unfoldConstraint<XConstraintInstantiation>(group, i, &XCSP3Manager::newConstraintInstantiation);
        if(group->type == ALLDIFF)
            unfoldConstraint<XConstraintAllDiff>(group, i, &XCSP3Manager::newConstraintAllDiff);
        if(group->type == ALLEQUAL)
            unfoldConstraint<XConstraintAllEqual>(group, i, &XCSP3Manager::newConstraintAllEqual);
        if(group->type == SUM)
            unfoldConstraint<XConstraintSum>(group, i, &XCSP3Manager::newConstraintSum);
        if(group->type == ORDERED)
            unfoldConstraint<XConstraintOrdered>(group, i, &XCSP3Manager::newConstraintOrdered);
        if(group->type == COUNT)
            unfoldConstraint<XConstraintCount>(group, i, &XCSP3Manager::newConstraintCount);
        if(group->type == NVALUES)
            unfoldConstraint<XConstraintNValues>(group, i, &XCSP3Manager::newConstraintNValues);
        if(group->type == CARDINALITY)
            unfoldConstraint<XConstraintCardinality>(group, i, &XCSP3Manager::newConstraintCardinality);
        if(group->type == MAXIMUM)
            unfoldConstraint<XConstraintMaximum>(group, i, &XCSP3Manager::newConstraintMaximum);
        if(group->type == MINIMUM)
            unfoldConstraint<XConstraintMinimum>(group, i, &XCSP3Manager::newConstraintMinimum);
        if(group->type == ELEMENT)
            unfoldConstraint<XConstraintElement>(group, i, &XCSP3Manager::newConstraintElement);
        if(group->type == NOOVERLAP)
            unfoldConstraint<XConstraintNoOverlap>(group, i, &XCSP3Manager::newConstraintNoOverlap);
        if(group->type == STRETCH)
            unfoldConstraint<XConstraintStretch>(group, i, &XCSP3Manager::newConstraintStretch);
        if(group->type == LEX)
            unfoldConstraint<XConstraintLex>(group, i, &XCSP3Manager::newConstraintLex);
        if(group->type == CHANNEL)
            unfoldConstraint<XConstraintChannel>(group, i, &XCSP3Manager::newConstraintChannel);
        if(group->type == REGULAR)
            unfoldConstraint<XConstraintRegular>(group, i, &XCSP3Manager::newConstraintRegular);
        if(group->type == MDD)
            unfoldConstraint<XConstraintMDD>(group, i, &XCSP3Manager::newConstraintMDD);
        if(group->type == CIRCUIT)
            unfoldConstraint<XConstraintCircuit>(group, i, &XCSP3Manager::newConstraintCircuit);
        if(group->type == CUMULATIVE)
            unfoldConstraint<XConstraintCumulative>(group, i, &XCSP3Manager::newConstraintCumulative);

        if(group->type == UNKNOWN) {
            throw runtime_error("Group constraint is badly defined");
        }
    }
}


void XCSP3Manager::addObjective(XObjective *objective) {
    if(objective->type == EXPRESSION_O) {
        XVariable *x = (XVariable *) mapping[objective->expression];
        if(x != NULL) {
            if(objective->goal == MINIMIZE)
                callback->buildObjectiveMinimizeVariable(x);
            else
                callback->buildObjectiveMaximizeVariable(x);
            return;
        }
        if(objective->goal == MINIMIZE)
            callback->buildObjectiveMinimizeExpression(objective->expression);
        else
            callback->buildObjectiveMaximizeExpression(objective->expression);
        return;
    }
    if(objective->type == SUM_O && callback->normalizeSum) {
        if(objective->coeffs.size() == 0) {
            bool toModify = false;
            // Check if a variable appears two times
            for(unsigned int i = 0; i < objective->list.size() - 1; i++)
                for(auto j = i + 1; j < objective->list.size(); j++) {
                    if(objective->list[i]->id == objective->list[j]->id)
                        toModify = true;
                }
            if(toModify)
                objective->coeffs.assign(objective->list.size(), 1);
        }
        if(objective->coeffs.size() > 0)
            normalizeSum(objective->list, objective->coeffs);
    }

    if(objective->coeffs.size() == 0) {
        if(objective->goal == MINIMIZE)
            callback->buildObjectiveMinimize(objective->type, objective->list);
        else
            callback->buildObjectiveMaximize(objective->type, objective->list);
        return;
    }
    if(objective->goal == MINIMIZE)
        callback->buildObjectiveMinimize(objective->type, objective->list, objective->coeffs);
    else
        callback->buildObjectiveMaximize(objective->type, objective->list, objective->coeffs);

}



