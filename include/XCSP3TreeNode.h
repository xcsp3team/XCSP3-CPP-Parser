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

#ifndef XCSP3PARSER_XCSP3TREENODE_H
#define XCSP3PARSER_XCSP3TREENODE_H

#include<cmath>
#include <vector>
#include <map>
#include<iostream>
#include<algorithm>
#include<cassert>

namespace XCSP3Core {


    NodeOperator *createNodeOperator(std::string op) {
        NodeOperator *tmp = nullptr;
        if (op == "neg") tmp = new NodeNeg();
        if (op == "abs") tmp = new NodeAbs();

        if (op == "add") tmp = new NodeAdd();
        if (op == "sub") tmp = new NodeSub();
        if (op == "mul") tmp = new NodeMult();
        if (op == "div") tmp = new NodeDiv();
        if (op == "mod") tmp = new NodeMod();

        if (op == "sqr") tmp = new NodeSquare();
        if (op == "pow") tmp = new NodePow();

        if (op == "min") tmp = new NodeMin();
        if (op == "max") tmp = new NodeMax();
        if (op == "dist") tmp = new NodeDist();

        if (op == "le") tmp = new NodeLE();
        if (op == "lt") tmp = new NodeLT();
        if (op == "ge") tmp = new NodeGE();
        if (op == "gt") tmp = new NodeGT();

        if (op == "ne") tmp = new NodeNE();
        if (op == "eq") tmp = new NodeEQ();

        if (op == "not") tmp = new NodeNot();
        if (op == "and") tmp = new NodeAnd();
        if (op == "or") tmp = new NodeOr();
        if (op == "xor") tmp = new NodeXor();
        if (op == "imp") tmp = new NodeImp();
        if (op == "if") tmp = new NodeIf();
        if (op == "iff") tmp = new NodeIff();

        if (op == "in") tmp = new NodeIn();
        if (op == "set") tmp = new NodeSet();

        return tmp;
    }


    //-------------------------------------

    class Node {
        friend class Intension;

    public:
        virtual int evaluate(std::map<std::string, int> &tuple) = 0;
        virtual Node *canonize() = 0;
        virtual void prefixe()   = 0;
        virtual Node *clone()    = 0;
    };


    //-------------------------------------

    class NodeConstant : public Node {

    public:
        int val;


        NodeConstant(int v) : val(v) {}


        // std::map<std::string, int> &tuple
        int evaluate(std::map<std::string, int> &) override {
            return val;
        }


        Node *clone() {
            return new NodeConstant(val);
        }


        Node *canonize() override {
            return clone();
        }


        void prefixe() override {
            std::cout << val;
        }
    };

    //-------------------------------------

    class NodeVariable : public Node {
    protected:
        std::string var;
    public:

        NodeVariable(std::string v) : var(v) {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return tuple[var];
        }


        Node *clone() {
            return new NodeVariable(var);
        }


        Node *canonize() override {
            return clone();
        }


        void prefixe() override {
            std::cout << var;
        }
    };


    //-------------------------------------
    template<class T>
    T *clone(T *tmp) { return new T(tmp); }


    class NodeOperator : public Node {
    public:
        std::string op;
        std::vector<Node *> parameters;
        bool isSymmetricOperator;
        std::string logicalInversion;

        NodeOperator(std::string o) : op(o), isSymmetricOperator(false), logicalInversion("") {}


        NodeOperator* addParameter(Node *p) {
            parameters.push_back(p);
            return this;
        }

        NodeOperator* addParameters(std::vector<Node *> params) {
            std::copy(params.begin(),params.end(), parameters);
            return this;
        }


        Node *clone() override {
            NodeOperator *tmp = clone(this);
            for(Node *n : parameters)
                tmp->parameters.push_back(n->clone());
        }


