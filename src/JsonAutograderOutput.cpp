#include <iostream>
#include <iomanip> // for the autograder for setw
#include <fstream>
#include <vector>
#include <map>
// to produce JSON
#include "json.hpp"
using json = nlohmann::json;

#include "JsonAutograderOutput.h"

JsonAutograderOutput::JsonAutograderOutput() {
  std::vector<TestCase *> tmp;
  tests_ = tmp;
}

void JsonAutograderOutput::AddTestCase(std::string name) {
  TestCase * tc = new TestCase();
  tc->name = name;
  tc->score = 0;
  tc->output = "";
  tests_.push_back(tc);
}


void JsonAutograderOutput::UpdateTestCase(std::string name, double score, std::string output) {
  // find the correct test case
  for (TestCase * tc : tests_) {
    if (tc->name == name) {
      tc->score = score;
      tc->output = output;
    }
  }
}

void JsonAutograderOutput::Write(std::string path) {
  std::ofstream o(path);

  json data;

  json tests;
  for (TestCase * tc : tests_) {
    json test;
    test["name"] = tc->name;
    test["score"] = tc->score;
    test["output"] = tc->output;
    tests.push_back(test);
  }


  data["tests"] = tests;

  o << std::setw(4) << data << std::endl;
}