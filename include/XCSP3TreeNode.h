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
#include<assert.h>

namespace XCSP3Core {



    //-------------------------------------

    class Node {
        friend class Intension;

    public:
        virtual int evaluate(std::map<std::string, int> &tuple) = 0;

        virtual void prefixe() = 0;
    };


    //-------------------------------------

    class NodeConstant : public Node {

    public:
        int val;


        NodeConstant(int v) : val(v) {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return val;
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


        void prefixe() override {
            std::cout << var;
        }
    };


    //-------------------------------------

    class NodeOperator : public Node {
    public:
        std::string op;


        NodeOperator(std::string o) : op(o) {}


        virtual void addParameter(Node *p) = 0;
    };

    class NodeUnary : public NodeOperator {
    protected:
        Node *parameter;
    public:

        NodeUnary(std::string o) : NodeOperator(o) {}


        void addParameter(Node *p) override {
            parameter = p;
        }


        void prefixe() override {
            std::cout << op << "(";
            parameter->prefixe();
            std::cout << ")";
        }

    };

    //-------------------------------------

    class NodeBinary : public NodeOperator {
    public:
        Node *parameter1, *parameter2;


        NodeBinary(std::string o) : NodeOperator(o), parameter1(NULL), parameter2(NULL) {}


        void addParameter(Node *p) override {
            if(parameter1 == NULL)
                parameter1 = p;
            else parameter2 = p;
        }


        void prefixe() override {
            std::cout << op << "(";
            parameter1->prefixe();
            std::cout << ",";
            parameter2->prefixe();
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

        void addParameter(Node *p) override {
            parameters.push_back(p);
        }


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

        NodeNeg() : NodeUnary("-") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return -parameter->evaluate(tuple);
        }
    };

    // --------------------------------------------------------------------------

    class NodeAbs : public NodeUnary {
    public:

        NodeAbs() : NodeUnary("abs") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int v = parameter->evaluate(tuple);
            return v > 0 ? v : -v;
        }
    };

    class NodeSquare : public NodeUnary {
    public:

        NodeSquare() : NodeUnary("sqr") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int v = parameter->evaluate(tuple);
            return v * v;
        }
    };

    class NodeNot : public NodeUnary {
    public:

        NodeNot() : NodeUnary("not") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int v = parameter->evaluate(tuple);
            return !v;//v ? 0 : v;
        }
    };
    // --------------------------------------------------------------------------

    class NodeSub : public NodeBinary {
    public:

        NodeSub() : NodeBinary("sub") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameter1->evaluate(tuple) - parameter2->evaluate(tuple);
        }
    };

    class NodeDiv : public NodeBinary {
    public:

        NodeDiv() : NodeBinary("div") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameter1->evaluate(tuple) / parameter2->evaluate(tuple);
        }
    };

    class NodeMod : public NodeBinary {
    public:

        NodeMod() : NodeBinary("mod") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameter1->evaluate(tuple) % parameter2->evaluate(tuple);
        }
    };

    class NodePow : public NodeBinary {
    public:

        NodePow() : NodeBinary("pow") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return pow(parameter1->evaluate(tuple), parameter2->evaluate(tuple));
        }
    };

    class NodeDist : public NodeBinary {
    public:

        NodeDist() : NodeBinary("dist") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int v = parameter1->evaluate(tuple) - parameter2->evaluate(tuple);
            return v > 0 ? v : -v;
        }
    };

    class NodeLE : public NodeBinary {
    public:

        NodeLE() : NodeBinary("le") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameter1->evaluate(tuple) <= parameter2->evaluate(tuple);
        }
    };

    class NodeLT : public NodeBinary {
    public:

        NodeLT() : NodeBinary("lt") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameter1->evaluate(tuple) < parameter2->evaluate(tuple);
        }
    };

    class NodeGE : public NodeBinary {
    public:

        NodeGE() : NodeBinary("ge") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameter1->evaluate(tuple) >= parameter2->evaluate(tuple);
        }
    };

    class NodeGT : public NodeBinary {
    public:

        NodeGT() : NodeBinary("gt") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameter1->evaluate(tuple) > parameter2->evaluate(tuple);
        }
    };

    class NodeNE : public NodeBinary {
    public:

        NodeNE() : NodeBinary("ne") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameter1->evaluate(tuple) != parameter2->evaluate(tuple);
        }
    };

    class NodeImp : public NodeBinary {
    public:

        NodeImp() : NodeBinary("impl") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            return parameter1->evaluate(tuple) == 0 || parameter2->evaluate(tuple);
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


        int evaluate(std::map<std::string, int> &tuple) override {
            throw std::runtime_error("can't evaluate set");
        }
    };


    class NodeIn : public NodeBinary {
    protected :

        std::vector<int> set;
    public :
        NodeIn() : NodeBinary("in") {}


        int evaluate(std::map<std::string, int> &tuple) override {
            int nb = parameter1->evaluate(tuple);
            set.clear();
            NodeSet *nodeSet;
            if((nodeSet = dynamic_cast<NodeSet *>(parameter2)) == NULL)
                throw std::runtime_error("intension constraint : in requires a set as second parameter");
            for(unsigned int i = 0 ; i < nodeSet->parameters.size() ; i++)
                set.push_back(nodeSet->parameters[i]->evaluate(tuple));
            return find(set.begin(), set.end(), nb) != set.end();
        }
    };
}
#endif //XCSP3PARSER_XCSP3TREENODE_H
