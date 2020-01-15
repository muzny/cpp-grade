#include <string>
#include <vector>
#include <experimental/filesystem> // g++ 7 includes this under experimental

#include "catch.hpp"
// include other files to be tested here
#include "JsonAutograderOutput.h"

// to refer to things on the filesystem
namespace fs = std::experimental::filesystem;


TEST_CASE("Correct files present", "[meta]") {

  JsonAutograderOutput &jao = JsonAutograderOutput::GetInstance();

  SECTION ("Required files present") {
    jao.AddTestCase("Required files present", 1);

    // what are the names of the files that they need to submit?
    std::vector<std::string> files = {"Point.h", "Point.cpp", "main.cpp", "Makefile.submission"};
    
    for (std::string filename : files) {
      bool exists = fs::is_regular_file(filename);
      REQUIRE( exists );
    }
        
    jao.UpdateTestCase("Required files present", 1, "Congrats, all required files are present!");
  }

  SECTION("Compiles and creates appropriate executables") {
    jao.AddTestCase("Compiles and cleans up afterwards", 1);

    // commands to clean then compile
    system("make -f Makefile.submission clean");
    system("make -f Makefile.submission");

    // what executables should they produce?
    std::vector<std::string> executables = {"main"};
    
    for (std::string filename : executables) {
      bool exists = fs::is_regular_file(filename);
      REQUIRE( exists );
    }

    // clean the system
    system("make -f Makefile.submission clean");

    // what files should not exist at this point (that are likely too exist)
    std::vector<std::string> gotten_rid_of = {"main", "Point.o", "main.o"};
    
    for (std::string filename : executables) {
      bool exists = fs::is_regular_file(filename);
      REQUIRE( ! exists );
    }

    jao.UpdateTestCase("Compiles and cleans up afterwards", 1, "Congrats, all required executables are and cleaned when you're done!");
  }

}
