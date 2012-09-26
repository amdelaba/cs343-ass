#include <uC++.h>
#include <iostream>
using namespace std;

_Coroutine FmtLines {
  
  char ch;
  int g,b;
  
  void main(){
    for(;;){
      for (g=0; g<5; g+=1){
	for (b=0; b<4; b+=1){
	  suspend();
	  cout << ch;
	}
	cout << " ";
      }
      cout << endl;
    }
  }
  
 public:
  FmtLines(){
    resume();
  }
  
  ~FmtLines(){
    if (g != 0 || b != 0){
      cout << endl;
    }
  }

  void prt(char ch){
    FmtLines::ch = ch;
    resume();
  }
};

void uMain::main(){
  FmtLines fmt;
  char ch;
  for (;;){
    cin >> ch;
    if (cin.fail()) break;
    fmt.prt( ch );
  }
}

