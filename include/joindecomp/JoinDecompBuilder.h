#ifndef JOIN_DECOMP_BUILDER_H
#define   JOIN_DECOMP_BUILDER_H

#include <map>
#include <string>

#include "CSPVariable.h"
#include "CSPConstraint.h"
#include "XCSP3JoinDecompCallbacks.h"
#include "JoinDecomp.h"
#include "XCSP3CoreParser.h"

using std::string;
//using namespace XCSP3Core;

class JoinDecompBuilder{

private:
  vector<CSPVariable> variables;
  vector<CSPConstraint> constraints;


public:
  //
  // vector<CSPVariable> variables;
  // vector<CSPConstraint> constraints;

  JoinDecompBuilder();

  int getNumVariables();
  int getNumConstraints();

  int loadXCSP(string filepath);
  void buildJoinDecomp(JoinDecomp * jd);

  // void addVariable(string id, int minVal, int maxVal);
  // void addVariables(string id, vector<int> values);
  //
  // void addConstraint(string id, string varId);
  // void addConstraints(string id, vector<string> varIds);
};


#endif