        Node *canonize() override {
            std::vector<Node *> newParams;
            for(Node * n : parameters)
                newParams.push_back(n->canonize());

            if (isSymmetricOperator)
                std::sort(newParams); // TODO

            std::string newType = op;
            // sons are potentially sorted if the type corresponds to a non-symmetric binary relational operator (in that case, we swap sons and
            // arithmetically
            // inverse the operator)
            if (newParams.length == 2 && type.isNonSymmetricRelationalOperator() && (type.arithmeticInversion().ordinal() < type.ordinal()
                                                                                   || (type.arithmeticInversion().ordinal() == type.ordinal() && newParams[0].compareTo(newParams[1]) > 0))) {
                newType = type.arithmeticInversion();
                Utilities.swap(newParams, 0, 1);
            }
            // Now, some specific reformulation rules are applied
            NodeOperator *tmp = nullptr;
            if (newType == "abs" && (tmp = dynamic_cast<NodeSub*>(newParams[0])) != nullptr) // abs(sub(...)) becomes dist(...)
                return (new NodeDist())->addParameters(tmp->parameters);

            if (newType == "not" && (tmp = dynamic_cast<NodeNot*>(newParams[0])) != nullptr) // not(not(...)) becomes ...
                return tmp->parameters[0];

            if (newType == "neg" && (tmp = dynamic_cast<NodeNeg*>(newParams[0])) != nullptr) // neg(neg(...)) becomes ...
                return tmp->parameters[0];

            if (newType == "not" && (tmp = dynamic_cast<NodeOperator*>(newParams[0])) != nullptr && tmp->logicalInversion != "")
                return createNodeOperator(tmp->logicalInversion)->addParameters(tmp->parameters);// not(lt(...)) becomes ge(...), not(eq(...)) becomes ne(...), and
                // so on.

            if (newParams.size() == 1 && (newType == "add" || newType == "mul" || newType == "min" || newType == "max" || newType == "eq" || newType == "and"
                                          || newType == "or" || newType == "xor" || newType == "iff")) // certainly can happen during the canonization process
                return newParams[0];

            if (newType == ADD) { // we merge long (similar operations possible for MUL, MIN, ...)
                if (newParams.length >= 2 && newParams[newParams.length - 1].type == LONG && newParams[newParams.length - 2].type == LONG) {
                    List<XNode<V>> list = IntStream.range(0, newParams.length - 2).mapToObj(j -> newParams[j]).collect(Collectors.toList());
                    list.add(new XNodeLeaf<V>(LONG, (long) newParams[newParams.length - 1].firstVal() + newParams[newParams.length - 2].firstVal()));
                    return new XNodeParent<V>(ADD, list).canonization();
                }
            }
            // Then, we merge operators when possible; for example add(add(x,y),z) becomes add(x,y,z)
            if (isSymmetricOperator && newType != "eq" && newType != "dist" && newType != "disjoint") {
                for (int i = 0; i < newParams.length; i++) {
                    if (newParams[i].type == newType) {
                        List<XNode<V>> list = IntStream.rangeClosed(0, i - 1).mapToObj(j -> newParams[j]).collect(Collectors.toList());
                        Stream.of(((XNodeParent<V>) newParams[i]).sons).forEach(s -> list.add(s));
                        IntStream.range(i + 1, newParams.length).mapToObj(j -> newParams[j]).forEach(s -> list.add(s));
                        return new XNodeParent<V>(newType, list).canonization();
                    }
                }
            }
            if (newParams.length == 2 && newType.isRelationalOperator()) {
                // First, we replace sub by add when possible
                if (newParams[0].type == SUB && newParams[1].type == SUB) {
                    XNode<V> a = new XNodeParent<V>(ADD, ((XNodeParent<V>) newParams[0]).sons[0], ((XNodeParent<V>) newParams[1]).sons[1]);
                    XNode<V> b = new XNodeParent<V>(ADD, ((XNodeParent<V>) newParams[1]).sons[0], ((XNodeParent<V>) newParams[0]).sons[1]);
                    return new XNodeParent<V>(newType, a, b).canonization();
                } else if (newParams[1].type == SUB) {
                    XNode<V> a = new XNodeParent<V>(ADD, newParams[0], ((XNodeParent<V>) newParams[1]).sons[1]);
                    XNode<V> b = ((XNodeParent<V>) newParams[1]).sons[0];
                    return new XNodeParent<V>(newType, a, b).canonization();
                } else if (newParams[0].type == SUB) {
                    XNode<V> a = ((XNodeParent<V>) newParams[0]).sons[0];
                    XNode<V> b = new XNodeParent<V>(ADD, newParams[1], ((XNodeParent<V>) newParams[0]).sons[1]);
                    return new XNodeParent<V>(newType, a, b).canonization();
                }
                // next, we remove some add when possible
                if (newParams[0].type == ADD && newParams[1].type == ADD) {
                    XNode<V>[] ns1 = ((XNodeParent<V>) newParams[0]).sons, ns2 = ((XNodeParent<V>) newParams[1]).sons;
                    if (ns1.length == 2 && ns2.length == 2 && ns1[1].type == LONG && ns2[1].type == LONG) {
                        ((XNodeLeaf<?>) ns1[1]).value = (long) ns1[1].firstVal() - ns2[1].firstVal();
                        newParams[1] = ns2[0];
                        return new XNodeParent<V>(newType, newParams).canonization();
                    }
                }
            }
            return new XNodeParent<V>(newType, newParams);
        }

    };

