#include "JoinDecompBuilder.h"

JoinDecompBuilder::JoinDecompBuilder(){
  //parser(&cb);

}


int JoinDecompBuilder::getNumVariables(){
  return variables.size();
}

int JoinDecompBuilder::getNumConstraints(){
  return constraints.size();
}




int JoinDecompBuilder::loadXCSP(string filepath){
  XCSP3Core::XCSP3JoinDecompCallbacks cb(&variables, &constraints);
  XCSP3Core::XCSP3CoreParser parser(&cb);
  parser.parse(filepath.c_str());


  return 0;
}
