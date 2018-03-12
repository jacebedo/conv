#include "functions.h"
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include <sqlite3.h>
#include <stdlib.h>
using namespace std;


ifstream * local_fs;

static int callback(void * retval,int colsFound, char** ret_text , char** names) {
  *(bool *)retval = true;
  return 0;
}

void pass_filestream(ifstream * src){
  local_fs = src;
}

void output_err_msg(){
  cout << "please enter the correct syntax or use './conv help' for proper use." << "\n";
  exit(0);
}

void output_help_doc(){
  string currentline;
  while (getline(*local_fs,currentline)){
    cout << currentline << "\n";
  }

  exit(0);
}

void check_txt_input(int argc, char * argv[]){
    if (argv[1] == NULL) output_err_msg();
    else {
      if (string(argv[1]) == "help") output_help_doc();
      else{
        if (argv[2] == NULL) output_err_msg();
      }
    }


}

bool check_db(string inputA,string inputB,float qty,sqlite3 * db){

  //Test empty inputs
  if ( inputA == "" || inputB == "" || qty == 0.0 ) return false;

  //Test inputs not in database
  string STATEMENT = "SELECT * FROM conversions WHERE srcunit='" + inputA + "' AND dstunit='" + inputB + "'";
  char * query_err_msg;
  bool valid = false;
  int query_res = sqlite3_exec(db,STATEMENT.c_str(),callback,&valid,&query_err_msg);
  if (!valid) return false;
  return true;
}
