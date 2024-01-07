/*=============================================================================
 * parser for CSP instances represented in XCSP3 Format
 *
 * Copyright (c) 2015 xcsp.org (contact <at> xcsp.org)
 * Copyright (c) 2008 Olivier ROUSSEL (olivier.roussel <at> cril.univ-artois.fr)
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
 *=============================================================================
 */
#ifndef COSOCO_XCSP3PRINTCALLBACKS_H
#define COSOCO_XCSP3PRINTCALLBACKS_H

#include <XCSP3Tree.h>
#include "XCSP3CoreCallbacks.h"
#include "XCSP3Variable.h"
/**
 * This is an example that prints useful informations of a XCSP3 instance.
 * You need to create your own class and to override functions of the callback.
 * We suggest to make a map between XVariable and your own variables in order to
 * facilitate the constructions of constraints.
 *
 * see main.cc to show declaration of the parser
 *
 */

namespace XCSP3Core {

    class XCSP3PrintCallbacks : public XCSP3CoreCallbacks {
    public:
        XCSP3PrintCallbacks();

        void beginInstance(InstanceType type) override;

        void endInstance() override;

        void beginVariables() override;

        void endVariables() override;

        void beginVariableArray(string id) override;

        void endVariableArray() override;

        void beginConstraints() override;

        void endConstraints() override;

        void beginGroup(string id) override;

        void endGroup() override;

        void beginBlock(string classes) override;

        void endBlock() override;

        void beginSlide(string id, bool circular) override;

        void endSlide() override;

        void beginObjectives() override;

        void endObjectives() override;

        void beginAnnotations() override;

        void endAnnotations() override;

        void buildVariableInteger(string id, int minValue, int maxValue) override;

        void buildVariableInteger(string id, vector<int> &values) override;

        void buildConstraintExtension(string id, vector<XVariable *> list, vector<vector<int>> &tuples, bool support, bool hasStar) override;

        void buildConstraintExtension(string id, XVariable *variable, vector<int> &tuples, bool support, bool hasStar) override;

        void buildConstraintExtensionAs(string id, vector<XVariable *> list, bool support, bool hasStar) override;

        void buildConstraintIntension(string id, string expr) override;

        void buildConstraintIntension(string id, Tree *tree) override;

        void buildConstraintPrimitive(string id, OrderType op, XVariable *x, int k, XVariable *y) override;

        void buildConstraintPrimitive(string id, OrderType op, XVariable *x, int k) override;

        void buildConstraintPrimitive(string id, XVariable *x,  bool in, int min, int max) override;

        void buildConstraintRegular(string id, vector<XVariable *> &list, string st, vector<string> &final, vector<XTransition> &transitions) override;

        void buildConstraintMDD(string id, vector<XVariable *> &list, vector<XTransition> &transitions) override;

        void buildConstraintAlldifferent(string id, vector<XVariable *> &list) override;

        void buildConstraintAlldifferentExcept(string id, vector<XVariable *> &list, vector<int> &except) override;

        void buildConstraintAlldifferent(string id, vector<Tree *> &list) override;

        void buildConstraintAlldifferentList(string id, vector<vector<XVariable *>> &lists) override;

        void buildConstraintAlldifferentMatrix(string id, vector<vector<XVariable *>> &matrix) override;

        void buildConstraintAllEqual(string id, vector<XVariable *> &list) override;

        void buildConstraintNotAllEqual(string id, vector<XVariable *> &list) override;

        void buildConstraintOrdered(string id, vector<XVariable *> &list, OrderType order) override;

        void buildConstraintOrdered(string id, vector<XVariable *> &list, vector<int> &lengths, OrderType order) override;

        void buildConstraintLex(string id, vector<vector<XVariable *>> &lists, OrderType order) override;

        void buildConstraintLexMatrix(string id, vector<vector<XVariable *>> &matrix, OrderType order) override;

        void buildConstraintSum(string id, vector<XVariable *> &list, vector<int> &coeffs, XCondition &cond) override;

        void buildConstraintSum(string id, vector<XVariable *> &list, XCondition &cond) override;

        void buildConstraintSum(string id, vector<XVariable *> &list, vector<XVariable *> &coeffs, XCondition &cond) override;

        void buildConstraintSum(string id, vector<Tree *> &list, vector<int> &coeffs, XCondition &cond) override;

        void buildConstraintSum(string id, vector<Tree *> &list, XCondition &cond) override;

        void buildConstraintAtMost(string id, vector<XVariable *> &list, int value, int k) override;

        void buildConstraintAtLeast(string id, vector<XVariable *> &list, int value, int k) override;

        void buildConstraintExactlyK(string id, vector<XVariable *> &list, int value, int k) override;

        void buildConstraintAmong(string id, vector<XVariable *> &list, vector<int> &values, int k) override;

        void buildConstraintExactlyVariable(string id, vector<XVariable *> &list, int value, XVariable *x) override;

        void buildConstraintCount(string id, vector<XVariable *> &list, vector<int> &values, XCondition &xc) override;

        void buildConstraintCount(string id, vector<XVariable *> &list, vector<XVariable *> &values, XCondition &xc) override;

        void buildConstraintNValues(string id, vector<XVariable *> &list, vector<int> &except, XCondition &xc) override;

        void buildConstraintNValues(string id, vector<XVariable *> &list, XCondition &xc) override;

        void buildConstraintCardinality(string id, vector<XVariable *> &list, vector<int> values, vector<int> &occurs, bool closed) override;

        void buildConstraintCardinality(string id, vector<XVariable *> &list, vector<int> values, vector<XVariable *> &occurs,
                                                bool closed) override;

        void buildConstraintCardinality(string id, vector<XVariable *> &list, vector<int> values, vector<XInterval> &occurs,
                                                bool closed) override;

        void buildConstraintCardinality(string id, vector<XVariable *> &list, vector<XVariable *> values, vector<int> &occurs,
                                                bool closed) override;

        void buildConstraintCardinality(string id, vector<XVariable *> &list, vector<XVariable *> values, vector<XVariable *> &occurs,
                                                bool closed) override;

        void buildConstraintCardinality(string id, vector<XVariable *> &list, vector<XVariable *> values, vector<XInterval> &occurs,
                                                bool closed) override;

