#include <string>
#include <vector>
#include <experimental/filesystem> // g++ 7 includes this under experimental

#include "catch.hpp"

#include "JsonAutograderOutput.h"


// include files to be tested here (e.g. from a student submission)
#include "Point.h"


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
