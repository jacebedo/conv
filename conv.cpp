#include <iostream>
#include <string>
#include <sqlite3.h>


using namespace std;


int main(int argc,char *argv[]) {

  sqlite3 * db;

  // sqlite database initialization
  int error_status = sqlite3_open("conversions.db",&db);
  if (error_status) cout << "ERROR: database connection failed\n";



  if (argc <= 1 || argc > 5) {
    cout << "please enter the correct syntax or use './conv help' for proper use." << "\n";
    return 0;
  }
  else {
    //Main workflow

    for (int i = 0; i < argc;i++) {
      if (string(argv[i]) == "help") {
        /*print out help documentation */
        cout << "help documentation placeholder \n";
      }


    }
  }


  return 0;

}




// Reqlires "sudo apt-get install libsqlite3-dev" , fixes sqlite3.h not found error
