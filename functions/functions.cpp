#include "functions.h"
#include <string>
#include <iostream>
#include <regex>
#include <sqlite3.h>
#include <stdlib.h>
using namespace std;


static int callback(void * retval,int colsFound, char** ret_text , char** names) {
  *(bool *)retval = true;
  return 0;
}

void output_err_msg(){
  cout << "please enter the correct syntax or use './conv help' for proper use." << "\n";
  exit(0);
}

void output_help_doc(){
  cout << "Welcome to conv!" << endl;
  cout << "To make a conversion, enter the following command:  ./conv <src> <dst> <qty>," << endl;
  cout << "Where <src> is the current unit you have, <dst> is your desired unit of measurement, and <qty> is the amount you would like to convert" << endl;
  cout << "You may choose from these units" << endl;
  cout << "Length:" << endl << "nanometres (nm)"<< endl << "micrometres (um)"<< endl << "millimetres (mm)"<< endl << "centimetres (cm)"<< endl << "metres (m)" << endl << "kilometres (km)"<< endl << "inches (in)";
  cout << endl << "feet (ft)"<< endl << "yard (yd)" << endl << "mile (mi)" << endl << endl;

  cout << "Weight:" << endl << "milligrams (mg)"<< endl << "grams (g)"<< endl << "kilograms (kg)"<< endl << "metric tons (t) "<< endl << "short tonnes (tsht)" << endl << "long tonnes (tlng)"<< endl << "pounds (lb)" << endl << "ounce (oz)" << endl;

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
