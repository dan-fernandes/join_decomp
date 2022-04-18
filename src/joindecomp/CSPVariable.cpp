#include "CSPVariable.h"

CSPVariable::CSPVariable(string id_, int minVal_, int maxVal_){
  id = id_;

  minVal = minVal_;
  maxVal = maxVal_;

  rangeVarFlag = true;

}

CSPVariable::CSPVariable(string id_, vector<int> domainValues_){
id = id_;

domainValues = domainValues_;

rangeVarFlag = false;

}

string CSPVariable::getId(){
  return id;
}

bool CSPVariable::inDomain(int value){
  // If range, check in range:
  if(rangeVarFlag){
    return (minVal <= value) and (value <= maxVal);
  }
  // Else itereate through domain:
  vector<int>::iterator iter;
  for(iter = domainValues.begin(); iter != domainValues.end(); ++iter){
    if(*iter == value){
      return true;
    }
  }
  return false;
}

int CSPVariable::getDomainSize(){
  if(rangeVarFlag){
    // Range inclusive:
    return (maxVal - minVal) + 1;
  }
  return domainValues.size();

}