        void buildConstraintMinimum(string id, vector<XVariable *> &list, XCondition &xc) override;

        void buildConstraintMinimum(string id, vector<XVariable *> &list, XVariable *index, int startIndex, RankType rank,
                                            XCondition &xc) override;

        void buildConstraintMaximum(string id, vector<XVariable *> &list, XCondition &xc) override;

        void buildConstraintMaximum(string id, vector<Tree *> &list, XCondition &xc) override;

        void buildConstraintMaximum(string id, vector<XVariable *> &list, XVariable *index, int startIndex, RankType rank,
                                            XCondition &xc) override;

        void buildConstraintElement(string id, vector<XVariable *> &list, int value) override;

        void buildConstraintElement(string id, vector<XVariable *> &list, XVariable *value) override;

        void buildConstraintElement(string id, vector<XVariable *> &list, int startIndex, XVariable *index, RankType rank, int value) override;

        void buildConstraintElement(string id, vector<XVariable *> &list, int startIndex, XVariable *index, RankType rank, XVariable *value) override;

        void buildConstraintElement(string id, vector<int> &list, int startIndex, XVariable *index, RankType rank, XVariable *value) override;

        void buildConstraintElement(string id, vector<vector<int> > &matrix, int startRowIndex, XVariable *rowIndex, int startColIndex, XVariable* colIndex, XVariable *value) override;

        void buildConstraintElement(string id, vector<XVariable *> &list, XVariable *index, int startIndex, XCondition &xc)  override;

        void buildConstraintChannel(string id, vector<XVariable *> &list, int startIndex) override;

        void buildConstraintChannel(string id, vector<XVariable *> &list1, int startIndex1, vector<XVariable *> &list2, int startIndex2) override;

        void buildConstraintChannel(string id, vector<XVariable *> &list, int startIndex, XVariable *value) override;

        void buildConstraintStretch(string id, vector<XVariable *> &list, vector<int> &values, vector<XInterval> &widths) override;

        void
        buildConstraintStretch(string id, vector<XVariable *> &list, vector<int> &values, vector<XInterval> &widths, vector<vector<int>> &patterns) override;

        void buildConstraintNoOverlap(string id, vector<XVariable *> &origins, vector<int> &lengths, bool zeroIgnored) override;

        void buildConstraintNoOverlap(string id, vector<XVariable *> &origins, vector<XVariable *> &lengths, bool zeroIgnored) override;

        void buildConstraintNoOverlap(string id, vector<vector<XVariable *>> &origins, vector<vector<int>> &lengths, bool zeroIgnored) override;

        void buildConstraintNoOverlap(string id, vector<vector<XVariable *>> &origins, vector<vector<XVariable *>> &lengths, bool zeroIgnored) override;

        void buildConstraintInstantiation(string id, vector<XVariable *> &list, vector<int> &values) override;

        void buildConstraintClause(string id, vector<XVariable *> &positive, vector<XVariable *> &negative) override ;

        void buildConstraintCircuit(string id, vector<XVariable *> &list, int startIndex) override;


        void buildConstraintCircuit(string id, vector<XVariable *> &list, int startIndex, int size) override;


        void buildConstraintCircuit(string id, vector<XVariable *> &list, int startIndex, XVariable *size) override;

        void buildConstraintPrecedence(string id, vector<XVariable *> &list, vector<int> values, bool covered) override;

        void buildConstraintBinPacking(string id, vector<XVariable *> &list, vector<int> &sizes, XCondition &cond) override;

        void buildConstraintFlow(string id, vector<XVariable *> &list, vector<int> &balance, vector<int> &weights, vector<vector<int> > &arcs, XCondition &xc) override;

        void buildConstraintKnapsack(string id, vector<XVariable *> &list, vector<int> &weights, vector<int> &profits,XCondition weightsCondition, XCondition &profitCondition) override;

        void
        buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<int> &lengths, vector<int> &heights,
                                  XCondition &xc) override;

        void buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<int> &lengths,
                                       vector<XVariable *> &varHeights, XCondition &xc) override;

        void buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<XVariable *> &lengths,
                                       vector<int> &heights, XCondition &xc) override;

        void buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<XVariable *> &lengths,
                                       vector<XVariable *> &heights, XCondition &xc) override;

        void
        buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<int> &lengths, vector<int> &heights,
                                  vector<XVariable *> &ends, XCondition &xc) override;

        void buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<int> &lengths,
                                       vector<XVariable *> &varHeights, vector<XVariable *> &ends,
                                       XCondition &xc) override;

        void buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<XVariable *> &lengths,
                                       vector<int> &heights, vector<XVariable *> &ends, XCondition &xc) override;

        void buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<XVariable *> &lengths,
                                       vector<XVariable *> &heights, vector<XVariable *> &ends,
                                       XCondition &xc) override;

        void buildObjectiveMinimizeExpression(string expr) override;

        void buildObjectiveMaximizeExpression(string expr) override;


        void buildObjectiveMinimizeVariable(XVariable *x) override;


        void buildObjectiveMaximizeVariable(XVariable *x) override;


        void buildObjectiveMinimize(ExpressionObjective type, vector<XVariable *> &list, vector<int> &coefs) override;


        void buildObjectiveMaximize(ExpressionObjective type, vector<XVariable *> &list, vector<int> &coefs) override;


        void buildObjectiveMinimize(ExpressionObjective type, vector<XVariable *> &list) override;


        void buildObjectiveMaximize(ExpressionObjective type, vector<XVariable *> &list) override;


        void buildAnnotationDecision(vector<XVariable*> &list) override;

        void buildConstraintCount(string id, vector<Tree *> &trees, vector<int> &values, XCondition &xc) override;

        bool canonize;
    };


}

using namespace XCSP3Core;


XCSP3PrintCallbacks::XCSP3PrintCallbacks() : XCSP3CoreCallbacks(), canonize(true) {}


template<class T>
void displayList(vector<T> &list, string separator = " ") {
    if(list.size() > 8) {
        for(int i = 0; i < 3; i++)
            cout << list[i] << separator;
        cout << " ... ";
        for(decltype(list.size()) i = list.size() - 4; i < list.size(); i++)
            cout << list[i] << separator;
        cout << endl;
        return;
    }
    for(unsigned int i = 0; i < list.size(); i++)
        cout << list[i] << separator;
    cout << endl;
}


