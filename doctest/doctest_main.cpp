#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest_main.h"

TEST_CASE("variables"){
  // Test range variable:
  CSPVariable r_v_1("r_v_1", 0, 13);

  CHECK(r_v_1.getId() == "r_v_1");
  CHECK(r_v_1.inDomain(6) == true);
  CHECK(r_v_1.inDomain(-3298) == false);
  CHECK(r_v_1.inDomain(42910) == false);
  CHECK(r_v_1.inDomain(13) == true);
  CHECK(r_v_1.getDomainSize() == 14);

  // Test domain variable:
  vector<int> d = {1,2,3,6,7,14,32};
  CSPVariable d_v_1("d_v_1", d);

  CHECK(d_v_1.getId() == "d_v_1");
  CHECK(d_v_1.inDomain(6) == true);
  CHECK(d_v_1.inDomain(-3298) == false);
  CHECK(d_v_1.inDomain(42910) == false);
  CHECK(d_v_1.inDomain(32) == true);
  CHECK(d_v_1.getDomainSize() == 7);

}


TEST_CASE("constraints"){
  CSPVariable r_v_1("r_v_1", 0, 13);
  vector<int> d = {1,2,3,6,7,14,32};
  CSPVariable d_v_1("d_v_1", d);

  // Test single-variable constructor
  CSPConstraint c_v_1("c_v_1", r_v_1);
  vector<vector<int>> tuples_1 = {{1}, {3}, {7}, {8}, {13}};
  vector<vector<int>> full_tuple_1 = {{12},{1},{3},{7},{8},{13}};
  vector<int> test_tuple_1 = {7};
  c_v_1.addTuple({12});
  c_v_1.addTuple({12,13});
  CHECK(c_v_1.isSatisfied(12) == true);
  CHECK(c_v_1.isSatisfied(13) == false);
  c_v_1.addTuples(tuples_1);
  CHECK(c_v_1.isSatisfied(12) == true);
  CHECK(c_v_1.isSatisfied(13) == true);

  CHECK(c_v_1.getTuple(3) == test_tuple_1);
  CHECK(c_v_1.getTuples() == full_tuple_1);

  CHECK(c_v_1.getId() == "c_v_1");

  CHECK(c_v_1.getNumberTuples() == 6);
/*
  CHECK(c_v_1.getScopeVariables() == {r_v_1});
*/
  //CHECK(c_v_1.inScope(r_v_1) == true);
  //CHECK(c_v_1.inScope(d_v_1) == false);
  CHECK(c_v_1.inScope("r_v_1") == true);
  CHECK(c_v_1.inScope("d_v_1") == false);

  CHECK(c_v_1.getScopeSize() == 1);


  //Test multi-variable constructor:
  vector<CSPVariable> v = {r_v_1, d_v_1};
  CSPConstraint c_vs_1("c_vs_1", v);
  vector<vector<int>> tuples_2 = {{1, 6}, {3,14}, {7,2}, {8,2}, {13,1}};
  vector<int> test_tuple_2 = {13,7};

  c_vs_1.addTuples(tuples_2);
  c_vs_1.addTuple({13,7});
  CHECK(c_vs_1.isSatisfied({1,6}) == true);
  CHECK(c_vs_1.getTuple(5) == test_tuple_2);

}

TEST_CASE("join_decomp_builder"){
  JoinDecompBuilder jdb();
}
