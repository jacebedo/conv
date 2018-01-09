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
  if (argc <= 1 || argc >= 5) {
    cout << "please enter the correct syntax or use './conv help' for proper use." << "\n";
    exit(0);
  }
  else {
    //Main workflow

    for (int i = 0; i < argc;i++) {
      if (string(argv[i]) == "help") {
        /*print out help documentation */
        cout << "help documentation placeholder \n";
        return 0;
      }
    }
    src = argv[1];
    dst = argv[2];
    if (argv[3] == NULL) { cout << "please enter a quantity: "; cin >> qty; }
    else {qty = strtof(argv[3],NULL);}

    // To do: Implement test case where srcunit and dstunit are not in the database.


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
