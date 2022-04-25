#ifndef JOIN_DECOMP_BUILDER_H
#define   JOIN_DECOMP_BUILDER_H

#include <map>
#include <string>

#include "CSPVariable.h"
#include "CSPConstraint.h"
#include "XCSP3JoinDecompCallbacks.h"
#include "JoinDecomp.h"
#include "XCSP3CoreParser.h"

#include "Globals.h"
#include "Hypergraph.h"
#include "Superedge.h"
#include "Hyperedge.h"
#include "Hypertree.h"
#include "DetKDecomp.h"


using std::string;
using std::map;
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

  void buildHG(HypergraphSharedPtr HG);

  void getHTNodeConstraints(vector<CSPConstraint*> * constrVec, HypertreeSharedPtr HT);

  JoinBinaryNode* computeSubJ(map<JoinBinaryNode*, CSPConstraint*>* q, JoinBinaryNode* root, vector<CSPConstraint*> constrVec);

  JoinBinaryNode* cleanJD(map<JoinBinaryNode*, CSPConstraint*>* q, JoinBinaryNode* root);

  // Converts from HT ot JD:
  JoinBinaryNode* convertHT(map<JoinBinaryNode*, CSPConstraint*> * q, HypertreeSharedPtr HT);

  // Takes all nodes in JoinBinaryNode's tempChildren and binarises them
  // In here rather than JoinBinaryNode to allow heuristic methods of bianrisation
  void binarise(JoinBinaryNode * root);

  void buildJoinDecomp(JoinDecomp * jd);

  // void addVariable(string id, int minVal, int maxVal);
  // void addVariables(string id, vector<int> values);
  //
  // void addConstraint(string id, string varId);
  // void addConstraints(string id, vector<string> varIds);
};


#endif
