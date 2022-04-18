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
