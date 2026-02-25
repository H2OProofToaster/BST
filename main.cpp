#include "structs.cpp"
#include <string>
#include <fstream>

using namespace std;

int main() {

  bool running = true;
  BST* tree = new BST();
  
  //Read in from file
  cout << "What file? ";

  string fileName;
  cin >> fileName;

  cout << "Reading..." << endl;
  
  ifstream readFile(fileName);
  if (readFile.is_open()) {

    int v;
    while (readFile >> v) { tree->insert(v); }
  }
  readFile.close();

  cout << "Done" << endl;

  //Do actions
  while (running) {

    cout << "What is your action? (ADD, DELETE, PRINT, QUIT)" << endl;
    string action;
    cin >> action;

    if (action == "ADD" or action == "a") {

      //Add
    }
    else if (action == "DELETE" or action == "d") {

      //Delete
    }
    else if (action == "PRINT" or action == "p") {

      //Print
    }
    else if (action == "QUIT" or action == "q") {

      delete tree;
      running = false;
    }
    else { cout << "Not an action" << endl; }

    action.clear();
  }
  
  return 0;
}
