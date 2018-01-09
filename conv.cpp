#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <sqlite3.h>

using namespace std;

static int callback(void * redacted,int colsFound, char** query_res , char** names) {
  for (int i = 0; i < colsFound; i++) {
    if (names[i] == NULL || query_res[i] == NULL) {cout << "LUL WRONG"; return 0;}
    cout << names[i] << " = " << query_res[i] << endl;
  }
  return 0;
}

int main(int argc,char *argv[]) {
  sqlite3 * db;
  string src = "";
  string dst = "";
  float qty = 0.0;
  // sqlite database initialization
  int error_status = sqlite3_open("conversions.db",&db);
  if (error_status) cout << "ERROR: database connection failed\n";



  if (argc <= 1 || argc >= 5) {
    cout << "please enter the correct syntax or use './conv help' for proper use." << "\n";
    return 0;
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


    //to do: parse arguments to make proper statements
    string STATEMENT = "SELECT qty FROM weight WHERE srcunit='lb' AND dstunit='oz'";
    char * test = 0;
    int query_res = sqlite3_exec(db,STATEMENT.c_str(),callback,NULL,&test);

  }


  return 0;

}




// Reqlires "sudo apt-get install libsqlite3-dev" , fixes sqlite3.h not found error
