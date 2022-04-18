#ifndef JOIN_BINARY_NODE_H
#define   JOIN_BINARY_NODE_H

class JoinBinaryNode;

class JoinBinaryNode{
private:
  JoinBinaryNode* childLeft;
  JoinBinaryNode* childRight;

public:
  void setLeft(JoinBinaryNode * child);
  void setRight(JoinBinaryNode * child);

  JoinBinaryNode * left();
  JoinBinaryNode * right();
};

#endif
