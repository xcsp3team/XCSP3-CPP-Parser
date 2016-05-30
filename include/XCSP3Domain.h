/*=============================================================================
 * parser for CSP instances represented in XCSP3 Format
 * 
 * Copyright (c) 2015 xcp3.org (contact <at> xcsp3.org)
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

#ifndef XDOMAIN_H
#define    XDOMAIN_H

#include<vector>
#include <iostream>

using namespace std;
namespace XCSP3Core {

    class XIntegerEntity {
    public :
        virtual int width() = 0;
        virtual int minimum() = 0;
        virtual int maximum() = 0;
        virtual void print(std::ostream &O) const = 0;
        friend ostream &operator<<(ostream &f, const XIntegerEntity &ie);
        virtual ~XIntegerEntity() { }

    };

    class XIntegerValue : public XIntegerEntity {
    public:
        int value;


        XIntegerValue(int v) : value(v) { }


        int width() { return 1; }


        int minimum() { return value; }


        int maximum() { return value; }


        void print(std::ostream &O) const { O << value << " "; }


        virtual ~XIntegerValue() { }
    };


    class XIntegerInterval : public XIntegerEntity {
    public :
        int min, max;


        XIntegerInterval(int inf, int sup) : min(inf), max(sup) { }


        int width() { return max - min + 1; }


        int minimum() { return min; }


        int maximum() { return max; }


        void print(std::ostream &O) const { O << min << ".." << max << " "; }


        virtual ~XIntegerInterval() { }
    };




    class XDomain {

    };

    class XDomainInteger : public XDomain {
//        friend class XMLParser;
    protected :
        int size;


        void addEntity(XIntegerEntity *e) {
            values.push_back(e);
            size += e->width();
        }


    public:
        std::vector<XIntegerEntity *> values;


        XDomainInteger() : size(0) { }


        int nbValues() {
            return size;
        }


        int minimum() {
            return values[0]->minimum();
        }


        int maximum() {
            return values[values.size() - 1]->maximum();
        }


        int isInterval() {
            return size == maximum() - minimum() + 1;
        }


        void addValue(int v) {
            addEntity(new XIntegerValue(v));
        }


        void addInterval(int min, int max) {
            addEntity(new XIntegerInterval(min, max));
        }


        friend ostream &operator<<(ostream &f, const XDomainInteger &d);


        virtual ~XDomainInteger() {
            for (XIntegerEntity * xi : values)
                delete xi;
        }

    };
}


#endif	/* XDOMAIN_H */

