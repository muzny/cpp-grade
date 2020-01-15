#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "JsonAutograderOutput.h"

// don't put anything else in this file so that test compile faster
int main( int argc, char* argv[] )
{

  Catch::Session session; // There must be exactly one instance
  
  std::string json_output = ""; // Some user variable you want to be able to set
  
  // Build a new parser on top of Catch's
  using namespace Catch::clara;
  auto cli 
    = session.cli() // Get Catch's composite command line parser
    | Opt( json_output, "json" ) // bind variable to a new option, with a hint string
        ["-j"]["--json"]    // the option names it will respond to
        ("where to write the json to?");        // description string for the help output
        
  // Now pass the new composite back to Catch so it uses that
  session.cli( cli ); 
  
  // Let Catch (using Clara) parse the command line
  int returnCode = session.applyCommandLine( argc, argv );
  if( returnCode != 0 ) // Indicates a command line error
      return returnCode;

  JsonAutograderOutput & jao = JsonAutograderOutput::GetInstance();


  int num_failed = session.run();

  // if set on the command line then 'json_output' is now set at this point
  if( json_output != "" ) {
      std::cout << "json output file: " << json_output << std::endl;
      jao.Write(json_output);
  }

  return 0;
}