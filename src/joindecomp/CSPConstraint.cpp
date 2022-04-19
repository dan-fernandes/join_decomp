#include "CSPConstraint.h"

CSPConstraint::CSPConstraint(string id_, CSPVariable* variable){
  id = id_;
  scope.push_back(variable);

}

CSPConstraint::CSPConstraint(string id_, vector<CSPVariable*> variables){
  id = id_;
  scope = variables;

}

string CSPConstraint::getId(){
  return id;
}

bool CSPConstraint::isSatisfied(int assignment){
  vector<vector<int>>::iterator iter;

    if(1 != getScopeSize()){
      std::cerr << "Warning: CSP:Constraint::isSatisfied called with assignment of incorrect size\n";
      return false;
    }

  for(iter = tuples.begin(); iter != tuples.end(); ++iter){
    if ((*iter).at(0) == assignment){
      return true;
    }
  }
  return false;
}

bool CSPConstraint::isSatisfied(vector<int> assignment){
  vector<vector<int>>::iterator iter;

  if(assignment.size() != getScopeSize()){
    std::cerr << "Warning: CSP:Constraint::isSatisfied called with assignment of incorrect size\n";
    return false;
  }

  for(iter = tuples.begin(); iter != tuples.end(); ++iter){
    if(std::equal((*iter).begin(), (*iter).end(), assignment.begin())){
      return true;
    }
  }
  return false;
}

void CSPConstraint::addTuple(vector<int> tuple){

  if(tuple.size() == getScopeSize()){
    tuples.push_back(tuple);
  }
  else{
    std::cerr << "Warning: CSPConstraint::addTuple called with tuple of incorrect size. Ignored\n";
  }
}

void CSPConstraint::addTuples(vector<vector<int>> tuples_){
  vector<vector<int>>::iterator iter;
  for(iter = tuples_.begin(); iter != tuples_.end(); ++iter){
    tuples.push_back(*iter);
  }
}

vector<int> CSPConstraint::getTuple(int index){
  return tuples.at(index);
}
// Not protected:
vector<vector<int>> CSPConstraint::getTuples(){
  return tuples;
}

int CSPConstraint::getNumberTuples(){
  return tuples.size();
}

vector<CSPVariable*> CSPConstraint::getScopeVariables(){
  return scope;
}
/*
bool CSPConstraint::inScope(CSPVariable variable){
  vector<CSPVariable>::iterator iter;
  for(iter = scope.begin(); iter != scope.end(); ++iter){
    if(&(*iter) == &variable){
      return true;
    }
  }
  return false;
}
*/
bool CSPConstraint::inScope(string variableId){
  vector<CSPVariable*>::iterator iter;
  for(iter = scope.begin(); iter != scope.end(); ++iter){
    if((*iter)->getId() == variableId){
      return true;
    }
  }
  return false;
}

int CSPConstraint::getScopeSize(){
  return scope.size();
}