void displayList(vector<XVariable *> &list, string separator = " ") {
    if(list.size() > 8) {
        for(int i = 0; i < 3; i++)
            cout << list[i]->id << separator;
        cout << " ... ";
        for(decltype(list.size()) i = list.size() - 4; i < list.size(); i++)
            cout << list[i]->id << separator;
        cout << endl;
        return;
    }
    for(unsigned int i = 0; i < list.size(); i++)
        cout << list[i]->id << separator;
    cout << endl;
}


void XCSP3PrintCallbacks::beginInstance(InstanceType type) {
    cout << "Start Instance - type=" << type << endl;
}


void XCSP3PrintCallbacks::endInstance() {
    cout << "End SAX parsing " << endl;
}


void XCSP3PrintCallbacks::beginVariables() {
    cout << " start variables declaration" << endl;
}


void XCSP3PrintCallbacks::endVariables() {
    cout << " end variables declaration" << endl << endl;
}


void XCSP3PrintCallbacks::beginVariableArray(string id) {
    cout << "    array: " << id << endl;
}


void XCSP3PrintCallbacks::endVariableArray() {
}


void XCSP3PrintCallbacks::beginConstraints() {
    cout << " start constraints declaration" << endl;
}


void XCSP3PrintCallbacks::endConstraints() {
    cout << "\n end constraints declaration" << endl << endl;
}


void XCSP3PrintCallbacks::beginGroup(string id) {
    cout << "   start group of constraint " << id << endl;
}


void XCSP3PrintCallbacks::endGroup() {
    cout << "   end group of constraint" << endl;
}


void XCSP3PrintCallbacks::beginBlock(string classes) {
    cout << "   start block of constraint classes = " << classes << endl;
}


void XCSP3PrintCallbacks::endBlock() {
    cout << "   end block of constraint" << endl;
}


// string id, bool circular
void XCSP3PrintCallbacks::beginSlide(string id, bool) {
    cout << "   start slide " << id << endl;
}


void XCSP3PrintCallbacks::endSlide() {
    cout << "   end slide" << endl;
}


void XCSP3PrintCallbacks::beginObjectives() {
    cout << "   start Objective " << endl;
}


void XCSP3PrintCallbacks::endObjectives() {
    cout << "   end Objective " << endl;
}


void XCSP3PrintCallbacks::beginAnnotations() {
    cout << "   begin Annotations " << endl;
}


void XCSP3PrintCallbacks::endAnnotations() {
    cout << "   end Annotations " << endl;
}


void XCSP3PrintCallbacks::buildVariableInteger(string id, int minValue, int maxValue) {
    cout << "    var " << id << " : " << minValue << "..." << maxValue << endl;
}


void XCSP3PrintCallbacks::buildVariableInteger(string id, vector<int> &values) {
    cout << "    var " << id << " : ";
    cout << "        ";
    displayList(values);

}


void XCSP3PrintCallbacks::buildConstraintExtension(string id, vector<XVariable *> list, vector<vector<int>> &tuples, bool support, bool hasStar) {
    cout << "\n    extension constraint : " << id << endl;
    cout << "        " << (support ? "support" : "conflict") << " arity: " << list.size() << " nb tuples: " << tuples.size() << " star: " << hasStar << endl;
    cout << "        ";
    displayList(list);
}


void XCSP3PrintCallbacks::buildConstraintExtension(string id, XVariable *variable, vector<int> &tuples, bool support, bool hasStar) {
    cout << "\n    extension constraint with one variable: " << id << endl;
    cout << "        " <<(*variable) << " "<< (support ? "support" : "conflict") << " nb tuples: " << tuples.size() << " star: " << hasStar << endl;
    cout << endl;
}


// string id, vector<XVariable *> list, bool support, bool hasStar
void XCSP3PrintCallbacks::buildConstraintExtensionAs(string id, vector<XVariable *>, bool, bool) {
    cout << "\n    extension constraint similar as previous one: " << id << endl;
}


void XCSP3PrintCallbacks::buildConstraintIntension(string id, string expr) {
    cout << "\n    intension constraint (using string) : " << id << " : " << expr << endl;
}


void XCSP3PrintCallbacks::buildConstraintIntension(string id, Tree *tree) {
    cout << "\n    intension constraint using canonized tree: " << id << " : ";
    tree->prefixe();
    std::cout << "\n";
}


void XCSP3PrintCallbacks::buildConstraintPrimitive(string id, OrderType, XVariable *x, int k, XVariable *y) {
    cout << "\n   intension constraint " << id << ": " << x->id << (k >= 0 ? "+" : "") << k << " op " << y->id << endl;
}


void XCSP3PrintCallbacks::buildConstraintPrimitive(string id, OrderType op, XVariable *x, int k) {
    cout << "\n   constraint  " << id << ":" << x->id << " op " << k << "\n";
}

void XCSP3PrintCallbacks::buildConstraintPrimitive(string id, XVariable *x, bool in, int min, int max) {
        cout << "\n   constraint  " << id << ":"<< x->id << (in ? " in " : " not in ") << min << ".." << max <<"\n";
}


// string id, vector<XVariable *> &list, string start, vector<string> &final, vector<XTransition> &transitions
void XCSP3PrintCallbacks::buildConstraintRegular(string, vector<XVariable *> &list, string start, vector<string> &final, vector<XTransition> &transitions) {
    cout << "\n    regular constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        start: " << start << endl;
    cout << "        final: ";
    displayList(final, ",");
    cout << endl;
    cout << "        transitions: ";
    for(unsigned int i = 0; i < (transitions.size() > 4 ? 4 : transitions.size()); i++) {
        cout << "(" << transitions[i].from << "," << transitions[i].val << "," << transitions[i].to << ") ";
    }
    if(transitions.size() > 4) cout << "...";
    cout << endl;
}