    class NodeUnary : public NodeOperator {
    public:

        NodeUnary(std::string o) : NodeOperator(o) {}

        void prefixe() override {
            std::cout << op << "(";
            parameters[0]->prefixe();
            std::cout << ")";
        }
    };

    //-------------------------------------

    class NodeBinary : public NodeOperator {
    public:


        NodeBinary(std::string o) : NodeOperator(o) {}


        void prefixe() override {
            std::cout << op << "(";
            parameters[0]->prefixe();
            std::cout << ",";
            parameters[1]->prefixe();
            std::cout << ")";
        }
    };


    //-------------------------------------

    class NodeNAry : public NodeOperator {
        friend class NodeIn;

    protected:
        std::vector<Node *> parameters;
    public:

        NodeNAry(std::string o) : NodeOperator(o) {}


    public:

        void prefixe() override {
            std::cout << op << "(";
            for(unsigned int i = 0 ; i < parameters.size() ; i++) {
                if(i != 0) std::cout << ",";
                parameters[i]->prefixe();

            }
            std::cout << ")";
        }
    };


    //-------------------------------------

    class NodeNeg : public NodeUnary {
    public:

        NodeNeg() : NodeUnary("neg") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return -parameters[0]->evaluate(tuple);
        }
    };

    // --------------------------------------------------------------------------

    class NodeAbs : public NodeUnary {
    public:

        NodeAbs() : NodeUnary("abs") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int v = parameters[0]->evaluate(tuple);
            return v > 0 ? v : -v;
        }
    };

    class NodeSquare : public NodeUnary {
    public:

        NodeSquare() : NodeUnary("sqr") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int v = parameters[0]->evaluate(tuple);
            return v * v;
        }
    };

    class NodeNot : public NodeUnary {
    public:

        NodeNot() : NodeUnary("not") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int v = parameters[0]->evaluate(tuple);
            return !v;//v ? 0 : v;
        }

    };
    // --------------------------------------------------------------------------

    class NodeSub : public NodeBinary {
    public:

        NodeSub() : NodeBinary("sub") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameters[0]->evaluate(tuple) - parameters[1]->evaluate(tuple);
        }
    };

    class NodeDiv : public NodeBinary {
    public:

        NodeDiv() : NodeBinary("div") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameters[0]->evaluate(tuple) / parameters[1]->evaluate(tuple);
        }
    };

    class NodeMod : public NodeBinary {
    public:

        NodeMod() : NodeBinary("mod") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameters[0]->evaluate(tuple) % parameters[1]->evaluate(tuple);
        }
    };

    class NodePow : public NodeBinary {
    public:

        NodePow() : NodeBinary("pow") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return pow(parameters[0]->evaluate(tuple), parameters[1]->evaluate(tuple));
        }
    };

    class NodeDist : public NodeBinary {
    public:

        NodeDist() : NodeBinary("dist") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int v = parameters[0]->evaluate(tuple) - parameters[1]->evaluate(tuple);
            return v > 0 ? v : -v;
        }
    };

    class NodeLE : public NodeBinary {
    public:

        NodeLE() : NodeBinary("le") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameters[0]->evaluate(tuple) <= parameters[1]->evaluate(tuple);
        }
    };

    class NodeLT : public NodeBinary {
    public:

        NodeLT() : NodeBinary("lt") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameters[0]->evaluate(tuple) < parameters[1]->evaluate(tuple);
        }
    };

    class NodeGE : public NodeBinary {
    public:

        NodeGE() : NodeBinary("ge") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameters[0]->evaluate(tuple) >= parameters[1]->evaluate(tuple);
        }
    };

    class NodeGT : public NodeBinary {
    public:

        NodeGT() : NodeBinary("gt") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameters[0]->evaluate(tuple) > parameters[1]->evaluate(tuple);
        }
    };

    class NodeNE : public NodeBinary {
    public:

        NodeNE() : NodeBinary("ne") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameters[0]->evaluate(tuple) != parameters[1]->evaluate(tuple);
        }
    };

    class NodeImp : public NodeBinary {
    public:

        NodeImp() : NodeBinary("impl") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameters[0]->evaluate(tuple) == 0 || parameters[1]->evaluate(tuple);
        }
    };

    //-------------------------------------

    class NodeAdd : public NodeNAry {
    public:

        NodeAdd() : NodeNAry("add") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int nb = 0;
            for(unsigned int i = 0 ; i < parameters.size() ; i++)
                nb += parameters[i]->evaluate(tuple);
            return nb;
        }
    };

    class NodeMult : public NodeNAry {
    public:

        NodeMult() : NodeNAry("mult") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int nb = 1;
            for(unsigned int i = 0 ; i < parameters.size() ; i++)
                nb *= parameters[i]->evaluate(tuple);
            return nb;
        }
    };

    class NodeMin : public NodeNAry {
    public:

        NodeMin() : NodeNAry("min") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int nb = parameters[0]->evaluate(tuple);
            for(unsigned int i = 1 ; i < parameters.size() ; i++) {
                int v = parameters[i]->evaluate(tuple);
                if(v < nb) nb = v;
            }
            return nb;
        }
    };

    class NodeMax : public NodeNAry {
    public:

        NodeMax() : NodeNAry("max") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int nb = parameters[0]->evaluate(tuple);
            for(unsigned int i = 1 ; i < parameters.size() ; i++) {
                int v = parameters[i]->evaluate(tuple);
                if(v > nb) nb = v;
            }
            return nb;
        }
    };

    class NodeEQ : public NodeNAry {
    public:

        NodeEQ() : NodeNAry("eq") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int nb = parameters[0]->evaluate(tuple);
            for(unsigned int i = 1 ; i < parameters.size() ; i++) {
                if(nb != parameters[i]->evaluate(tuple))
                    return 0;
            }
            return 1;
        }
    };

    class NodeAnd : public NodeNAry {
    public:

        NodeAnd() : NodeNAry("and") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            for(unsigned int i = 0 ; i < parameters.size() ; i++)
                if(!parameters[i]->evaluate(tuple))
                    return 0;
            return 1;
        }
    };

    class NodeOr : public NodeNAry {
    public:

        NodeOr() : NodeNAry("or") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            for(unsigned int i = 0 ; i < parameters.size() ; i++)
                if(parameters[i]->evaluate(tuple)) {
                    return 1;
                }
            return 0;
        }
    };

    class NodeXor : public NodeNAry {
    public:

        NodeXor() : NodeNAry("xor") {}


        int evaluate(std::map<std::string, int> &tuple) override {

            int nb = !parameters[0]->evaluate(tuple) != !parameters[1]->evaluate(tuple);

            for(unsigned int i = 2 ; i < parameters.size() ; i++)
                nb = ((!nb) != parameters[i]->evaluate(tuple));
            return nb;
        }
    };

    class NodeIf : public NodeNAry {
    public:

        NodeIf() : NodeNAry("if") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int nb = parameters[0]->evaluate(tuple);
            if(nb) return parameters[1]->evaluate(tuple);
            return parameters[2]->evaluate(tuple);
        }
    };


    class NodeIff : public NodeNAry {
    public:

        NodeIff() : NodeNAry("iff") {
        }


        int evaluate(std::map<std::string, int> &tuple) override {
            assert(parameters.size() == 2); // TODO if greater!!
            int nb = parameters[0]->evaluate(tuple);
            return (nb) ? parameters[1]->evaluate(tuple) : !parameters[1]->evaluate(tuple);
        }
    };

    class NodeSet : public NodeNAry {
    public :
        NodeSet() : NodeNAry("set") {}


        // std::map<std::string, int> &tuple
        int evaluate(std::map<std::string, int> &) override {
            throw std::runtime_error("can't evaluate set");
        }
    };


    class NodeIn : public NodeBinary {
    protected :

        std::vector<int> set;
    public :
        NodeIn() : NodeBinary("in") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int nb = parameters[0]->evaluate(tuple);
            set.clear();
            NodeSet *nodeSet;
            if((nodeSet = dynamic_cast<NodeSet *>(parameters[1])) == NULL)
                throw std::runtime_error("intension constraint : in requires a set as second parameter");
            for(unsigned int i = 0 ; i < nodeSet->parameters.size() ; i++)
                set.push_back(nodeSet->parameters[i]->evaluate(tuple));
            return find(set.begin(), set.end(), nb) != set.end();
        }
    };
}
#endif //XCSP3PARSER_XCSP3TREENODE_H
