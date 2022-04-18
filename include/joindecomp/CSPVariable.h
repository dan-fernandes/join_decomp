#ifndef CSPVARIABLE_H
#define    CSPVARIABLE_H


#include <vector>
#include <string>

using std::string;
using std::vector;

class CSPVariable{
private:
  // String id of variables:
  string id;
  // Domain is defines by a either a range, or vector of ints
  // This is abstracted by the get and and in functions:
  vector<int> domainValues;
  int minVal, maxVal;

  // If variable is defined over a range, flag true:
  bool rangeVarFlag;

public:

  CSPVariable(string id_, int minVal_, int maxVal_);
  CSPVariable(string id_, vector<int> domainValues_);

  // Ge the id of the variables:
  string getId();

  // Check value is in domain:
  bool inDomain(int value);

  // Returns number of elements in domain:
  int getDomainSize();
};


#endif
