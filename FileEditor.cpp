#include "FileEditor.hpp"
#include <iostream>
#include <string>
#include <regex>

using namespace std;

FileEditor::FileEditor(){}
FileEditor::~FileEditor(){}


void FileEditor::mainMenu()
{
    string selection;
    bool valid;
    regex range("[0-6]");

    do{
        valid = true;

        cout << "**Multi-Processing File Editor**\n\n";
        cout << "Please choose an option below:\n";
        cout << "1. Create a directory file\n";
        cout << "2. Create a regular file\n";
        cout << "3. Read from a file\n";
        cout << "4. Write to a file\n";
        cout << "5. Print file status\n";
        cout << "6. Print directory listing\n";
        cout << "0. Exit program\n\n";

        getline(cin, selection);

        if(!regex_match(selection, range))
        {
            cout << "Please enter a valid selection\n\n";
            valid = false;
        }
        else if(selection == "0")
        {
            cout << "Exiting program...\n";
            return;
        }
        else if(selection == "1")
            cout << "1 selected\n";
        else if(selection == "2")
            cout << "2 selected\n";
        else if(selection == "3")
            cout << "3 selected\n";
        else if(selection == "4")
            cout << "4 selected\n";
        else if(selection == "5")
            cout << "5 selected\n";
        else if(selection == "6")
            cout << "6 selected\n";
      }
    while(!valid);
         
}