// string id, vector<XVariable *> &list, vector<XTransition> &transitions
void XCSP3PrintCallbacks::buildConstraintMDD(string, vector<XVariable *> &list, vector<XTransition> &transitions) {
    cout << "\n    mdd constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        transitions: ";
    for(unsigned int i = 0; i < (transitions.size() > 4 ? 4 : transitions.size()); i++) {
        cout << "(" << transitions[i].from << "," << transitions[i].val << "," << transitions[i].to << ") ";
    }
    if(transitions.size() > 4) cout << "...";
    cout << endl;
}


void XCSP3PrintCallbacks::buildConstraintAlldifferent(string id, vector<XVariable *> &list) {
    cout << "\n    allDiff constraint" << id << endl;
    cout << "        ";
    displayList(list);
}


void XCSP3PrintCallbacks::buildConstraintAlldifferentExcept(string id, vector<XVariable *> &list, vector<int> &except) {
    cout << "\n    allDiff constraint with exceptions" << id << endl;
    cout << "        ";
    displayList(list);
    cout << "        Exceptions:";
    displayList(except);
}


void XCSP3PrintCallbacks::buildConstraintAlldifferent(string id, vector<Tree *> &list) {
    cout << "\n    allDiff constraint with expresions" << id << endl;
    cout << "        ";
    for(Tree *t : list) {
        t->prefixe();std::cout << " ";
    }
    std::cout << std::endl;
}

void XCSP3PrintCallbacks::buildConstraintAlldifferentList(string id, vector<vector<XVariable *>> &lists) {
    cout << "\n    allDiff list constraint" << id << endl;
    for(unsigned int i = 0; i < (lists.size() < 4 ? lists.size() : 3); i++) {
        cout << "        ";
        displayList(lists[i]);

    }
}


void XCSP3PrintCallbacks::buildConstraintAlldifferentMatrix(string id, vector<vector<XVariable *>> &matrix) {
    cout << "\n    allDiff matrix constraint" << id << endl;
    for(unsigned int i = 0; i < matrix.size(); i++) {
        cout << "        ";
        displayList(matrix[i]);
    }
}


void XCSP3PrintCallbacks::buildConstraintAllEqual(string id, vector<XVariable *> &list) {
    cout << "\n    allEqual constraint" << id << endl;
    cout << "        ";
    displayList(list);
}


void XCSP3PrintCallbacks::buildConstraintNotAllEqual(string id, vector<XVariable *> &list) {
    cout << "\n    not allEqual constraint" << id << endl;
    cout << "        ";
    displayList(list);
}


// string id, vector<XVariable *> &list, OrderType order
void XCSP3PrintCallbacks::buildConstraintOrdered(string, vector<XVariable *> &list, OrderType order) {
    cout << "\n    ordered constraint" << endl;
    string sep;
    if(order == LT) sep = " < ";
    if(order == LE) sep = " <= ";
    if(order == GT) sep = " > ";
    if(order == GE) sep = " >= ";
    cout << "        ";
    displayList(list, sep);
}

// string id, vector<XVariable *> &list, vector<int> &lengths, OrderType order
void XCSP3PrintCallbacks::buildConstraintOrdered(string, vector<XVariable *> &list, vector<int> &lengths, OrderType order) {
    cout << "\n    ordered constraint with lengths" << endl;
    string sep;
    if(order == LT) sep = " < ";
    if(order == LE) sep = " <= ";
    if(order == GT) sep = " > ";
    if(order == GE) sep = " >= ";
    cout << "        ";
    displayList(lengths); cout << "      ";
    displayList(list, sep);
}

// string id, vector<vector<XVariable *>> &lists, OrderType order
void XCSP3PrintCallbacks::buildConstraintLex(string, vector<vector<XVariable *>> &lists, OrderType order) {
    cout << "\n    lex constraint   nb lists: " << lists.size() << endl;
    string sep;
    if(order == LT) sep = " < ";
    if(order == LE) sep = " <= ";
    if(order == GT) sep = " > ";
    if(order == GE) sep = " >= ";
    cout << "        operator: " << sep << endl;
    for(unsigned int i = 0; i < lists.size(); i++) {
        cout << "        list " << i << ": ";
        cout << "        ";
        displayList(lists[i], " ");
    }
}


// string id, vector<vector<XVariable *>> &matrix, OrderType order
void XCSP3PrintCallbacks::buildConstraintLexMatrix(string, vector<vector<XVariable *>> &matrix, OrderType order) {
    cout << "\n    lex matrix constraint   matrix  " << endl;
    string sep;
    if(order == LT) sep = " < ";
    if(order == LE) sep = " <= ";
    if(order == GT) sep = " > ";
    if(order == GE) sep = " >= ";

    for(unsigned int i = 0; i < (matrix.size() < 4 ? matrix.size() : 3); i++) {
        cout << "        ";
        displayList(matrix[i]);
    }
    cout << "        Order " << sep << endl;
}


// string id, vector<XVariable *> &list, vector<int> &coeffs, XCondition &cond
void XCSP3PrintCallbacks::buildConstraintSum(string, vector<XVariable *> &list, vector<int> &coeffs, XCondition &cond) {
    cout << "\n        sum constraint:";
    if(list.size() > 8) {
        for(int i = 0; i < 3; i++)
            cout << (coeffs.size() == 0 ? 1 : coeffs[i]) << "*" << *(list[i]) << " ";
        cout << " ... ";
        for(decltype(list.size()) i = list.size() - 4; i < list.size(); i++)
            cout << (coeffs.size() == 0 ? 1 : coeffs[i]) << "*" << *(list[i]) << " ";
    } else {
        for(decltype(list.size()) i = 0; i < list.size(); i++)
            cout << (coeffs.size() == 0 ? 1 : coeffs[i]) << "*" << *(list[i]) << " ";
    }
    cout << cond << endl;
}


// string id, vector<XVariable *> &list, XCondition &cond
void XCSP3PrintCallbacks::buildConstraintSum(string, vector<XVariable *> &list, XCondition &cond) {
    cout << "\n        unweighted sum constraint:";
    cout << "        ";
    displayList(list, "+");
    cout << cond << endl;

}


