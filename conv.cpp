#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <sqlite3.h>
#include "./functions/functions.h"

using namespace std;

static int callback(void * retval,int colsFound, char** ret_text , char** names) {

  for (int i = 0;i < colsFound;i++) {
      *(float *)retval = strtof(ret_text[i],NULL);
  }


  return 0;
}

int main(int argc,char *argv[]) {
  sqlite3 * db;
  string src = "";
  string dst = "";
  float qty = 0.0;
  int error_status = sqlite3_open("conversions.db",&db);
  if (error_status) cout << "ERROR: database connection failed\n";

  /* Check if command-line input syntax is valid. ("./conv help || ./conv src dst qty") */
  if (argc <= 1 || argc >= 5)  output_err_msg();
  else {
    //Main workflow

    if (string(argv[1]) == "help" || string(argv[2]) == "help") output_help_doc();

    src = string(argv[1]);
    dst = string(argv[2]);
    if (argv[3] == NULL) { cout << "please enter a quantity: "; cin >> qty; }
    else {qty = strtof(argv[3],NULL);}

    if (!check_valid_input(src,dst,qty)) {output_err_msg();}

    string STATEMENT = "SELECT qty FROM conversions WHERE srcunit='" + src + "' AND dstunit='" + dst + "'";
    char * query_err_msg;
    float convratio = 0.0;
    int query_res = sqlite3_exec(db,STATEMENT.c_str(),callback,&convratio,&query_err_msg);

    float result = qty * convratio;
    cout << qty << src << " = " << result << dst << "." << endl;

  return 0;

  }
}




// Reqlires "sudo apt-get install libsqlite3-dev" , fixes sqlite3.h not found error
