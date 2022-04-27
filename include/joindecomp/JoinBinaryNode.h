#ifndef JOIN_BINARY_NODE_H
#define   JOIN_BINARY_NODE_H

#include <vector>

using std::vector;

// class JoinBinaryNode;

class JoinBinaryNode{
private:
  JoinBinaryNode* childLeft = NULL;
  JoinBinaryNode* childRight = NULL;

  // Used for construction:
  vector<JoinBinaryNode*> tempChildren;


public:
  void setLeft(JoinBinaryNode * child);
  void setRight(JoinBinaryNode * child);

  JoinBinaryNode * left();
  JoinBinaryNode * right();

  void addTempChild(JoinBinaryNode* child);

  void setTempChildren(vector<JoinBinaryNode*> children);

  void clearTempChildren();

  JoinBinaryNode* getTempChild(int i);
  vector<JoinBinaryNode*> getTempChildren();

};

#endif