// string id, vector<XVariable *> &list, vector<XVariable *> &coeffs, XCondition &cond
void XCSP3PrintCallbacks::buildConstraintSum(string, vector<XVariable *> &list, vector<XVariable *> &coeffs, XCondition &cond) {
    cout << "\n        scalar sum constraint:";
    if(list.size() > 8) {
        for(int i = 0; i < 3; i++)
            cout << coeffs[i]->id << "*" << *(list[i]) << " ";
        cout << " ... ";
        for(decltype(list.size()) i = list.size() - 4; i < list.size(); i++)
            cout << coeffs[i]->id << "*" << *(list[i]) << " ";
    } else {
        for(decltype(list.size()) i = 0; i < list.size(); i++)
            cout << coeffs[i]->id << "*" << *(list[i]) << " ";
    }
    cout << cond << endl;
}


void XCSP3PrintCallbacks::buildConstraintSum(string id, vector<Tree *> &list, vector<int> &coeffs, XCondition &cond) {
    std::cout << "\n        sum with expression constraint;";
    if(list.size() > 8) {
        for(int i = 0; i < 3; i++) {
            cout << coeffs[i];
            list[i]->prefixe();
        }
        cout << " ... ";
        for(decltype(list.size()) i = list.size() - 4; i < list.size(); i++) {
            cout << coeffs[i];
            list[i]->prefixe();
        }
    } else {
        for(decltype(list.size()) i = 0; i < list.size(); i++) {
            cout << coeffs[i];
            list[i]->prefixe();
        }
    }
    cout << cond << endl;
}

void XCSP3PrintCallbacks::buildConstraintSum(string id, vector<Tree *> &list, XCondition &cond) {
    if(list.size() > 8) {
        for(int i = 0; i < 3; i++) {
            list[i]->prefixe();
        }
        cout << " ... ";
        for(decltype(list.size()) i = list.size() - 4; i < list.size(); i++) {
            list[i]->prefixe();
        }
    } else {
        for(decltype(list.size()) i = 0; i < list.size(); i++) {
            list[i]->prefixe();
        }
    }
    cout << cond << endl;
}



// string id, vector<XVariable *> &list, int value, int k
void XCSP3PrintCallbacks::buildConstraintAtMost(string, vector<XVariable *> &list, int value, int k) {
    cout << "\n    AtMost constraint: val=" << value << " k=" << k << endl;
    cout << "        ";
    displayList(list);
}


// string id, vector<XVariable *> &list, int value, int k
void XCSP3PrintCallbacks::buildConstraintAtLeast(string, vector<XVariable *> &list, int value, int k) {
    cout << "\n    Atleast constraint: val=" << value << " k=" << k << endl;
    cout << "        ";
    displayList(list);
}


// string id, vector<XVariable *> &list, int value, int k
void XCSP3PrintCallbacks::buildConstraintExactlyK(string, vector<XVariable *> &list, int value, int k) {
    cout << "\n    Exactly constraint: val=" << value << " k=" << k << endl;
    cout << "        ";
    displayList(list);
}


// string id, vector<XVariable *> &list, vector<int> &values, int k
void XCSP3PrintCallbacks::buildConstraintAmong(string, vector<XVariable *> &list, vector<int> &values, int k) {
    cout << "\n    Among constraint: k=" << k << endl;
    cout << "        ";
    displayList(list);
    cout << "        values:";
    displayList(values);

}


// string id, vector<XVariable *> &list, int value, XVariable *x
void XCSP3PrintCallbacks::buildConstraintExactlyVariable(string, vector<XVariable *> &list, int value, XVariable *x) {
    cout << "\n    Exactly Variable constraint: val=" << value << " variable=" << *x << endl;
    cout << "        ";
    displayList(list);
}


// string id, vector<XVariable *> &list, vector<int> &values, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintCount(string, vector<XVariable *> &list, vector<int> &values, XCondition &xc) {
    cout << "\n    count constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        values: ";
    cout << "        ";
    displayList(values);
    cout << "        condition: " << xc << endl;
}


// string id, vector<XVariable *> &list, vector<XVariable *> &values, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintCount(string, vector<XVariable *> &list, vector<XVariable *> &values, XCondition &xc) {
    cout << "\n    count constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        values: ";
    displayList(values);
    cout << "        condition: " << xc << endl;
}


// string id, vector<XVariable *> &list, vector<int> &except, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintNValues(string, vector<XVariable *> &list, vector<int> &except, XCondition &xc) {
    cout << "\n    NValues with exceptions constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        exceptions: ";
    displayList(except);
    cout << "        condition:" << xc << endl;
}


// string id, vector<XVariable *> &list, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintNValues(string, vector<XVariable *> &list, XCondition &xc) {
    cout << "\n    NValues  constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        condition:" << xc << endl;
}


// string id, vector<XVariable *> &list, vector<int> values, vector<int> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(string, vector<XVariable *> &list, vector<int> values, vector<int> &occurs, bool closed) {
    cout << "\n    Cardinality constraint (int values, int occurs)  constraint closed: " << closed << endl;
    cout << "        ";
    displayList(list);
    cout << "        values:";
    displayList(values);
    cout << "        occurs:";
    displayList(occurs);
}


// string id, vector<XVariable *> &list, vector<int> values, vector<XVariable *> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(string, vector<XVariable *> &list, vector<int> values, vector<XVariable *> &occurs, bool closed) {
    cout << "\n    Cardinality constraint (int values, var occurs)  constraint closed: " << closed << endl;
    cout << "        ";
    displayList(list);
    cout << "        values:";
    displayList(values);
    cout << "        occurs:";
    displayList(occurs);
}


// string id, vector<XVariable *> &list, vector<int> values, vector<XInterval> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(string, vector<XVariable *> &list, vector<int> values, vector<XInterval> &occurs, bool closed) {
    cout << "\n    Cardinality constraint (int values, interval occurs)  constraint closed: " << closed << endl;
    cout << "        ";
    displayList(list);
    cout << "        values:";
    displayList(values);
    cout << "        occurs:";
    displayList(occurs);
}


// string id, vector<XVariable *> &list, vector<XVariable *> values, vector<int> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(string, vector<XVariable *> &list, vector<XVariable *> values, vector<int> &occurs, bool closed) {
    cout << "\n    Cardinality constraint (var values, int occurs)  constraint closed: " << closed << endl;
    cout << "        ";
    displayList(list);
    cout << "        values:";
    displayList(values);
    cout << "        occurs:";
    displayList(occurs);
}


