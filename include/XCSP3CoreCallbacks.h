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
        vector <string> classesToDiscard;
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
        virtual void beginInstance(InstanceType type) {}


        virtual void endInstance() {}


        virtual void beginVariables() {}


        virtual void endVariables() {}


        virtual void beginVariableArray(string id) {} //beginArray
        virtual void endVariableArray() {}


        virtual void beginConstraints() {}


        virtual void endConstraints() {}


        virtual void beginGroup(string id) {}


        virtual void endGroup() {}


        virtual void beginBlock(string classes) {}


        virtual void endBlock() {}


        virtual void beginSlide(string id, bool circular) {}


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

        virtual void buildConstraintExtension(string id, vector<XVariable *> list, vector <vector<int>> &tuples, bool support, bool hasStar) {
            std::cout << "WARNING: tuples are not checked wrt domains" << std::endl;
            throw runtime_error("extension constraint is not yet supported");
        }


        virtual void buildConstraintExtension(string id, XVariable *variable, vector<int> &tuples, bool support, bool hasStar) {
            throw runtime_error("unary extension constraint is not yet supported");
        }


        virtual void buildConstraintExtensionAs(string id, vector<XVariable *> list, bool support, bool hasStar) {
            throw runtime_error("This extension constraint contains exactly the same tuples than previous one");
        }


        virtual void buildConstraintIntension(string id, string expr) {
            throw runtime_error("intension constraint is not yet supported");
        }


        virtual void buildConstraintPrimitive(string id, OrderType op, XVariable *x, int k, XVariable *y) {
            throw runtime_error("primitive constraint x +-k op y constraint is not yet supported. "
                                        "You can use classical intension constrain by assigning recognizeSpecialIntensionCases to false ");
        }

        //--------------------------------------------------------------------------------------
        // Language constraints
        //--------------------------------------------------------------------------------------

        virtual void buildConstraintRegular(string id, vector<XVariable *> &list, string st, vector <string> &final, vector <XTransition> &transitions) {
            throw runtime_error("regular constraint is not yet supported");
        }


        virtual void buildConstraintMDD(string id, vector<XVariable *> &list, vector <XTransition> &transitions) {
            throw runtime_error("MDD constraint is not yet supported");
        }


        //--------------------------------------------------------------------------------------
        // Comparison constraints
        //--------------------------------------------------------------------------------------

        virtual void buildConstraintAlldifferent(string id, vector<XVariable *> &list) {
            throw runtime_error("AllDiff constraint is not yet supported");
        }


        virtual void buildConstraintAlldifferentExcept(string id, vector<XVariable *> &list, vector<int> &except) {
            throw runtime_error("AllDiff constraint with exception is not yet supported");
        }


        virtual void buildConstraintAlldifferentList(string id, vector <vector<XVariable *>> &lists) {
            throw runtime_error("AllDiff list constraint  is not yet supported");
        }


        virtual void buildConstraintAlldifferentMatrix(string id, vector <vector<XVariable *>> &matrix) {
            throw runtime_error("AllDiff matrix constraint  is not yet supported");
        }


        virtual void buildConstraintAllEqual(string id, vector<XVariable *> &list) {
            throw runtime_error("Allequal constraint  is not yet supported");
        }


        virtual void buildConstraintNotAllEqual(string id, vector<XVariable *> &list) {
            throw runtime_error("NotAllequal constraint  is not yet supported");
        }


        virtual void buildConstraintOrdered(string id, vector<XVariable *> &list, OrderType order) {
            throw runtime_error("Ordered constraint  is not yet supported");
        }


        virtual void buildConstraintLex(string id, vector <vector<XVariable *>> &lists, OrderType order) {
            throw runtime_error("Lex constraint  is not yet supported");
        }


        virtual void buildConstraintLexMatrix(string id, vector <vector<XVariable *>> &matrix, OrderType order) {
            throw runtime_error("Lex matrix constraint  is not yet supported");
        }

        //--------------------------------------------------------------------------------------
        // Summing and counting constraints
        //--------------------------------------------------------------------------------------

        virtual void buildConstraintSum(string id, vector<XVariable *> &list, vector<int> &coeffs, XCondition &cond) {
            throw runtime_error("sum constraint  is not yet supported");
        }


        virtual void buildConstraintSum(string id, vector<XVariable *> &list, XCondition &cond) {
            throw runtime_error("unweighted sum constraint  is not yet supported");
        }


        virtual void buildConstraintSum(string id, vector<XVariable *> &list, vector<XVariable *> &coeffs, XCondition &cond) {
            throw runtime_error("sum constraint with variables weights is not yet supported");
        }


        virtual void buildConstraintAtMost(string id, vector<XVariable *> &list, int value, int k) {
            throw runtime_error("atmost constraint  is not yet supported");
        }


        virtual void buildConstraintAtLeast(string id, vector<XVariable *> &list, int value, int k) {
            throw runtime_error("atleast constraint  is not yet supported");
        }


        virtual void buildConstraintExactlyK(string id, vector<XVariable *> &list, int value, int k) {
            throw runtime_error("exactly K constraint  is not yet supported");
        }


        virtual void buildConstraintExactlyVariable(string id, vector<XVariable *> &list, int value, XVariable *x) {
            throw runtime_error("exactly Variable constraint  is not yet supported");
        }


        virtual void buildConstraintAmong(string id, vector<XVariable *> &list, vector<int> &values, int k) {// TODO AMONG
            throw runtime_error("Among constraint  is not yet supported");
        }


        virtual void buildConstraintCount(string id, vector<XVariable *> &list, vector<int> &values, XCondition &xc) {
            throw runtime_error("count with integer values constraint  is not yet supported");
        }


        virtual void buildConstraintCount(string id, vector<XVariable *> &list, vector<XVariable *> &values, XCondition &xc) {
            throw runtime_error("count with variables values constraint is not yet supported");
        }


        virtual void buildConstraintNValues(string id, vector<XVariable *> &list, vector<int> &except, XCondition &xc) {
            throw runtime_error("NValues with exception constraint is not yet supported");
        }


        virtual void buildConstraintNValues(string id, vector<XVariable *> &list, XCondition &xc) {
            throw runtime_error("NValues with exception constraint is not yet supported");
        }


        virtual void buildConstraintCardinality(string id, vector<XVariable *> &list, vector<int> values, vector<int> &occurs, bool closed) {
            throw runtime_error("cardinality with int values and int occurs constraint is not yet supported");
        }


        virtual void buildConstraintCardinality(string id, vector<XVariable *> &list, vector<int> values, vector<XVariable *> &occurs, bool closed) {
            throw runtime_error("cardinality with int values and int occurs constraint is not yet supported");
        }


        virtual void buildConstraintCardinality(string id, vector<XVariable *> &list, vector<int> values, vector <XInterval> &occurs, bool closed) {
            throw runtime_error("cardinality with int values and int occurs constraint is not yet supported");
        }


        virtual void buildConstraintCardinality(string id, vector<XVariable *> &list, vector<XVariable *> values, vector<int> &occurs, bool closed) {
            throw runtime_error("cardinality with int values and int occurs constraint is not yet supported");
        }


        virtual void buildConstraintCardinality(string id, vector<XVariable *> &list, vector<XVariable *> values, vector<XVariable *> &occurs, bool closed) {
            throw runtime_error("cardinality with int values and int occurs constraint is not yet supported");
        }


        virtual void buildConstraintCardinality(string id, vector<XVariable *> &list, vector<XVariable *> values, vector <XInterval> &occurs, bool closed) {
            throw runtime_error("cardinality with int values and int occurs constraint is not yet supported");
        }
        //--------------------------------------------------------------------------------------
        // Connection constraints
        //--------------------------------------------------------------------------------------

        virtual void buildConstraintMinimum(string id, vector<XVariable *> &list, XCondition &xc) {
            throw runtime_error("minimum constraint is not yet supported");

        }


        virtual void buildConstraintMinimum(string id, vector<XVariable *> &list, XVariable *index, int startIndex, RankType rank, XCondition &xc) {
            throw runtime_error("minimum with index constraint is not yet supported");
        }


        virtual void buildConstraintMaximum(string id, vector<XVariable *> &list, XCondition &xc) {
            throw runtime_error("maximum constraint is not yet supported");

        }


        virtual void buildConstraintMaximum(string id, vector<XVariable *> &list, XVariable *index, int startIndex, RankType rank, XCondition &xc) {
            throw runtime_error("maximum with index constraint is not yet supported");
        }


        virtual void buildConstraintElement(string id, vector<XVariable *> &list, int value) {
            throw runtime_error("Element value constraint is not yet supported");
        }


        virtual void buildConstraintElement(string id, vector<XVariable *> &list, XVariable *value) {
            throw runtime_error("Element variable constraint is not yet supported");
        }


        virtual void buildConstraintElement(string id, vector<XVariable *> &list, int startIndex, XVariable *index, RankType rank, int value) {
            throw runtime_error("Element value with index constraint is not yet supported");
        }


        virtual void buildConstraintElement(string id, vector<XVariable *> &list, int startIndex, XVariable *index, RankType rank, XVariable *value) {
            throw runtime_error("Element variable with index constraint is not yet supported");
        }


        virtual void buildConstraintChannel(string id, vector<XVariable *> &list, int startIndex) {
            throw runtime_error("channel with 1 list constraint is not yet supported");
        }


        virtual void buildConstraintChannel(string id, vector<XVariable *> &list1, int startIndex1, vector<XVariable *> &list2, int startIndex2) {
            throw runtime_error("channel with 2 lists constraint is not yet supported");
        }


        virtual void buildConstraintChannel(string id, vector<XVariable *> &list, int startIndex, XVariable *value) {
            throw runtime_error("channel with 1 list and 1 value constraint is not yet supported");
        }

        //--------------------------------------------------------------------------------------
        // packing and schedulling constraints
        //--------------------------------------------------------------------------------------

        virtual void buildConstraintStretch(string id, vector<XVariable *> &list, vector<int> &values, vector <XInterval> &widths) {
            throw runtime_error("stretch constraint is not yet supported");
        }


        virtual void buildConstraintStretch(string id, vector<XVariable *> &list, vector<int> &values, vector <XInterval> &widths, vector <vector<int>> &patterns) {
            throw runtime_error("stretch constraint is not yet supported");
        }


        virtual void buildConstraintNoOverlap(string id, vector<XVariable *> &origins, vector<int> &lengths, bool zeroIgnored) {
            throw runtime_error("nooverlap with int lengths constraint is not yet supported");
        }


        virtual void buildConstraintNoOverlap(string id, vector<XVariable *> &origins, vector<XVariable *> &lengths, bool zeroIgnored) {
            throw runtime_error("nooverlap with variable lengths constraint is not yet supported");
        }


        virtual void buildConstraintNoOverlap(string id, vector <vector<XVariable *>> &origins, vector <vector<int>> &lengths, bool zeroIgnored) {
            throw runtime_error("K dim nooverlap with int lengths constraint is not yet supported");
        }


        virtual void buildConstraintNoOverlap(string id, vector <vector<XVariable *>> &origins, vector <vector<XVariable *>> &lengths, bool zeroIgnored) {
            throw runtime_error("K dim nooverlap with variable lengths constraint is not yet supported");
        }


        virtual void buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<int> &lengths, vector<int> &heights, XCondition &xc) {
            throw runtime_error("cumulative (int lengths, int heights) constraint is not yet supported");
        }


        virtual void buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<int> &lengths, vector<XVariable *> &varHeights, XCondition &xc) {
            throw runtime_error("cumulative (int lengths, var heights) constraint is not yet supported");
        }


        virtual void buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<XVariable *> &lengths, vector<int> &heights, XCondition &xc) {
            throw runtime_error("cumulative (var lengths, int heights) constraint is not yet supported");
        }


        virtual void buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<XVariable *> &lengths, vector<XVariable *> &heights, XCondition &xc) {
            throw runtime_error("cumulative (var lengths, var heights) constraint is not yet supported");
        }


        virtual void buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<int> &lengths, vector<int> &heights, vector<XVariable *> &ends, XCondition &xc) {
            throw runtime_error("cumulative (int lengths, int heights) constraint is not yet supported");
        }


        virtual void
        buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<int> &lengths, vector<XVariable *> &varHeights, vector<XVariable *> &ends, XCondition &xc) {
            throw runtime_error("cumulative (int lengths, var heights, ends) constraint is not yet supported");
        }


        virtual void
        buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<XVariable *> &lengths, vector<int> &heights, vector<XVariable *> &ends, XCondition &xc) {
            throw runtime_error("cumulative (var lengths, int heights, ends) constraint is not yet supported");
        }


        virtual void
        buildConstraintCumulative(string id, vector<XVariable *> &origins, vector<XVariable *> &lengths, vector<XVariable *> &heights, vector<XVariable *> &ends, XCondition &xc) {
            throw runtime_error("cumulative (var lengths, var heights, ends) constraint is not yet supported");
        }

        //--------------------------------------------------------------------------------------
        // instantiation constraints
        //--------------------------------------------------------------------------------------

        virtual void buildConstraintInstantiation(string id, vector<XVariable *> &list, vector<int> &values) {
            throw runtime_error("instantiation constraint not yet supported");
        }

        //--------------------------------------------------------------------------------------
        // Objectives
        //--------------------------------------------------------------------------------------

        virtual void buildObjectiveMinimizeExpression(string expr) {
            throw runtime_error("minimize expression objective not yet supported");
        }


        virtual void buildObjectiveMaximizeExpression(string expr) {
            throw runtime_error("maximize expression objective not yet supported");
        }


        virtual void buildObjectiveMinimizeVariable(XVariable *x) {
            throw runtime_error("minimize variable objective not yet supported");
        }


        virtual void buildObjectiveMaximizeVariable(XVariable *x) {
            throw runtime_error("maximize variable objective not yet supported");
        }


        virtual void buildObjectiveMinimize(ExpressionObjective type, vector<XVariable *> &list, vector<int> &coefs) {
            throw runtime_error("minimize objective sum...  not yet supported");
        }


        virtual void buildObjectiveMaximize(ExpressionObjective type, vector<XVariable *> &list, vector<int> &coefs) {
            throw runtime_error("maximize objective   not yet supported");
        }


        virtual void buildObjectiveMinimize(ExpressionObjective type, vector<XVariable *> &list) {
            throw runtime_error("minimize objective   not yet supported");
        }


        virtual void buildObjectiveMaximize(ExpressionObjective type, vector<XVariable *> &list) {
            throw runtime_error("maximize objective   not yet supported");
        }

    };


};


#endif //COSOCO_XCSP3CORECALLBACKS_H





























