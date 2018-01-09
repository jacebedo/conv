#include "functions.h"
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;


void output_err_msg(){
  cout << "please enter the correct syntax or use './conv help' for proper use." << "\n";
  exit(0);
}

void output_help_doc(){
  cout << "Help documentation placeholder" << endl;
  exit(0);
}

bool check_valid_input(string srcunit,string dstunit,float qty);
