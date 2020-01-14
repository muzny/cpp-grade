#include <vector>
// to produce JSON
#include "json.hpp"
using json = nlohmann::json;

struct TestCase {
  std::string name;
  double score;
  std::string output;

};

class JsonAutograderOutput {
public:
  static JsonAutograderOutput& GetInstance() {
    static JsonAutograderOutput instance;

    return instance;
  }

  void AddTestCase(std::string name);

  void UpdateTestCase(std::string name, double score, std::string output);


  void Write(std::string path);

  // Delete the methods we don't want
  JsonAutograderOutput(JsonAutograderOutput const&) = delete; // copy constructor
  void operator=(JsonAutograderOutput const&) = delete; // assignment operator

private:
  JsonAutograderOutput();  // private constructor


  std::vector<TestCase *> tests_;

};

