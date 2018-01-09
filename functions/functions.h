#include <string>

using namespace std;



void output_err_msg();    //Outputs 'incorrect syntax' message to user
void output_help_doc();   //Outputs help documentation to user.

/* Checks the arguments passed for valid inputs. Returns true if valud.*/
bool check_valid_input(string srcunit,string dstunit,float qty);
