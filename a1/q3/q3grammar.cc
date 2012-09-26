// Command syntax:
//   $ ./a.out  [ input-file ] 
// all parameters are optional. Defaults: input=>cin
//
// Examples:
//   $ ./a.out 
//   $ ./a.out in

#include <uC++.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;					// direct access to std
#include <cstdlib>					// exit
#include "q3grammar.h"
#include <string>

bool convert( int &val, char *buffer ) {		// convert C string to integer
    std::stringstream ss( buffer );			// connect stream and buffer
    ss >> dec >> val;					// convert integer from buffer
    return ! ss.fail() &&				// conversion successful ?
	// characters after conversion all blank ?
	string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
} // convert



void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
	 << ") [ infile ]" << endl;
    exit( EXIT_FAILURE );				// TERMINATE
} // usage




void uMain::main() {
    istream *infile = &cin;				// default value
    ostream *outfile = &cout;				// default value

    switch ( argc ) {
     case 2:
	try {
	    infile = new ifstream( argv[1] );
	} catch( uFile::Failure ) {
	    cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
	    usage( argv );
	} // try
        // FALL THROUGH
      case 1:						// all defaults
        break;
      default:						// wrong number of options
	usage( argv );
    } // switch

    *infile >> noskipws;				// turn off white space skipping during input

    //* line by line
    string line;
    for (;;){ 
      Grammar grammar;
      getline(*infile, line);
      if ( infile->fail() ) break;
      *outfile << "\"" << line <<  "\" : ";
      
      if (line == ""){
	*outfile << "Warning! Blank line.";
      }
      
      else {
	
	*outfile << "\"";
      
	for (unsigned int i = 0; i < line.length(); i+=1){
	  
	  *outfile << line[i];
	  
	  Grammar::Status status = grammar.next( line[i] );

	  if ( status  == Grammar::CONT ){
	    if (i == line.length()-1){ //last character
	      *outfile << "\"";
	      *outfile << " no";
	    }
	  }

	  else {
	    *outfile << "\"";
	  
	    if ( status == Grammar::MATCH ){
	      *outfile << " yes";
	    }
	    else if ( status == Grammar::ERROR ){
	      *outfile << " no";
	    }
	    
	    if ( i != line.length()-1 ){
	      *outfile << " -- extraneous characters ";
	      *outfile << "\"" << line.substr(i+1) << "\"";
	    }
	    break;
	  }
	  
	}
		
      }
      *outfile << endl;
    }

    if ( infile != &cin ) delete infile;		// close file, do not delete cin!
    if ( outfile != &cout ) delete outfile;		// close file, do not delete cout!

} // uMain::main



