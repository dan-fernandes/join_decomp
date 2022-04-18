#ifndef JOIN_DECOMP_H
#define   JOIN_DECOMP_H

#include "JoinBinaryNode.h"
#include "CSPConstraint.h"
#include <map>

using std::map;

class JoinDecomp{
private:
  JoinBinaryNode J;
  map<CSPConstraint, JoinBinaryNode> q;
};


#endif
