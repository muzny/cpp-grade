#include <vector>
// to produce JSON
#include "json.hpp"
using json = nlohmann::json;

struct TestCase {
  std::string name;
  double score;
  std::string output;
  double max_score;
  std::string visibility; // visible, after_published, after_due_date

};

class JsonAutograderOutput {
public:
  static JsonAutograderOutput& GetInstance() {
    static JsonAutograderOutput instance;

    return instance;
  }

  // adds an "empty test case"
  void AddTestCase(std::string name, double max_score);


  // updates the value for a given test case
  void UpdateTestCase(std::string name, double score, std::string output);


  // writes the test case values as JSON to the given path
  void Write(std::string path);

  // Delete the methods we don't want
  JsonAutograderOutput(JsonAutograderOutput const&) = delete; // copy constructor
  void operator=(JsonAutograderOutput const&) = delete; // assignment operator

private:
  JsonAutograderOutput();  // private constructor


  std::vector<TestCase *> tests_;

};