// string id, vector<XVariable *> &list, vector<XVariable *> values, vector<XVariable *> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(string, vector<XVariable *> &list, vector<XVariable *> values, vector<XVariable *> &occurs, bool closed) {
    cout << "\n    Cardinality constraint (var values, var occurs)  constraint closed: " << closed << endl;
    cout << "        ";
    displayList(list);
    cout << "        values:";
    displayList(values);
    cout << "        occurs:";
    displayList(occurs);
}


// string id, vector<XVariable *> &list, vector<XVariable *> values, vector<XInterval> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(string, vector<XVariable *> &list, vector<XVariable *> values, vector<XInterval> &occurs, bool closed) {
    cout << "\n    Cardinality constraint (var values, interval occurs)  constraint closed: " << closed << endl;
    cout << "        ";
    displayList(list);
    cout << "        values:";
    displayList(values);
    cout << "        occurs:";
    displayList(occurs);
}


// string id, vector<XVariable *> &list, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintMinimum(string, vector<XVariable *> &list, XCondition &xc) {
    cout << "\n    minimum  constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        condition: " << xc << endl;
}


// string id, vector<XVariable *> &list, XVariable *index, int startIndex, RankType rank, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintMinimum(string, vector<XVariable *> &list, XVariable *index, int startIndex, RankType, XCondition &xc) {
    cout << "\n    arg_minimum  constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        index:" << *index << endl;
    cout << "        Start index : " << startIndex << endl;
    cout << "        condition: " << xc << endl;

}


// string id, vector<XVariable *> &list, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintMaximum(string, vector<XVariable *> &list, XCondition &xc) {
    cout << "\n    maximum  constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        condition: " << xc << endl;
}


void XCSP3PrintCallbacks::buildConstraintMaximum(string, vector<Tree *> &list, XCondition &xc) {
    cout << "\n    maximum  constraint" << endl;
    cout << "        ";
    for(Tree *t : list) {
        t->prefixe();std::cout << " ";
    }
    cout << "        condition: " << xc << endl;
}


// string id, vector<XVariable *> &list, XVariable *index, int startIndex, RankType rank, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintMaximum(string, vector<XVariable *> &list, XVariable *index, int startIndex, RankType, XCondition &xc) {
    cout << "\n    arg_maximum  constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        index:" << *index << endl;
    cout << "        Start index : " << startIndex << endl;
    cout << "        condition: " << xc << endl;
}


// string id, vector<XVariable *> &list, int value
void XCSP3PrintCallbacks::buildConstraintElement(string, vector<XVariable *> &list, int value) {
    cout << "\n    element constant constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        value: " << value << endl;
}


// string id, vector<XVariable *> &list, XVariable *value
void XCSP3PrintCallbacks::buildConstraintElement(string, vector<XVariable *> &list, XVariable *value) {
    cout << "\n    element variable constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        value: " << *value << endl;
}


// string id, vector<XVariable *> &list, int startIndex, XVariable *index, RankType rank, int value
void XCSP3PrintCallbacks::buildConstraintElement(string, vector<XVariable *> &list, int startIndex, XVariable *index, RankType, int value) {
    cout << "\n    element constant (with index) constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        value: " << value << endl;
    cout << "        Start index : " << startIndex << endl;
    cout << "        index : " << *index << endl;
}

