#include "JoinDecompBuilder.h"



void printJBN(JoinBinaryNode * jbn, map<JoinBinaryNode*, CSPConstraint*> q){
  // PRINTING BIT:
  vector<JoinBinaryNode*> printVec;
  int i = 0;
  JoinBinaryNode* curNode;
  printVec.push_back(jbn);

  while(printVec.size() != i){
    curNode = printVec.at(i);
    cout << "curNode: "<<curNode;
    if(curNode->left() != NULL){
      printVec.push_back(curNode->left());
    }
    cout << " leftNode: " << curNode->right();
    if(curNode->right() != NULL){
      printVec.push_back(curNode->right());
    }
    cout << " rightNode: " << curNode->left();

    if(q.find(curNode) != q.end()){
      cout << " In map";
    }
    else{
      cout << " Not in map";
    }

    cout << '\n';

    i++;
  }
}


void printJBNTempChildren( JoinBinaryNode * jbn, map<JoinBinaryNode*, CSPConstraint*> q){
  // PRINTING BIT:
  vector<JoinBinaryNode*> printVec;
  int i = 0;
  JoinBinaryNode* curNode;
  printVec.push_back(jbn);

  while(printVec.size() != i){
    curNode = printVec.at(i);
    cout << "curNode: "<<curNode<<" tempChildren: ";
    for(auto temp: curNode->getTempChildren()){
      printVec.push_back(temp);
      cout << ' ' << temp;
    }

    if(q.find(curNode) != q.end()){
      cout << " In map";
    }
    else{
      cout << " Not in map";
    }
    cout << '\n';

    i++;
  }
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

void JoinDecompBuilder::buildHG(HypergraphSharedPtr HG){
  VertexVector vertices;
  HyperedgeSharedPtr edge;

  for(vector<CSPVariable>::iterator varIter = variables.begin(); varIter != variables.end(); ++varIter){
    vertices.push_back(std::make_shared<Vertex>(varIter->getId()));
  }

  for(vector<CSPConstraint>::iterator constrIter = constraints.begin(); constrIter != constraints.end(); ++constrIter){
    edge = std::make_shared<Hyperedge>(constrIter->getId());
    vector<CSPVariable*> scope = constrIter->getScopeVariables();
    for(vector<CSPVariable*>::iterator scopeIter = scope.begin(); scopeIter != scope.end(); ++scopeIter){

      int i = 0;

      for(vector<CSPVariable>::iterator varIter2 = variables.begin(); varIter2 != variables.end(); ++varIter2){
        if((varIter2)->getId() == (*scopeIter)->getId()){
          break;
        }
        else{
          i++;
        }
      }

      edge->add(vertices[i]);
    }
    HG->insertEdge(edge);
  }

}


void JoinDecompBuilder::getHTNodeConstraints(vector<CSPConstraint*> * constrVec, HypertreeSharedPtr HT){
  for(auto iter:HT->allLambda()){
    vector<CSPConstraint>::iterator constrIter;
    for(constrIter = constraints.begin(); constrIter != constraints.end(); ++constrIter){
      if(constrIter->getScopeSize() == iter->getNbrOfVertices()){
        bool constrFlag = true;
        for(auto iter2:iter->allVertices()){
          if(!constrIter->inScope(iter2->getName())){
            constrFlag = false;
          }
        }
        if(constrFlag){
          constrVec->push_back(&(*constrIter));
        }
      }
    }
  }
}


JoinBinaryNode* JoinDecompBuilder::computeSubJ(map<JoinBinaryNode*, CSPConstraint*>* q, JoinBinaryNode* root, vector<CSPConstraint*> constrVec){


  if(constrVec.size()>1){
    JoinBinaryNode* childLeft = new JoinBinaryNode;
    JoinBinaryNode* childRight = new JoinBinaryNode;

    root->addTempChild(childLeft);
    root->addTempChild(childRight);

    int mid = ceil(constrVec.size()/2);

    vector<CSPConstraint*> constrVecLeft(constrVec.begin(), (constrVec.begin() + mid));
    vector<CSPConstraint*> constrVecRight((constrVec.begin() + mid), constrVec.end());

    computeSubJ(q, childLeft, constrVecLeft);
    computeSubJ(q, childRight, constrVecRight);

  }
  else{

    for(auto c: (*q)){
      if( c.second == constrVec.at(0)){
        return NULL;
      }
    }


    q->insert( pair<JoinBinaryNode*, CSPConstraint*>(root, constrVec.at(0)));
  }

  return root;

}



JoinBinaryNode* JoinDecompBuilder::cleanJD(map<JoinBinaryNode*, CSPConstraint*>* q, JoinBinaryNode* root){
  // I think this causes a memory leak

  if(root->left() != NULL){
    root->setLeft(cleanJD(q,root->left()));
  }
  if(root->right() != NULL){
    root->setRight(cleanJD(q,root->right()));
  }

  if((root->left() == NULL)&(root->right() == NULL)){
    if(q->find(root) == q->end()){
      return NULL;
    }

  }
  return root;

}




JoinBinaryNode* JoinDecompBuilder::convertHT(map<JoinBinaryNode*, CSPConstraint*> * q, HypertreeSharedPtr HT){

  JoinBinaryNode * root = new JoinBinaryNode;

  vector<CSPConstraint*> constrVec;
  getHTNodeConstraints(&constrVec, HT);

  computeSubJ(q, root, constrVec);

  for(auto &child : HT->allChildren()){
    root->addTempChild(convertHT(q, child));
  }
  return root;
}





void JoinDecompBuilder::binarise(JoinBinaryNode * root){

  if(root == NULL){
    return;
  }

  root->setLeft(NULL);
  root->setRight(NULL);

  vector<JoinBinaryNode*> tempChildren = root->getTempChildren();
  for(auto iter:tempChildren){
  }

  root->clearTempChildren();
  if(tempChildren.size() > 2){
    JoinBinaryNode * child1 = new JoinBinaryNode;

    int mid = ceil(tempChildren.size()/2);

    vector<JoinBinaryNode*> popped(tempChildren.begin(), (tempChildren.begin() + mid));
    vector<JoinBinaryNode*> remaining((tempChildren.begin() + mid), tempChildren.end());
    for(auto iter: popped){
    }

    for(auto iter: remaining){
    }


    child1->setTempChildren(popped);
    root->setLeft(child1);

    if(remaining.size()>1){
      JoinBinaryNode * child2 = new JoinBinaryNode;

      child2->setTempChildren(remaining);

      root->setRight(child2);
    }
    else{
      root->setRight(remaining.at(0));
    }

  }
  else if(tempChildren.size() == 2){
    root->setLeft(tempChildren.at(0));
    root->setRight(tempChildren.at(1));
  }
  else if(tempChildren.size() == 1){
    root->setLeft(tempChildren.at(0));
  }
  binarise(root->left());
  binarise(root->right());

}

void JoinDecompBuilder::buildJoinDecomp(JoinDecomp *jd){
  HypergraphSharedPtr HG = make_shared<Hypergraph>();
  HypertreeSharedPtr HT;
  buildHG(HG);

  //DELETE THIS:
  int maxIWidth = 100;
  //DELETE IT

  HT = NULL;
  int iWidth = 0;
  while( (HT == NULL) & ((iWidth <= maxIWidth)|(maxIWidth==-1))){
    iWidth++;
    DetKDecomp Decomp(HG, iWidth, false);
    HT = Decomp.buildHypertree();
  }
  map<JoinBinaryNode*, CSPConstraint*> * q = new map<JoinBinaryNode*, CSPConstraint*>;

  JoinBinaryNode* jdn = convertHT(q, HT);

  binarise(jdn);

  cleanJD(q,jdn);
}
