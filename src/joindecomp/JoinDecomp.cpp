#include "JoinDecomp.h"


void JoinDecomp::setRoot(JoinDecomp* root_){
  root = root_;
}

JoinDecomp* JoinDecomp::getRoot(){
  return root;
}

void JoinDecomp::setChildLeft(JoinDecomp* child){
  childLeft = child;
}

void JoinDecomp::setChildRight(JoinDecomp* child){
  childRight = child;
}

JoinDecomp* JoinDecomp::left(){
  return childLeft;
}

JoinDecomp* JoinDecomp::right(){
  return childRight;
}

void JoinDecomp::setVariables(vector<string> variables_){
  variables = variables_;
}

void JoinDecomp::setTuples(vector<vector<int>> tuples_){
  tuples = tuples_;
}

void JoinDecomp::clearVariables(){
  variables.clear();
}

void JoinDecomp::clearTuples(){
  tuples.clear();
}

vector<string> JoinDecomp::getVariables(){
  return variables;
}

vector<vector<int>> JoinDecomp::getTuples(){
  return tuples;
}


void JoinDecomp::naiveJoin(){

  if((childLeft == NULL) & (childRight == NULL)){
    return;
  }
  if(childRight == NULL){
    variables.clear();
    tuples.clear();
    variables = childLeft->getVariables();
    tuples = childLeft->getTuples();
    return;
  }
  if(childLeft == NULL){
    variables.clear();
    tuples.clear();
    variables = childRight->getVariables();
    tuples = childRight->getTuples();
    return;
  }

  variables.clear();
  tuples.clear();
  // map indices of common variables in childLeft to childRight
  map<int, int> m;
  int i1 = 0;
  for(auto var1: childLeft->getVariables()){
    int i2 = 0;
    for(auto var2: childRight->getVariables()){
      if((var1) == (var2)){
        m.insert(std::pair<int, int>(i1, i2));
      }
      i2++;
    }
    i1++;
  }
  // build vars:
  for(auto var1: childRight->getVariables()){
    variables.push_back(var1);
  }
  int i = 0;
  for(auto var2: childLeft->getVariables()){
    if(m.find(i) == m.end()){
      variables.push_back(var2);
    }
    i++;
  }

  // take each tuple with matching var values:
  for(auto tuple_1: childLeft->getTuples()){
    for(auto tuple_2: childRight->getTuples()){
      bool flag = true;
      for(auto iter: m){
        if(tuple_1.at(iter.first) != tuple_2.at(iter.second)){
          flag = false;
        }
      }
      if(flag){
        // if match, build tuple:
        vector<int> newTuple;
        // add all from tuple_2:
        for(auto val: tuple_2){
          newTuple.push_back(val);
        }
        // add all not in tuple 2:
        int i = 0;
        for(auto val: tuple_1){
          if(m.find(i) == m.end()){
            newTuple.push_back(val);
          }
          i++;
        }
        tuples.push_back(newTuple);
      }
    }
  }
}


void JoinDecomp::vBar(JoinDecomp * startJD, vector<string> * vars){
  if(this == startJD){
    return;
  }
  for(auto var:variables){
    if(std::find(vars->begin(), vars->end(), var) == vars->end()){
      vars->push_back(var);
    }
  }
  if(childLeft != NULL){
    childLeft->vBar(startJD, vars);
  }
  if(childRight != NULL){
    childRight->vBar(startJD, vars);
  }
}


void JoinDecomp::proj(){
  // THIS CAN LEED TO DUPLICATES
  // CONSIDER CHECKING + REMOVING
  vector<string> vars;
  if(root == NULL){
    std::cerr<<"Warning: JoinDecomp::proj() null pointer root. Projection ignored.\n";
    return;
  }
  if(this == root){
    return;
  }
  root->vBar(this, &vars);

  vector<int> toRemove;
  int i = 0;
  for(auto var:variables){
    if(std::find(vars.begin(), vars.end(), var) == vars.end()){
      toRemove.push_back(i);
    }
    i++;
  }

  i = 0;
  vector<string>::iterator var = variables.begin();
  while(var != variables.end()){
    if(std::find(toRemove.begin(), toRemove.end(), i) != toRemove.end()){
      var = variables.erase(var);
    }
    else{
      ++var;
    }
    i++;
  }

  for(vector<vector<int>>::iterator tuple = tuples.begin(); tuple != tuples.end(); ++tuple){

    int i = 0;
    vector<int>::iterator val = tuple->begin();
    while(val != tuple->end()){
      if(std::find(toRemove.begin(), toRemove.end(), i) != toRemove.end()){
        val = tuple->erase(val);
      }
      else{
        ++val;
      }
      i++;
    }
  }
}


vector<pair<vector<string>, vector<vector<int>>>> JoinDecomp::getBaseConstraints(){
  vector<pair<vector<string>, vector<vector<int>>>> constrVector;

  if((childLeft == NULL)&(childRight == NULL)){
    constrVector.push_back(pair<vector<string>, vector<vector<int>>>(variables, tuples));
    return constrVector;
  }
  if(childRight == NULL){
    return childLeft->getBaseConstraints();
  }
  if(childLeft == NULL){
    return childRight->getBaseConstraints();
  }
  vector<pair<vector<string>, vector<vector<int>>>> constrVector2;

  constrVector = childLeft->getBaseConstraints();
  constrVector2 = childRight->getBaseConstraints();

  constrVector.insert(constrVector.end(), constrVector2.begin(), constrVector2.end());

  return constrVector;

}


void JoinDecomp::prune(){
  vector<pair<vector<string>, vector<vector<int>>>> fullConstraints = root->getBaseConstraints();
  // For each tuple in this JD:
  vector<vector<int>>::iterator tuple = tuples.begin();
  while(tuple != tuples.end()){
    bool tupleFineFlag = true;
    // Check each constraint for violation:
    for(auto constraint: fullConstraints){
      bool constrSatisFlag = false;
      vector<string> conVars = constraint.first;
      vector<vector<int>> conTuples = constraint.second;
      // Map from current tuple in this JD to constraint:
      map<int, int> m;
      int i1 = 0;
      for(auto var1: variables){
        int i2 = 0;
        for(auto var2: conVars){
          if((var1) == (var2)){
            m.insert(std::pair<int, int>(i1, i2));
          }
          i2++;
        }
        i1++;
      }

      // Check current tuple matches at least one tuple on constraint:
      for(auto conTuple: conTuples){
        bool tupleMatchFlag = true;
        for(auto mIter: m){
          if(tuple->at(mIter.first)!=conTuple.at(mIter.second)){
            tupleMatchFlag = false;
          }
        }
        if(tupleMatchFlag){
          constrSatisFlag = true;
          break;
        }
      }

      // If constraint not satisfied, flag:
      if(!constrSatisFlag){
        tupleFineFlag = false;
        break;
      }
    }

    // If tuple contradicts a constraint, remove:
    if(!tupleFineFlag){
      tuple = tuples.erase(tuple);
    }
    else{
      ++tuple;
    }
  }
}


void JoinDecomp::solve(){
  if(childLeft != NULL){
    childLeft->solve();
  }
  if(childRight != NULL){
    childRight->solve();
  }
  naiveJoin();
  proj();
  prune();
}
