#include "XCSP3JoinDecompCallbacks.h"



using namespace XCSP3Core;

XCSP3JoinDecompCallbacks::XCSP3JoinDecompCallbacks(vector<CSPVariable> * instanceVariables_, vector<CSPConstraint> * instanceConstraints_) : XCSP3CoreCallbacks(), canonize(true) {
  instanceVariables = instanceVariables_;
  instanceConstraints = instanceConstraints_;
}


template<class T>
void displayList(vector<T> &list, string separator = " ") {
    if(list.size() > 8) {
        for(int i = 0; i < 3; i++)
            cout << list[i] << separator;
        cout << " ... ";
        for(unsigned int i = list.size() - 4; i < list.size(); i++)
            cout << list[i] << separator;
        cout << endl;
        return;
    }
    for(unsigned int i = 0; i < list.size(); i++)
        cout << list[i] << separator;
    cout << endl;
}


void displayList(vector<XVariable *> &list, string separator = " ") {
    if(list.size() > 8) {
        for(int i = 0; i < 3; i++)
            cout << list[i]->id << separator;
        cout << " ... ";
        for(unsigned int i = list.size() - 4; i < list.size(); i++)
            cout << list[i]->id << separator;
        cout << endl;
        return;
    }
    for(unsigned int i = 0; i < list.size(); i++)
        cout << list[i]->id << separator;
    cout << endl;
}

CSPVariable* XCSP3JoinDecompCallbacks::getInstanceVarById(string id){
  vector<CSPVariable>::iterator iter;

  for(iter = instanceVariables->begin(); iter != instanceVariables->end(); ++iter){
    if( (*iter).getId() == id ){
      return &(*iter);
    }
  }

}

string XCSP3JoinDecompCallbacks::generateId(string id){
  // Ensures unique id (probably):
  // string id_out;
  // id_out = (to_string( (instanceConstraints->size() ))) + id;
  // id = id + id_out;
  string foo;
  foo = (to_string( (instanceConstraints->size() )));
  //id = id +  foo;
  return foo;
  //return id_out;
}


void XCSP3JoinDecompCallbacks::addXVarConstraint(string id, vector<XVariable*> constrVariables, vector<vector<int>> tuples){
  string newId = generateId(id);

  vector<XVariable*>::iterator iter;

  vector<CSPVariable*> cspVars;

  for(iter = constrVariables.begin(); iter != constrVariables.end(); ++iter){
    cspVars.push_back(getInstanceVarById((*iter)->id));
  }

  CSPConstraint constr(newId, cspVars);
  constr.addTuples(tuples);
  instanceConstraints->push_back(constr);

}

void XCSP3JoinDecompCallbacks::addXVarConstraint(string id, vector<CSPVariable*> constrVariables, vector<vector<int>> tuples){
  string newId = generateId(id);

  CSPConstraint constr(newId, constrVariables);
  constr.addTuples(tuples);
  instanceConstraints->push_back(constr);

}



void XCSP3JoinDecompCallbacks::beginInstance(InstanceType type) {
    //cout << "Start Instance - type=" << type << endl;
}


void XCSP3JoinDecompCallbacks::endInstance() {
    //cout << "End SAX parsing " << endl;
}


void XCSP3JoinDecompCallbacks::beginVariables() {
    //cout << " start variables declaration" << endl;
}


void XCSP3JoinDecompCallbacks::endVariables() {
    //cout << " end variables declaration" << endl << endl;
}


void XCSP3JoinDecompCallbacks::beginVariableArray(string id) {
    //cout << "    array: " << id << endl;
}


void XCSP3JoinDecompCallbacks::endVariableArray() {
}


void XCSP3JoinDecompCallbacks::beginConstraints() {
    //cout << " start constraints declaration" << endl;
}


void XCSP3JoinDecompCallbacks::endConstraints() {
    //cout << "\n end constraints declaration" << endl << endl;
}


void XCSP3JoinDecompCallbacks::beginGroup(string id) {
    //cout << "   start group of constraint " << id << endl;
}


void XCSP3JoinDecompCallbacks::endGroup() {
    //cout << "   end group of constraint" << endl;
}


void XCSP3JoinDecompCallbacks::buildVariableInteger(string id, int minValue, int maxValue) {
    CSPVariable var(id, minValue, maxValue);
    instanceVariables->push_back(var);
}


void XCSP3JoinDecompCallbacks::buildVariableInteger(string id, vector<int> &values) {
    CSPVariable var(id, values);
    instanceVariables->push_back(var);

}


void XCSP3JoinDecompCallbacks::buildConstraintExtension(string id, vector<XVariable *> list, vector<vector<int>> &tuples, bool support, bool hasStar) {
     // cout << "\n    extension constraint : " << id << endl;
     // cout << "        " << (support ? "support" : "conflict") << " arity: " << list.size() << " nb tuples: " << tuples.size() << " star: " << hasStar << endl;
     // cout << "        ";
     // displayList(list);

     addXVarConstraint(id, list, tuples);

}




void XCSP3JoinDecompCallbacks::buildConstraintExtension(string id, XVariable *variable, vector<int> &tuples, bool support, bool hasStar) {
    // cout << "\n    extension constraint with one variable: " << id << endl;
    // cout << "        " <<(*variable) << " "<< (support ? "support" : "conflict") << " nb tuples: " << tuples.size() << " star: " << hasStar << endl;
    // cout << endl;
    //
    vector<XVariable*> list;
    vector<vector<int>> tuples_;
    list.push_back(variable);
    tuples_.push_back(tuples);

    addXVarConstraint(id, list, tuples_);
}


// string id, vector<XVariable *> list, bool support, bool hasStar
void XCSP3JoinDecompCallbacks::buildConstraintExtensionAs(string id, vector<XVariable *> list, bool, bool) {
    // cout << "\n    extension constraint similar as previous one: " << id << endl;

    addXVarConstraint(id, list, (instanceConstraints->back()).getTuples());

}
void XCSP3JoinDecompCallbacks::buildAnnotationDecision(vector<XVariable*> &list) {
    std::cout << "       decision variables" << std::endl<< "       ";
    displayList(list);

}
