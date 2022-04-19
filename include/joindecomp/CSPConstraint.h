#ifndef CSPCONSTRAINT_H
#define    CSPCONSTRAINT_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "CSPVariable.h"

using std::string;
using std::vector;

class CSPConstraint{
private:
  string id;
  vector<CSPVariable*> scope;
  vector<vector<int>> tuples;

public:
  // Either way, internal representation is through a vector:
  CSPConstraint(string id, CSPVariable *variable);
  CSPConstraint(string id, vector<CSPVariable*>  variables);

  // Returns string id:
  string getId();

  // Check constraint is satisfied under assignment
  // Singular integer is for unary constraints:
  bool isSatisfied(int assignment);
  bool isSatisfied(vector<int> assignment);

  // Add one or multiple tuples:
  void addTuple(vector<int> tuple);
  void addTuples(vector<vector<int>> tuples);

  // Get one or all tuples:
  vector<int> getTuple(int index);
  vector<vector<int>> getTuples();

  // Get number of tuples
  int getNumberTuples();

  // Get variables or variable id's in constraint:
  vector<CSPVariable*> getScopeVariables();
  //vector<string> getScopeIds();

  // Check variables is in scope:
  //bool inScope(CSPVariable variable);
  bool inScope(string variableId);

  // Get number of variables in scope:
  int getScopeSize();
};



#endif
