#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest_main.h"


void printJD(JoinDecomp * jd){
  cout<<"===================="<<'\n';
  cout<<"Printing JD at: "<<jd<<'\n';
  cout<<"Variables: ";
  for(auto var: jd->getVariables()){
    cout<< var<<" ";
  }
  cout<<"\n";
  cout<<"Tuples: ";
  for(auto tuple: jd->getTuples()){
    for(auto val: tuple){
      cout<<val<<" ";
    }
    cout<<";";
  }
  cout<<"\n";
  cout<<"===================="<<'\n';
}

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
  CSPConstraint c_v_1("c_v_1", &r_v_1);
  vector<vector<int>> tuples_1 = {{1}, {3}, {7}, {8}, {13}};
  vector<vector<int>> full_tuple_1 = {{12},{1},{3},{7},{8},{13}};
  vector<int> test_tuple_1 = {7};
  c_v_1.addTuple({12});
  // This is an error case:
  c_v_1.addTuple({12,13});
  // ^^ should give warning, and be ignored
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
  vector<CSPVariable*> v = {&r_v_1, &d_v_1};
  CSPConstraint c_vs_1("c_vs_1", v);
  vector<vector<int>> tuples_2 = {{1, 6}, {3,14}, {7,2}, {8,2}, {13,1}};


  c_vs_1.addTuples(tuples_2);
  c_vs_1.addTuple({13,7});

  CHECK(c_vs_1.getId() == "c_vs_1");
  CHECK(c_vs_1.isSatisfied({1,6}) == true);
  CHECK(c_vs_1.isSatisfied({1,7}) == false);

  vector<int> test_tuple_2 = {8,2};
  vector<int> test_tuple_3 = {13,7};

  CHECK(c_vs_1.getTuple(3) == test_tuple_2);
  CHECK(c_vs_1.getTuple(5) == test_tuple_3);


  vector<vector<int>> full_tuple_2 = {{1,6},{3,14},{7,2},{8,2},{13,1},{13,7}};
  CHECK(c_vs_1.getTuples() == full_tuple_2);

  CHECK(c_vs_1.getNumberTuples() == 6);

  CHECK(c_vs_1.inScope("r_v_1") == true);
  CHECK(c_vs_1.inScope("d_v_1") == true);
  CHECK(c_vs_1.inScope("sfjiodsj") == false);
}

TEST_CASE("basic_join_decomp"){
  JoinDecomp jd_0;

  JoinDecomp jd_1;
  JoinDecomp jd_2;

  JoinDecomp jd_3;
  JoinDecomp jd_4;
  JoinDecomp jd_5;

  jd_0.setChildLeft(&jd_1);
  jd_0.setChildRight(&jd_2);
  jd_1.setChildLeft(&jd_3);
  jd_1.setChildRight(&jd_4);
  jd_2.setChildLeft(&jd_5);

  jd_0.setRoot(&jd_0);
  jd_1.setRoot(&jd_0);
  jd_2.setRoot(&jd_0);
  jd_3.setRoot(&jd_0);
  jd_4.setRoot(&jd_0);
  jd_5.setRoot(&jd_0);

  vector<string> vars_jd_3 = {"A","B"};
  vector<vector<int>> tuples_jd_3 = {{0,1},{1,0},{1,1}};


  vector<string> vars_jd_4 = {"B","C"};
  vector<vector<int>> tuples_jd_4 = {{1,2},{2,2}};

  vector<string> vars_jd_5 = {"A", "C", "D"};
  vector<vector<int>> tuples_jd_5 = {{1,2,3},{1,3,4}};

  jd_3.setVariables(vars_jd_3);
  jd_3.setTuples(tuples_jd_3);

  jd_4.setVariables(vars_jd_4);
  jd_4.setTuples(tuples_jd_4);

  jd_5.setVariables(vars_jd_5);
  jd_5.setTuples(tuples_jd_5);

  vector<vector<int>> test_t_1 = {{0,1},{1,0},{1,1}};
  CHECK(jd_3.getTuples() == test_t_1);

  jd_1.naiveJoin();
  vector<string> test_t_s_1 = {{"B","C","A"}};
  CHECK(jd_1.getVariables() == test_t_s_1);
  vector<vector<int>> test_t_3 = {{1,2,0},{1,2,1}};
  CHECK(jd_1.getTuples() == test_t_3);

  jd_3.prune();

  vector<vector<int>> test_t_2 = {{1,1}};
  CHECK(jd_3.getTuples() == test_t_2);

  vector<string> test_v_s_2 = {{"A","C","D"}};
  CHECK(jd_5.getVariables() == test_v_s_2);

  jd_5.proj();

  vector<string> test_v_s_3 = {"A","C"};
  vector<vector<int>> test_t_4 = {{1,2},{1,3}};
  CHECK(jd_5.getVariables() == test_v_s_3);
  CHECK(jd_5.getTuples() == test_t_4);

  jd_0.solve();
  vector<vector<int>> test_t_5 = {{1,2}};
  CHECK(jd_0.getTuples() == test_t_5);

}

TEST_CASE("join_decomp_builder"){
  JoinDecompBuilder jdb;

  JoinDecomp jd;

  jdb.loadXCSP("../samples/MaxCSP-connell.xml");

  CHECK(jdb.getNumVariables() == 13);
  CHECK(jdb.getNumConstraints() == 15);

  jdb.buildJoinDecomp(&jd);

}
