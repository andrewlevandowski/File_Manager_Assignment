#include "FileEditor.hpp"
#include <iostream>
#include <string>
#include <regex>
#include <sys/stat.h>
#include <climits>

using namespace std;

FileEditor::FileEditor(){}
FileEditor::~FileEditor(){}


void FileEditor::mainMenu()
{
    string selection;
    regex range("[0-6]");

    do{
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
            cout << "Please enter a valid selection\n\n";
        else if(selection == "0")
        {
            cout << "Exiting program...\n";
            return;
        }
        else if(selection == "1")
            createDir();
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
    while(true);    
}

void FileEditor::createDir()
{
    cout << "Enter name of new directory\n";

    string root = "/home/cody/Desktop/CS570_a2/";
    string newDir;
    cin >> newDir;
    cin.ignore(INT_MAX, '\n');      // flush out cin buffer

    if(newDir == "0")       // input is 0, return to main menu
    {
        cout << "\n";
        return;
    }

    string path = root + newDir;
    int test = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    if(test == -1)
    {
        cout << "Directory already exists\n\n";  
        createDir();
    }
    else
        cout << "Directory created\n\n";     
}

