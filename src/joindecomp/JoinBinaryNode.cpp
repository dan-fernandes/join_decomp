#include "JoinBinaryNode.h"


void JoinBinaryNode::setLeft(JoinBinaryNode * child){
  childLeft = child;
}

void JoinBinaryNode::setRight(JoinBinaryNode * child){
  childRight = child;
}

JoinBinaryNode * JoinBinaryNode::left(){
  return childLeft;
}

JoinBinaryNode * JoinBinaryNode::right(){
  return childRight;
}

void JoinBinaryNode::addTempChild(JoinBinaryNode* child){
  tempChildren.push_back(child);
}

void JoinBinaryNode::setTempChildren(vector<JoinBinaryNode*> children){
  tempChildren = children;
}

void JoinBinaryNode::clearTempChildren(){
  tempChildren.clear();
}

JoinBinaryNode* JoinBinaryNode::getTempChild(int i){
  return tempChildren.at(i);
}

vector<JoinBinaryNode*> JoinBinaryNode::getTempChildren(){
  return tempChildren;
}
