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
#ifndef COSOCO_XCSP3JoinDecompCallbacks_H
#define COSOCO_XCSP3JoinDecompCallbacks_H

#include <XCSP3Tree.h>
#include "XCSP3CoreCallbacks.h"
#include "XCSP3Variable.h"
#include "CSPVariable.h"
#include "CSPConstraint.h"


namespace XCSP3Core {

    class XCSP3JoinDecompCallbacks : public XCSP3CoreCallbacks {
    private:
      vector<CSPVariable> * instanceVariables;
      vector<CSPConstraint> * instanceConstraints;

      // Gets the CSPVariable with id:
      CSPVariable * getInstanceVarById(string id);

      // returns a string with unique id (assuming all id's generated from this function):
      string generateId(string id);

      // adds to instanceConstraints vector, from non-unique id, xvars, tuples:
      void addXVarConstraint(string id, vector<XVariable*> constrVariables, vector<vector<int>> tuples);
      // void addXVarConstraint(string id, vector<CSPVariable*> constrVariables, vector<vector<int>> tuples);

      void invertTuples(vector<XVariable*> constrVariables, vector<vector<int>> tuples);
    public:
        XCSP3JoinDecompCallbacks(vector<CSPVariable> * instanceVariables_, vector<CSPConstraint> * instanceConstraints_);

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

        void buildVariableInteger(string id, int minValue, int maxValue) override;

        void buildVariableInteger(string id, vector<int> &values) override;

        void buildConstraintExtension(string id, vector<XVariable *> list, vector<vector<int>> &tuples, bool support, bool hasStar) override;

        void buildConstraintExtension(string id, XVariable *variable, vector<int> &tuples, bool support, bool hasStar) override;

        void buildConstraintExtensionAs(string id, vector<XVariable *> list, bool support, bool hasStar) override;

    //     void buildAnnotationDecision(vector<XVariable*> &list) override;
         bool canonize;
    };


}

#endif //COSOCO_XCSP3JoinDecompCallbacks_H