void XCSP3PrintCallbacks::buildConstraintElement(string id, vector<vector<int> > &matrix, int startRowIndex, XVariable *rowIndex, int startColIndex, XVariable* colIndex, XVariable *value) {
    cout << "\n    element matrix with rowIndex, colIndex and Value variables\n";
    for(unsigned int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix.size(); j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
    cout << "        row index : " << *rowIndex << endl;
    cout << "        col index : " << *colIndex << endl;
    cout << "        value     : " << *value << endl;
}

void XCSP3PrintCallbacks::buildConstraintElement(string id, vector<XVariable *> &list, XVariable *index, int startIndex, XCondition &xc) {
    cout << "\n   element with list and condition\n";
    displayList(list);
    cout << "        Start index : " << startIndex << endl;
    cout << "        index : " << *index << endl;

    cout << "        condition: " << xc << endl;
}

// string id, vector<XVariable *> &list, int startIndex, XVariable *index, RankType rank, XVariable *value
void XCSP3PrintCallbacks::buildConstraintElement(string, vector<XVariable *> &list, int startIndex, XVariable *index, RankType, XVariable *value) {
    cout << "\n    element variable (with index) constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        value: " << *value << endl;
    cout << "        Start index : " << startIndex << endl;
    cout << "        index : " << *index << endl;
}


// string, vector<int> &list, int startIndex, XVariable *index, RankType rank, XVariable *value
void XCSP3PrintCallbacks::buildConstraintElement(string, vector<int> &list, int startIndex, XVariable *index, RankType, XVariable *value) {
    cout << "\n    element variable with list of integers (with index) constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        value: " << *value << endl;
    cout << "        Start index : " << startIndex << endl;
    cout << "        index : " << *index << endl;
}


// string id, vector<XVariable *> &list, int startIndex
void XCSP3PrintCallbacks::buildConstraintChannel(string, vector<XVariable *> &list, int startIndex) {
    cout << "\n    channel constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        Start index : " << startIndex << endl;
}


// string id, vector<XVariable *> &list1, int startIndex1, vector<XVariable *> &list2, int startIndex2
void XCSP3PrintCallbacks::buildConstraintChannel(string, vector<XVariable *> &list1, int, vector<XVariable *> &list2, int) {
    cout << "\n    channel constraint" << endl;
    cout << "        list1 ";
    displayList(list1);
    cout << "        list2 ";
    displayList(list2);
}


// string id, vector<XVariable *> &list, int startIndex, XVariable *value
void XCSP3PrintCallbacks::buildConstraintChannel(string, vector<XVariable *> &list, int, XVariable *value) {
    cout << "\n    channel constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        value: " << *value << endl;
}


// string id, vector<XVariable *> &list, vector<int> &values, vector<XInterval> &widths
void XCSP3PrintCallbacks::buildConstraintStretch(string, vector<XVariable *> &list, vector<int> &values, vector<XInterval> &widths) {
    cout << "\n    stretch constraint" << endl;
    cout << "        ";
    displayList(list);
    cout << "        values :";
    displayList(values);
    cout << "        widths:";
    displayList(widths);
}


// string id, vector<XVariable *> &list, vector<int> &values, vector<XInterval> &widths, vector<vector<int>> &patterns
void XCSP3PrintCallbacks::buildConstraintStretch(string, vector<XVariable *> &list, vector<int> &values, vector<XInterval> &widths, vector<vector<int>> &patterns) {
    cout << "\n    stretch constraint (with patterns)" << endl;
    cout << "        ";
    displayList(list);
    cout << "        values :";
    displayList(values);
    cout << "        widths:";
    displayList(widths);
    cout << "        patterns";
    for(unsigned int i = 0; i < patterns.size(); i++)
        cout << "(" << patterns[i][0] << "," << patterns[i][1] << ") ";
    cout << endl;
}


// string id, vector<XVariable *> &origins, vector<int> &lengths, bool zeroIgnored
void XCSP3PrintCallbacks::buildConstraintNoOverlap(string, vector<XVariable *> &origins, vector<int> &lengths, bool) {
    cout << "\n    nooverlap constraint" << endl;
    cout << "        origins";
    displayList(origins);
    cout << "        lengths";
    displayList(lengths);
}


// string id, vector<XVariable *> &origins, vector<XVariable *> &lengths, bool zeroIgnored
void XCSP3PrintCallbacks::buildConstraintNoOverlap(string, vector<XVariable *> &origins, vector<XVariable *> &lengths, bool) {
    cout << "\n    nooverlap constraint (origins and lenghts variables)" << endl;
    cout << "        origins:";
    displayList(origins);
    cout << "        lengths";
    displayList(lengths);
}


// string id, vector<vector<XVariable *>> &origins, vector<vector<int>> &lengths, bool zeroIgnored
void XCSP3PrintCallbacks::buildConstraintNoOverlap(string, vector<vector<XVariable *>> &origins, vector<vector<int>> &lengths, bool) {
    cout << "\n    kdim (int lengths) nooverlap constraint" << endl;
    cout << "origins: " << endl;
    for(unsigned int i = 0; i < origins.size(); i++) {
        cout << "        ";
        displayList(origins[i]);
    }
    cout << "lengths: " << endl;
    for(unsigned int i = 0; i < origins.size(); i++) {
        cout << "        ";
        displayList(lengths[i]);
    }

}


// string id, vector<vector<XVariable *>> &origins, vector<vector<XVariable *>> &lengths, bool zeroIgnored
void XCSP3PrintCallbacks::buildConstraintNoOverlap(string, vector<vector<XVariable *>> &origins, vector<vector<XVariable *>> &lengths, bool) {
    cout << "\n    kdim (lenghts vars nooverlap constraint" << endl;
    cout << "origins: " << endl;
    for(unsigned int i = 0; i < origins.size(); i++) {
        cout << "        ";
        displayList(origins[i]);
    }
    cout << "lengths: " << endl;
    for(unsigned int i = 0; i < origins.size(); i++) {
        cout << "        ";
        displayList(lengths[i]);
    }
}


// string id, vector<XVariable *> &list, vector<int> &values
void XCSP3PrintCallbacks::buildConstraintInstantiation(string, vector<XVariable *> &list, vector<int> &values) {
    cout << "\n    instantiation constraint" << endl;
    cout << "        list:";
    displayList(list);
    cout << "        values:";
    displayList(values);

}


// string id, vector<XVariable *> &list, vector<int> &values
void XCSP3PrintCallbacks::buildConstraintClause(string, vector<XVariable *> &positive, vector<XVariable *> &negative) {
    cout << "\n    Clause constraint" << endl;
    cout << "        positive lits size:" << positive.size() <<" ";
    displayList(positive);
    cout << "        negative lits size:" << negative.size() <<" ";
    displayList(negative);

}


// string id, vector<XVariable *> &list, int startIndex
void XCSP3PrintCallbacks::buildConstraintCircuit(string, vector<XVariable *> &list, int startIndex) {
    cout << "\n    circuit constraint" << endl;
    cout << "        list:";
    displayList(list);
    cout << "        startIndex:" << startIndex << endl;
}


// string id, vector<XVariable *> &list, int startIndex, int size
void XCSP3PrintCallbacks::buildConstraintCircuit(string, vector<XVariable *> &list, int startIndex, int size) {
    cout << "\n    circuit constraint" << endl;
    cout << "        list:";
    displayList(list);
    cout << "        startIndex:" << startIndex << endl;
    cout << "        size: " << size << endl;
}


// string id, vector<XVariable *> &list, int startIndex, XVariable *size
void XCSP3PrintCallbacks::buildConstraintCircuit(string, vector<XVariable *> &list, int startIndex, XVariable *size) {
    cout << "\n    circuit constraint" << endl;
    cout << "        list:";
    displayList(list);
    cout << "        startIndex:" << startIndex << endl;
    cout << "        size: " << size->id << endl;
}

void XCSP3PrintCallbacks::buildConstraintPrecedence(string id, vector<XVariable *> &list, vector<int> values, bool covered) {
    cout << "\n    Precedence constraint" << endl;
    cout << "        list:";
    displayList(list);
    cout << "        values: ";
    displayList(values);
    cout << "        covered?  " << covered << endl;
}

void XCSP3PrintCallbacks::buildConstraintCount(string id, vector<Tree *> &trees, vector<int> &values, XCondition &xc) {
    cout << "\n    Count constraint with trees and integer values" << endl;
}


void XCSP3PrintCallbacks::buildConstraintBinPacking(string id, vector<XVariable *> &list, vector<int> &sizes,
                                                    XCondition &cond) {

    cout << "\n    BinPacking constraint" << endl;
    cout << "        list:";
    displayList(list);
    cout << "        sizes: ";
    displayList(sizes);
    cout << "        condition:" << cond << endl;
}


void XCSP3PrintCallbacks::buildConstraintFlow(string id, vector<XVariable *> &list, vector<int> &balance, vector<int> &weights, vector<vector<int> > &arcs, XCondition &cond) {
    cout << "\n    Flow constraint" << endl;
    cout << "        list:";
    displayList(list);
    cout << "        balance: ";
    displayList(balance);
    cout << "        weights: ";
    displayList(weights);
    cout << "        arcs: ";
    cout << "("<<arcs[0][0] << "," << arcs[0][1] << ") ... (" << arcs.back()[0] << "," << arcs.back()[1]<<")" <<endl;

    cout << "        condition:" << cond << endl;

}
void XCSP3PrintCallbacks::buildConstraintKnapsack(string id, vector<XVariable *> &list, vector<int> &weights, vector<int> &profits,XCondition weightsCondition, XCondition &profitCondition) {
    cout << "\n    Knapsack constraint with integer limit" << endl;
    cout << "        list:";
    displayList(list);
    cout << "        profits: ";
    displayList(profits);
    cout << "        weights: ";
    displayList(weights);
    cout << "        weightsConditions: " << weightsCondition << endl;
    cout << "        profitscondition:" << profitCondition << endl;
}



void XCSP3PrintCallbacks::buildObjectiveMinimizeExpression(string expr) {

    cout << "\n    objective: minimize" << expr << endl;
}


void XCSP3PrintCallbacks::buildObjectiveMaximizeExpression(string expr) {
    cout << "\n    objective: maximize" << expr << endl;
}


void XCSP3PrintCallbacks::buildObjectiveMinimizeVariable(XVariable *x) {
    cout << "\n    objective: minimize variable " << x << endl;
}


void XCSP3PrintCallbacks::buildObjectiveMaximizeVariable(XVariable *x) {
    cout << "\n    objective: maximize variable " << x << endl;
}


void XCSP3PrintCallbacks::buildObjectiveMinimize(ExpressionObjective type, vector<XVariable *> &list, vector<int> &coefs) {
    XCSP3CoreCallbacks::buildObjectiveMinimize(type, list, coefs);
}


void XCSP3PrintCallbacks::buildObjectiveMaximize(ExpressionObjective type, vector<XVariable *> &list, vector<int> &coefs) {
    XCSP3CoreCallbacks::buildObjectiveMaximize(type, list, coefs);
}


void XCSP3PrintCallbacks::buildObjectiveMinimize(ExpressionObjective type, vector<XVariable *> &list) {
    XCSP3CoreCallbacks::buildObjectiveMinimize(type, list);
}


void XCSP3PrintCallbacks::buildObjectiveMaximize(ExpressionObjective type, vector<XVariable *> &list) {
    XCSP3CoreCallbacks::buildObjectiveMaximize(type, list);
}

void XCSP3PrintCallbacks::buildAnnotationDecision(vector<XVariable*> &list) {
    std::cout << "       decision variables" << std::endl<< "       ";
    displayList(list);

}

void XCSP3PrintCallbacks::buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<int> &lengths,
                                                    vector<XVariable *> &varHeights, XCondition &xc) {
    cout << "\n    Cumulative constraint" << endl;
    cout << "        list:";
    displayList(origins);
    cout << "        lengths:";
    displayList(lengths);
    cout << "        heights:";
    displayList(varHeights);
    cout << "        condition:" << xc << endl;
}

