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
 *=============================================================================
 */
#ifndef COSOCO_XCSP3CORECALLBACKS_H
#define COSOCO_XCSP3CORECALLBACKS_H

#include "XCSP3Constants.h"
#include "XCSP3Variable.h"
#include "XCSP3Constraint.h"
#include <vector>
#include <string>


namespace XCSP3Core {

    using namespace std;

    class XCSP3CoreCallbacks {
    protected :
        vector<string> classesToDiscard;
    public :

        bool recognizeSpecialIntensionCases; // x<y.. x=k,
        bool recognizeSpecialCountCases;     // atleast, atmost, exactly, among, exctalyVariable
        bool recognizeNValuesCases;          // AllEqual, NotAllEqual, AllDiff
        bool normalizeSum;                   // Normalize sum : merge same variables...remove var with coef = 0,

        XCSP3CoreCallbacks() {
            recognizeSpecialIntensionCases = true;
            recognizeSpecialCountCases = true;
            recognizeNValuesCases = true;
            normalizeSum = true;
        }


        void addClassToDiscard(string cl) {
            classesToDiscard.push_back(cl);
        }


        bool discardedClasses(string classes) {
            if(classes == "")
                return false;

            for(string c : classesToDiscard)
                if(classes.find(c) != std::string::npos)
                    return true;
            return false;
        }


        // All these callbacks are called when the tag starts and when it ends.
        // InstanceType type
        virtual void beginInstance(InstanceType) {}


        virtual void endInstance() {}


        virtual void beginVariables() {}


        virtual void endVariables() {}


        // string id
        virtual void beginVariableArray(string) {} //beginArray
        virtual void endVariableArray() {}


        virtual void beginConstraints() {}


        virtual void endConstraints() {}


        // string id
        virtual void beginGroup(string) {}


        virtual void endGroup() {}


        // string classes
        virtual void beginBlock(string) {}


        virtual void endBlock() {}


        // string id, bool circular
        virtual void beginSlide(string, bool) {}


        virtual void endSlide() {}


        virtual void beginObjectives() {}


        virtual void endObjectives() {}


        //--------------------------------------------------------------------------------------
        // Build Variable. Must be implemented.
        //--------------------------------------------------------------------------------------
        virtual void buildVariableInteger(string id, int minValue, int maxValue) = 0;

        virtual void buildVariableInteger(string id, vector<int> &values) = 0;



        //--------------------------------------------------------------------------------------
        // Basic constraints
        //--------------------------------------------------------------------------------------

        // string id, vector<XVariable *> list, vector <vector<int>> &tuples, bool support, bool hasStar)
        virtual void buildConstraintExtension(string, vector<XVariable *>, vector <vector<int>> &, bool, bool) {
            std::cout << "WARNING: tuples are not checked wrt domains" << std::endl;
            throw runtime_error("extension constraint is not yet supported");
        }


        // string id, XVariable *variable, vector<int> &tuples, bool support, bool hasStar
        virtual void buildConstraintExtension(string, XVariable *, vector<int> &, bool, bool) {
            throw runtime_error("unary extension constraint is not yet supported");
        }


        // string id, vector<XVariable *> list, bool support, bool hasStar
        virtual void buildConstraintExtensionAs(string, vector<XVariable *>, bool, bool) {
            throw runtime_error("This extension constraint contains exactly the same tuples than previous one");
        }


        // string id, string expr
        virtual void buildConstraintIntension(string, string) {
            throw runtime_error("intension constraint is not yet supported");
        }


        // string id, OrderType op, XVariable *x, int k, XVariable *y
        virtual void buildConstraintPrimitive(string, OrderType, XVariable *, int, XVariable *) {
            throw runtime_error("primitive constraint x +-k op y constraint is not yet supported. "
                                        "You can use classical intension constrain by assigning recognizeSpecialIntensionCases to false ");
        }

        //--------------------------------------------------------------------------------------
        // Language constraints
        //--------------------------------------------------------------------------------------

