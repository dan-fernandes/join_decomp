#ifndef JOIN_DECOMP_H
#define   JOIN_DECOMP_H

#include <vector>
#include <string>
#include <map>

#include "CSPConstraint.h"

using std::pair;
using std::vector;
using std::string;
using std::map;

class JoinDecomp{
private:
  JoinDecomp* root = NULL;
  JoinDecomp* childLeft = NULL;
  JoinDecomp* childRight = NULL;

  vector<string> variables;
  vector<vector<int>> tuples;


public:
  void setRoot(JoinDecomp* root_);
  JoinDecomp* getRoot();

  void setChildLeft(JoinDecomp* child);
  void setChildRight(JoinDecomp* child);

  JoinDecomp* left();
  JoinDecomp* right();

  void setVariables(vector<string> variables_);
  void setTuples(vector<vector<int>> tuples_);

  void clearVariables();
  void clearTuples();

  vector<string> getVariables();
  vector<vector<int>> getTuples();

  // naive joins from children
  // clears variables and tuples if non-leaf
  // non-recursive:
  void naiveJoin();

  // Calculates variables of rest of JD tree:
  void vBar(JoinDecomp * startJD, vector<string> * vars);

  // Projects self to v bar:
  void proj();

  // Returns base (leaf) addConstraints
  vector<pair<vector<string>, vector<vector<int>>>> getBaseConstraints();

  // Removes tuples that violate any constraint in full tree:
  void prune();

  void solve();

};


#endif
