#ifndef JOIN_DECOMP_BUILDER_H
#define   JOIN_DECOMP_BUILDER_H

#include "CSPVariable.h"
#include "CSPConstraint.h"
//#include "XCSP3JoinDecompCallbacks.h"
#include "JoinDecomp.h"
//#include "XCSP3CoreParser.h"


class JoinDecompBuilder{
private:
  vector<CSPVariable> variables;
  vector<CSPConstraint> constraints;
  //XCSP3JoinDecompCallbacks cb;
  //XCSP3CoreParser parser;

public:
  JoinDecompBuilder();
  void loadXCSP(string filepath);
  void buildJoinDecomp(JoinDecomp * jd);
};


#endif