        // string id, vector<XVariable *> &list, string st, vector<string> &final, vector<XTransition> &transitions
        virtual void buildConstraintRegular(string, vector<XVariable *> &, string, vector<string> &, vector<XTransition> &) {
            throw runtime_error("regular constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, vector<XTransition> &transitions
        virtual void buildConstraintMDD(string, vector<XVariable *> &, vector<XTransition> &) {
            throw runtime_error("MDD constraint is not yet supported");
        }


        //--------------------------------------------------------------------------------------
        // Comparison constraints
        //--------------------------------------------------------------------------------------

        // string id, vector<XVariable *> &list
        virtual void buildConstraintAlldifferent(string, vector<XVariable *> &) {
            throw runtime_error("AllDiff constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, vector<int> &except
        virtual void buildConstraintAlldifferentExcept(string, vector<XVariable *> &, vector<int> &) {
            throw runtime_error("AllDiff constraint with exception is not yet supported");
        }


        // string id, vector<vector<XVariable *>> &lists
        virtual void buildConstraintAlldifferentList(string, vector<vector<XVariable *>> &) {
            throw runtime_error("AllDiff list constraint  is not yet supported");
        }


        // string id, vector<vector<XVariable *>> &matrix
        virtual void buildConstraintAlldifferentMatrix(string, vector<vector<XVariable *>> &) {
            throw runtime_error("AllDiff matrix constraint  is not yet supported");
        }


        // string id, vector<XVariable *> &list
        virtual void buildConstraintAllEqual(string, vector<XVariable *> &) {
            throw runtime_error("Allequal constraint  is not yet supported");
        }


        // string id, vector<XVariable *> &list
        virtual void buildConstraintNotAllEqual(string, vector<XVariable *> &) {
            throw runtime_error("NotAllequal constraint  is not yet supported");
        }


        // string id, vector<XVariable *> &list, OrderType order
        virtual void buildConstraintOrdered(string, vector<XVariable *> &, OrderType) {
            throw runtime_error("Ordered constraint  is not yet supported");
        }


        // string id, vector<vector<XVariable *>> &lists, OrderType order
        virtual void buildConstraintLex(string, vector<vector<XVariable *>> &, OrderType) {
            throw runtime_error("Lex constraint  is not yet supported");
        }


        // string id, vector<vector<XVariable *>> &matrix, OrderType order
        virtual void buildConstraintLexMatrix(string, vector<vector<XVariable *>> &, OrderType) {
            throw runtime_error("Lex matrix constraint  is not yet supported");
        }

        //--------------------------------------------------------------------------------------
        // Summing and counting constraints
        //--------------------------------------------------------------------------------------

        // string id, vector<XVariable *> &list, vector<int> &coeffs, XCondition &cond
        virtual void buildConstraintSum(string, vector<XVariable *> &, vector<int> &, XCondition &) {
            throw runtime_error("sum constraint  is not yet supported");
        }


        // string id, vector<XVariable *> &list, XCondition &cond
        virtual void buildConstraintSum(string, vector<XVariable *> &, XCondition &) {
            throw runtime_error("unweighted sum constraint  is not yet supported");
        }


        // string id, vector<XVariable *> &list, vector<XVariable *> &coeffs, XCondition &cond
        virtual void buildConstraintSum(string, vector<XVariable *> &, vector<XVariable *> &, XCondition &) {
            throw runtime_error("sum constraint with variables weights is not yet supported");
        }


        // string id, vector<XVariable *> &list, int value, int k
        virtual void buildConstraintAtMost(string, vector<XVariable *> &, int, int) {
            throw runtime_error("atmost constraint  is not yet supported");
        }


        // string id, vector<XVariable *> &list, int value, int k
        virtual void buildConstraintAtLeast(string, vector<XVariable *> &, int, int) {
            throw runtime_error("atleast constraint  is not yet supported");
        }


        // string id, vector<XVariable *> &list, int value, int k
        virtual void buildConstraintExactlyK(string, vector<XVariable *> &, int, int) {
            throw runtime_error("exactly K constraint  is not yet supported");
        }


        // string id, vector<XVariable *> &list, int value, XVariable *x
        virtual void buildConstraintExactlyVariable(string, vector<XVariable *> &, int, XVariable *) {
            throw runtime_error("exactly Variable constraint  is not yet supported");
        }


        // string id, vector<XVariable *> &list, vector<int> &values, int k
        virtual void buildConstraintAmong(string, vector<XVariable *> &, vector<int> &, int) {// TODO AMONG
            throw runtime_error("Among constraint  is not yet supported");
        }


        // string id, vector<XVariable *> &list, vector<int> &values, XCondition &xc
        virtual void buildConstraintCount(string, vector<XVariable *> &, vector<int> &, XCondition &) {
            throw runtime_error("count with integer values constraint  is not yet supported");
        }


        // string id, vector<XVariable *> &list, vector<XVariable *> &values, XCondition &xc
        virtual void buildConstraintCount(string, vector<XVariable *> &, vector<XVariable *> &, XCondition &) {
            throw runtime_error("count with variables values constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, vector<int> &except, XCondition &xc
        virtual void buildConstraintNValues(string, vector<XVariable *> &, vector<int> &, XCondition &) {
            throw runtime_error("NValues with exception constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, XCondition &xc
        virtual void buildConstraintNValues(string, vector<XVariable *> &, XCondition &) {
            throw runtime_error("NValues with exception constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, vector<int> values, vector<int> &occurs, bool closed
        virtual void buildConstraintCardinality(string, vector<XVariable *> &, vector<int>, vector<int> &, bool) {
            throw runtime_error("cardinality with int values and int occurs constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, vector<int> values, vector<XVariable *> &occurs, bool closed
        virtual void buildConstraintCardinality(string, vector<XVariable *> &, vector<int>, vector<XVariable *> &, bool) {
            throw runtime_error("cardinality with int values and int occurs constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, vector<int> values, vector<XInterval> &occurs, bool closed
        virtual void buildConstraintCardinality(string, vector<XVariable *> &, vector<int>, vector<XInterval> &, bool) {
            throw runtime_error("cardinality with int values and int occurs constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, vector<XVariable *> values, vector<int> &occurs, bool closed
        virtual void buildConstraintCardinality(string, vector<XVariable *> &, vector<XVariable *>, vector<int> &, bool) {
            throw runtime_error("cardinality with int values and int occurs constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, vector<XVariable *> values, vector<XVariable *> &occurs, bool closed
        virtual void buildConstraintCardinality(string, vector<XVariable *> &, vector<XVariable *>, vector<XVariable *> &, bool) {
            throw runtime_error("cardinality with int values and int occurs constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, vector<XVariable *> values, vector<XInterval> &occurs, bool closed
        virtual void buildConstraintCardinality(string, vector<XVariable *> &, vector<XVariable *>, vector<XInterval> &, bool) {
            throw runtime_error("cardinality with int values and int occurs constraint is not yet supported");
        }
        //--------------------------------------------------------------------------------------
        // Connection constraints
        //--------------------------------------------------------------------------------------

        // string id, vector<XVariable *> &list, XCondition &xc
        virtual void buildConstraintMinimum(string, vector<XVariable *> &, XCondition &) {
            throw runtime_error("minimum constraint is not yet supported");

        }


        // string id, vector<XVariable *> &list, XVariable *index, int startIndex, RankType rank, XCondition &xc
        virtual void buildConstraintMinimum(string, vector<XVariable *> &, XVariable *, int, RankType, XCondition &) {
            throw runtime_error("minimum with index constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, XCondition &xc
        virtual void buildConstraintMaximum(string, vector<XVariable *> &, XCondition &) {
            throw runtime_error("maximum constraint is not yet supported");

        }


        // string id, vector<XVariable *> &list, XVariable *index, int startIndex, RankType rank, XCondition &xc
        virtual void buildConstraintMaximum(string, vector<XVariable *> &, XVariable *, int, RankType, XCondition &) {
            throw runtime_error("maximum with index constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, int value
        virtual void buildConstraintElement(string, vector<XVariable *> &, int) {
            throw runtime_error("Element value constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, XVariable *value
        virtual void buildConstraintElement(string, vector<XVariable *> &, XVariable *) {
            throw runtime_error("Element variable constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, int startIndex, XVariable *index, RankType rank, int value
        virtual void buildConstraintElement(string, vector<XVariable *> &, int, XVariable *, RankType, int) {
            throw runtime_error("Element value with index constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, int startIndex, XVariable *index, RankType rank, XVariable *value
        virtual void buildConstraintElement(string, vector<XVariable *> &, int, XVariable *, RankType, XVariable *) {
            throw runtime_error("Element variable with index constraint is not yet supported");
        }


        // string id, vector<int> &list, int startIndex, XVariable *index, RankType rank, XVariable *value
        virtual void buildConstraintElement(string, vector<int> &, int, XVariable *, RankType, XVariable *) {
            throw runtime_error("Element value  (with list of integers)  with index constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, int startIndex
        virtual void buildConstraintChannel(string, vector<XVariable *> &, int) {
            throw runtime_error("channel with 1 list constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list1, int startIndex1, vector<XVariable *> &list2, int startIndex2
        virtual void buildConstraintChannel(string, vector<XVariable *> &, int, vector<XVariable *> &, int) {
            throw runtime_error("channel with 2 lists constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, int startIndex, XVariable *value
        virtual void buildConstraintChannel(string, vector<XVariable *> &, int, XVariable *) {
            throw runtime_error("channel with 1 list and 1 value constraint is not yet supported");
        }

        //--------------------------------------------------------------------------------------
        // packing and schedulling constraints
        //--------------------------------------------------------------------------------------

        // string id, vector<XVariable *> &list, vector<int> &values, vector<XInterval> &widths
        virtual void buildConstraintStretch(string, vector<XVariable *> &, vector<int> &, vector<XInterval> &) {
            throw runtime_error("stretch constraint is not yet supported");
        }


        // string id, vector<XVariable *> &list, vector<int> &values, vector<XInterval> &widths, vector<vector<int>> &patterns
        virtual void buildConstraintStretch(string, vector<XVariable *> &, vector<int> &, vector<XInterval> &, vector<vector<int>> &) {
            throw runtime_error("stretch constraint is not yet supported");
        }


        // string id, vector<XVariable *> &origins, vector<int> &lengths, bool zeroIgnored
        virtual void buildConstraintNoOverlap(string, vector<XVariable *> &, vector<int> &, bool) {
            throw runtime_error("nooverlap with int lengths constraint is not yet supported");
        }


        // string id, vector<XVariable *> &origins, vector<XVariable *> &lengths, bool zeroIgnored
        virtual void buildConstraintNoOverlap(string, vector<XVariable *> &, vector<XVariable *> &, bool) {
            throw runtime_error("nooverlap with variable lengths constraint is not yet supported");
        }


        // string id, vector<vector<XVariable *>> &origins, vector<vector<int>> &lengths, bool zeroIgnored
        virtual void buildConstraintNoOverlap(string, vector<vector<XVariable *>> &, vector<vector<int>> &, bool) {
            throw runtime_error("K dim nooverlap with int lengths constraint is not yet supported");
        }


        // string id, vector<vector<XVariable *>> &origins, vector<vector<XVariable *>> &lengths, bool zeroIgnored
        virtual void buildConstraintNoOverlap(string, vector<vector<XVariable *>> &, vector<vector<XVariable *>> &, bool) {
            throw runtime_error("K dim nooverlap with variable lengths constraint is not yet supported");
        }


        // string id, vector<XVariable *> &origins, vector<int> &lengths, vector<int> &heights, XCondition &xc
        virtual void buildConstraintCumulative(string, vector<XVariable *> &, vector<int> &, vector<int> &, XCondition &) {
            throw runtime_error("cumulative (int lengths, int heights) constraint is not yet supported");
        }


        // string id, vector<XVariable *> &origins, vector<int> &lengths, vector<XVariable *> &varHeights, XCondition &xc
        virtual void buildConstraintCumulative(string, vector<XVariable *> &, vector<int> &, vector<XVariable *> &, XCondition &) {
            throw runtime_error("cumulative (int lengths, var heights) constraint is not yet supported");
        }


        // string id, vector<XVariable *> &origins, vector<XVariable *> &lengths, vector<int> &heights, XCondition &xc
        virtual void buildConstraintCumulative(string, vector<XVariable *> &, vector<XVariable *> &, vector<int> &, XCondition &) {
            throw runtime_error("cumulative (var lengths, int heights) constraint is not yet supported");
        }


        // string id, vector<XVariable *> &origins, vector<XVariable *> &lengths, vector<XVariable *> &heights, XCondition &xc
        virtual void buildConstraintCumulative(string, vector<XVariable *> &, vector<XVariable *> &, vector<XVariable *> &, XCondition &) {
            throw runtime_error("cumulative (var lengths, var heights) constraint is not yet supported");
        }


        // string id, vector<XVariable *> &origins, vector<int> &lengths, vector<int> &heights, vector<XVariable *> &ends, XCondition &xc
        virtual void buildConstraintCumulative(string, vector<XVariable *> &, vector<int> &, vector<int> &, vector<XVariable *> &, XCondition &) {
            throw runtime_error("cumulative (int lengths, int heights) constraint is not yet supported");
        }


        // string id, vector<XVariable *> &origins, vector<int> &lengths, vector<XVariable *> &varHeights, vector<XVariable *> &ends, XCondition &xc
        virtual void buildConstraintCumulative(string, vector<XVariable *> &, vector<int> &, vector<XVariable *> &, vector<XVariable *> &, XCondition &) {
            throw runtime_error("cumulative (int lengths, var heights, ends) constraint is not yet supported");
        }


        // string id, vector<XVariable *> &origins, vector<XVariable *> &lengths, vector<int> &heights, vector<XVariable *> &ends, XCondition &xc
        virtual void buildConstraintCumulative(string, vector<XVariable *> &, vector<XVariable *> &, vector<int> &, vector<XVariable *> &, XCondition &) {
            throw runtime_error("cumulative (var lengths, int heights, ends) constraint is not yet supported");
        }


        // string id, vector<XVariable *> &origins, vector<XVariable *> &lengths, vector<XVariable *> &heights, vector<XVariable *> &ends, XCondition &xc
        virtual void buildConstraintCumulative(string, vector<XVariable *> &, vector<XVariable *> &, vector<XVariable *> &, vector<XVariable *> &, XCondition &) {
            throw runtime_error("cumulative (var lengths, var heights, ends) constraint is not yet supported");
        }

        //--------------------------------------------------------------------------------------
        // instantiation constraints
        //--------------------------------------------------------------------------------------

        // string id, vector<XVariable *> &list, vector<int> &values
        virtual void buildConstraintInstantiation(string, vector<XVariable *> &, vector<int> &) {
            throw runtime_error("instantiation constraint not yet supported");
        }

        //--------------------------------------------------------------------------------------
        // Graph constraints
        //--------------------------------------------------------------------------------------

        // string id, vector<XVariable *> &list, int startIndex
        virtual void buildConstraintCircuit(string, vector<XVariable *> &, int) {
            throw runtime_error("circuit constraint not yet supported");
        }


        // string id, vector<XVariable *> &list, int startIndex, int size
        virtual void buildConstraintCircuit(string, vector<XVariable *> &, int, int) {
            throw runtime_error("circuit constraint not yet supported");
        }


        // string id, vector<XVariable *> &list, int startIndex, XVariable *size
        virtual void buildConstraintCircuit(string, vector<XVariable *> &, int, XVariable *) {
            throw runtime_error("circuit constraint not yet supported");
        }

        //--------------------------------------------------------------------------------------
        // Objectives
        //--------------------------------------------------------------------------------------

        // string expr
        virtual void buildObjectiveMinimizeExpression(string) {
            throw runtime_error("minimize expression objective not yet supported");
        }


        // string expr
        virtual void buildObjectiveMaximizeExpression(string) {
            throw runtime_error("maximize expression objective not yet supported");
        }


        // XVariable *x
        virtual void buildObjectiveMinimizeVariable(XVariable *) {
            throw runtime_error("minimize variable objective not yet supported");
        }


        // XVariable *x
        virtual void buildObjectiveMaximizeVariable(XVariable *) {
            throw runtime_error("maximize variable objective not yet supported");
        }


        // ExpressionObjective type, vector<XVariable *> &list, vector<int> &coefs
        virtual void buildObjectiveMinimize(ExpressionObjective, vector<XVariable *> &, vector<int> &) {
            throw runtime_error("minimize objective sum...  not yet supported");
        }


        // ExpressionObjective type, vector<XVariable *> &list, vector<int> &coefs
        virtual void buildObjectiveMaximize(ExpressionObjective, vector<XVariable *> &, vector<int> &) {
            throw runtime_error("maximize objective   not yet supported");
        }


        // ExpressionObjective type, vector<XVariable *> &list
        virtual void buildObjectiveMinimize(ExpressionObjective, vector<XVariable *> &) {
            throw runtime_error("minimize objective   not yet supported");
        }


        // ExpressionObjective type, vector<XVariable *> &list
        virtual void buildObjectiveMaximize(ExpressionObjective, vector<XVariable *> &) {
            throw runtime_error("maximize objective   not yet supported");
        }

    };

}

#endif //COSOCO_XCSP3CORECALLBACKS_H

