#ifndef __GRAMMAR_H__
#define __GRAMMAR_H__

#include <uC++.h>

_Coroutine Grammar {
 public:
  enum Status { CONT, MATCH, ERROR };			// send more characters, in language, invalid
 private:
  Status status;					// current status of match
  char ch;						// character passed by cocaller
  int bs;                                               // stack-like variable to make sure #bs == #cs+1
  
  void main(){
    bs = 0;
   
    // First a
    if ( ch == 'a'){
      status = CONT;
    }
    else{
      status = ERROR;
    }
    suspend();


    // At least 1 b
    if ( ch == 'b'){
      bs++;
      status = CONT;
    }
    else{
      status = ERROR;
    }
    suspend();


    // 0 or more b's
    while ( ch == 'b'){
      bs++;
      status = CONT;
      suspend();
    }
    

    // 0 or more c's
    while ( ch == 'c'){
      bs--;
      if (bs == 0){ // number of cs equal or greater than number of bs
	status = ERROR;
	suspend();
	break;
      }
      status = CONT;
      suspend();
    }

    
    if (bs != 1){ // There are 2 or more bs than cs
      status = ERROR;
      suspend();
    }

    // Last d
    if ( ch == 'd'){
      status = MATCH;
    }
    else{
      status = ERROR;
    }
    suspend();


  }


 public:
  Status next( char c ) {
    ch = c;						// communication in
    resume();					// activate
    return status;					// communication out
  } // Grammar::next
}; // Grammar

#endif // __GRAMMAR_H__
