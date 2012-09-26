// Purpose: copy file
//
// Command syntax:
//   $ ./a.out [ size (>= 0) [ code (>= 0) [ input-file [ output-file ] ] ] ]
// all parameters are optional. Defaults: size=>20, code=>5, input=>cin, output=>cout
//
// Examples:
//   $ ./a.out 34
//   $ ./a.out 34 0
//   $ ./a.out 34 0 in
//   $ ./a.out 34 0 in out

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;					// direct access to std
#include <cstdlib>					// exit

bool convert( int &val, char *buffer ) {		// convert C string to integer
    std::stringstream ss( buffer );			// connect stream and buffer
    ss >> dec >> val;					// convert integer from buffer
    return ! ss.fail() &&				// conversion successful ?
	// characters after conversion all blank ?
	string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
} // convert

enum { sizeDeflt = 20, codeDeflt = 5 };			// global defaults

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " [ size (>= 0 : " << sizeDeflt
	 << ") [ code (>= 0 : " << codeDeflt
	 << ") [ input-file [ output-file ] ] ] ]" << endl;
    exit( EXIT_FAILURE );				// TERMINATE
} // usage

int main( int argc, char *argv[] ) {
    int size = sizeDeflt, code = codeDeflt;		// default value
    istream *infile = &cin;				// default value
    ostream *outfile = &cout;				// default value

    cin.exceptions( ios_base::badbit | ios_base::failbit | ios_base::eofbit );
    cout.exceptions( ios_base::badbit | ios_base::failbit );

    switch ( argc ) {
      case 5:
	try {
	    outfile = new ofstream( argv[4] );
	    outfile->exceptions( ios_base::badbit | ios_base::failbit );
	} catch( ios_base::failure ) {			// open failed ?
	    cerr << "Error! Could not open output file \"" << argv[4] << "\"" << endl;
	    usage( argv );
	} // try
        // FALL THROUGH
      case 4:
	try {
	    infile = new ifstream( argv[3] );
	    infile->exceptions( ios_base::badbit | ios_base::failbit | ios_base::eofbit );
	} catch( ios_base::failure ) {
	    cerr << "Error! Could not open input file \"" << argv[3] << "\"" << endl;
	    usage( argv );
	} // try
        // FALL THROUGH
      case 3:
        if ( ! convert( code, argv[2] ) || code < 0 ) {	// invalid integer ?
	    usage( argv );
	} // if
        // FALL THROUGH
      case 2:
        if ( ! convert( size, argv[1] ) || size < 0 ) {	// invalid integer ?
	    usage( argv );
	} // if
        // FALL THROUGH
      case 1:						// all defaults
        break;
      default:
	    usage( argv );
    } // switch

    *infile >> noskipws;				// turn off white space skipping during input

    char ch;
    try {						// eof raises exception
	for ( ;; ) {					// copy input file to output file
	    *infile >> ch;				// read a character
	    *outfile << ch;				// write a character
	} // for
    } catch( ios_base::failure ) {
    } // try

    if ( infile != &cin ) delete infile;		// close file, do not delete cin!
    if ( outfile != &cout ) delete outfile;		// close file, do not delete cout!
} // main

// Local Variables: //
// compile-command: "g++ IOexp.cc" //
// End: //