void
XCSP3PrintCallbacks::buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<XVariable *> &lengths,
                                               vector<int> &heights, XCondition &xc) {
    cout << "\n    Cumulative constraint" << endl;
    cout << "        list:";
    displayList(origins);
    cout << "        lengths:";
    displayList(lengths);
    cout << "        heights:";
    displayList(heights);
    cout << "        condition:" << xc << endl;
}

void
XCSP3PrintCallbacks::buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<XVariable *> &lengths,
                                               vector<XVariable *> &heights, XCondition &xc) {
    cout << "\n    Cumulative constraint" << endl;
    cout << "        list:";
    displayList(origins);
    cout << "        lengths:";
    displayList(lengths);
    cout << "        heights:";
    displayList(heights);
    cout << "        condition:" << xc << endl;
}

void XCSP3PrintCallbacks::buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<int> &lengths,
                                                    vector<int> &heights, vector<XVariable *> &ends, XCondition &xc) {
    cout << "\n    Cumulative constraint" << endl;
    cout << "        list:";
    displayList(origins);
    cout << "        lengths:";
    displayList(lengths);
    cout << "        heights:";
    displayList(heights);
    cout << "        ends:";
    displayList(ends);
    cout << "        condition:" << xc << endl;
}

void XCSP3PrintCallbacks::buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<int> &lengths,
                                                    vector<XVariable *> &varHeights, vector<XVariable *> &ends,
                                                    XCondition &xc) {
    cout << "\n    Cumulative constraint" << endl;
    cout << "        list:";
    displayList(origins);
    cout << "        lengths:";
    displayList(lengths);
    cout << "        heights:";
    displayList(varHeights);
    cout << "        ends:";
    displayList(ends);
    cout << "        condition:" << xc << endl;
}

void
XCSP3PrintCallbacks::buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<XVariable *> &lengths,
                                               vector<int> &heights, vector<XVariable *> &ends, XCondition &xc) {
    cout << "\n    Cumulative constraint" << endl;
    cout << "        list:";
    displayList(origins);
    cout << "        lengths:";
    displayList(lengths);
    cout << "        heights:";
    displayList(heights);
    cout << "        ends:";
    displayList(ends);
    cout << "        condition:" << xc << endl;
}

void
XCSP3PrintCallbacks::buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<XVariable *> &lengths,
                                               vector<XVariable *> &heights, vector<XVariable *> &ends,
                                               XCondition &xc) {
    cout << "\n    Cumulative constraint" << endl;
    cout << "        list:";
    displayList(origins);
    cout << "        lengths:";
    displayList(lengths);
    cout << "        heights:";
    displayList(heights);
    cout << "        ends:";
    displayList(ends);
    cout << "        condition:" << xc << endl;
}

void XCSP3PrintCallbacks::buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<int> &lengths,
                                                    vector<int> &heights, XCondition &xc) {
    cout << "\n    Cumulative constraint" << endl;
    cout << "        list:";
    displayList(origins);
    cout << "        lengths:";
    displayList(lengths);
    cout << "        heights:";
    displayList(heights);
    cout << "        condition:" << xc << endl;
}

#endif //COSOCO_XCSP3PRINTCALLBACKS_H
