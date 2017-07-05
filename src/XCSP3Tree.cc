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

#include <map>

#include "XCSP3Tree.h"
#include "XCSP3TreeNode.h"
#include <sstream>
#include <vector>
using namespace XCSP3Core;
using namespace std;


// trim from start

static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end

static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends

static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

static int min(int v1, int v2, int v3) {
    if (v1 == -1) v1 = INT_MAX;
    if (v2 == -1) v2 = INT_MAX;
    if (v3 == -1) v3 = INT_MAX;

    if (v1 < v2) {
        if (v1 < v3) return v1;
        return v3;
    }
    if (v2 < v3) return v2;
    return v3;
}

Node *Tree::fromStringToTree(std::string current) {

    current = trim(current);
    std::vector<NodeOperator*> stack;
    std::vector<Node*> params;
    while (true) {
        int posOpenParenthesis = current.find('(');
        int posCloseParenthesis = current.find(')');
        int posComma = current.find(',');
        int nb = min(posCloseParenthesis, posComma, posOpenParenthesis);


        string currentElement = current.substr(0, nb);
        if (currentElement != "" && nb != posOpenParenthesis)
            createBasicParameter(currentElement,stack,params);
        

        if (nb == posCloseParenthesis)
            closeOperator(stack,params);


        if (nb == posOpenParenthesis)
            createOperator(currentElement,stack,params);

        current = current.substr(nb + 1);
        if (current == "") break;
    }
    assert(params.size() == 1);
    assert(stack.size() == 0);

    return params.back();
}

void Tree::createOperator(string currentElement, ::vector<NodeOperator*> &stack,std::vector<Node*> &params) {
    NodeOperator *tmp = nullptr;
    if (currentElement == "neg") tmp = new NodeNeg();
    if (currentElement == "abs") tmp = new NodeAbs();

    if (currentElement == "add") tmp = new NodeAdd();
    if (currentElement == "sub") tmp = new NodeSub();
    if (currentElement == "mul") tmp = new NodeMult();
    if (currentElement == "div") tmp = new NodeDiv();
    if (currentElement == "mod") tmp = new NodeMod();

    if (currentElement == "sqr") tmp = new NodeSquare();
    if (currentElement == "pow") tmp = new NodePow();

    if (currentElement == "min") tmp = new NodeMin();
    if (currentElement == "max") tmp = new NodeMax();
    if (currentElement == "dist") tmp = new NodeDist();

    if (currentElement == "le") tmp = new NodeLE();
    if (currentElement == "lt") tmp = new NodeLT();
    if (currentElement == "ge") tmp = new NodeGE();
    if (currentElement == "gt") tmp = new NodeGT();

    if (currentElement == "ne") tmp = new NodeNE();
    if (currentElement == "eq") tmp = new NodeEQ();

    if (currentElement == "not") tmp = new NodeNot();
    if (currentElement == "and") tmp = new NodeAnd();
    if (currentElement == "or") tmp = new NodeOr();
    if (currentElement == "xor") tmp = new NodeXor();
    if (currentElement == "imp") tmp = new NodeImp();
    if (currentElement == "if") tmp = new NodeIf();
    if (currentElement == "iff") tmp = new NodeIff();

    if (currentElement == "in") tmp = new NodeIn();
    if (currentElement == "set") tmp = new NodeSet();

    if (tmp == nullptr)
        throw runtime_error("Intension constraint. Unknown operator: " + currentElement);
    stack.push_back(tmp);
    params.push_back(nullptr); // delemitor
}

void Tree::closeOperator(std::vector<NodeOperator*> &stack,std::vector<Node*> &params) {
    NodeOperator *tmp = stack.back();

    int startParams = params.size() - 1;
    while (params[startParams] != nullptr)
        startParams--;
    startParams++;
    int nbP = 0;
    for (int i = startParams; i < params.size(); i++, nbP++)
        tmp->addParameter(params[i]);
    stack.pop_back();
    //params.shrink(nbP);
    params.erase(params.end() - nbP, params.end());
    assert(params.back() == nullptr);
    params.pop_back();
    params.push_back(tmp);
}

void Tree::createBasicParameter(string currentElement, std::vector<NodeOperator*> &stack,std::vector<Node*> &params) {
    try {
        int nb = stoi(currentElement);
        params.push_back(new NodeConstant(nb));
    } catch (invalid_argument e) {
        int position = -1;
        for (unsigned int i = 0; i < listOfVariables.size(); i++)
            if (listOfVariables[i] == currentElement) {
                position = i;
                break;
            }
        if (position == -1) {
            listOfVariables.push_back(currentElement);
            position = listOfVariables.size() - 1;
        }
        params.push_back(new NodeVariable(currentElement, position));
    }
}