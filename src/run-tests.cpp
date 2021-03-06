#include <string>
#include <vector>
#include <experimental/filesystem> // g++ 7 includes this under experimental

#include "catch.hpp"
// include other files to be tested here
#include "JsonAutograderOutput.h"

// to refer to things on the filesystem
namespace fs = std::experimental::filesystem;

TEST_CASE("Unit tests run test case", "[meta]" ) {
  JsonAutograderOutput &jao = JsonAutograderOutput::GetInstance();
    
  SECTION("running 1 test") {
    jao.AddTestCase("Unit tests successfully include files", 1);
    REQUIRE( 1 == 1 ); 
    jao.UpdateTestCase("Unit tests successfully include files", 1, "This test ran successfully");
  }

  SECTION("second test case adds on") {
    jao.AddTestCase("Unit tests successfully include files # 2", 1);
    REQUIRE( 1 == 1 );
    jao.UpdateTestCase("Unit tests successfully include files # 2", 1, "This test ran successfully");
  }
}

TEST_CASE("Unit tests run test case 2", "[meta]" ) {
  JsonAutograderOutput &jao = JsonAutograderOutput::GetInstance();
    
  SECTION("running 1 test") {
    jao.AddTestCase("Unit tests earn partial credit", 2);
    REQUIRE( 1 == 1 ); 
    jao.UpdateTestCase("Unit tests earn partial credit", 1, "This test ran successfully");
  }

  SECTION("second test case adds on") {
    jao.AddTestCase("Unit tests successfully include files # 2 2", 0);
    REQUIRE( 1 == 1 );
    jao.UpdateTestCase("Unit tests successfully include files # 2 2", 0, "This test ran successfully");
  }

  SECTION("second test case adds on") {
    jao.AddTestCase("Unit tests failure test max 0 points", 0);
    REQUIRE( 1 == 2 );
    jao.UpdateTestCase("Unit tests failure test max 0 points", 0, "This test ran successfully");
  }

  SECTION("second test case adds on") {
    jao.AddTestCase("Unit tests failure test max 1 points", 1);
    REQUIRE( 1 == 2 );
    jao.UpdateTestCase("Unit tests failure test max 1 points", 0, "This test ran successfully");
  }
}



TEST_CASE("Correct files present", "[meta]") {

  JsonAutograderOutput &jao = JsonAutograderOutput::GetInstance();

  SECTION ("Required files present") {
    jao.AddTestCase("Required files present", 1);
    std::vector<std::string> files = {"Point.h", "Point.cpp", "main.cpp", "Makefile.submission"};
    
    for (std::string filename : files) {
      bool exists = fs::is_regular_file(filename);
      REQUIRE( exists );
    }
        
    jao.UpdateTestCase("Required files present", 1, "Congrats, all required files are present!");
  }

  SECTION("Compiles and creates appropriate executables") {
    jao.AddTestCase("Compiles and cleans up afterwards", 1);

    system("make -f Makefile.submission clean");
    system("make -f Makefile.submission");
    std::vector<std::string> executables = {"main"};
    
    for (std::string filename : executables) {
      bool exists = fs::is_regular_file(filename);
      REQUIRE( exists );
    }

    system("make -f Makefile.submission clean");

    std::vector<std::string> gotten_rid_of = {"main", "Point.o", "main.o"};
    
    for (std::string filename : executables) {
      bool exists = fs::is_regular_file(filename);
      REQUIRE( ! exists );
    }

    jao.UpdateTestCase("Compiles and cleans up afterwards", 1, "Congrats, all required executables are and cleaned when you're done!");
  }

}
