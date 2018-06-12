#include "FileEditor.hpp"
#include <iostream>
#include <string>
//#include <regex>
#include <sys/stat.h>
#include <climits>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

FileEditor::FileEditor(){}
FileEditor::~FileEditor(){}


void FileEditor::mainMenu()
{
    string selection;

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
		cout << "\n";
        
        if(selection == "0")
        {
            cout << "Exiting program...\n";
            return;
        }
        else if(selection == "1")
            createDir();
        else if(selection == "2")
            createFile();
        else if(selection == "3")
            cout << "3 selected\n";
        else if(selection == "4")
            writeFile();
        else if(selection == "5")
            cout << "5 selected\n";
        else if(selection == "6")
            cout << "6 selected\n";
        else
            cout << "Please enter a valid selection\n\n";
      }
    while(true);    
}

void FileEditor::createDir()
{
    cout << "Enter name of new directory\n";

    string newDir;
    cin >> newDir;
    cin.ignore(INT_MAX, '\n');      // flush out cin buffer

    if(newDir == "0")       // input is 0, return to main menu
    {
        cout << "\n";
        return;
    }

    int test = mkdir(newDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    if(test == -1)
    {
        cout << "Directory file already exists\n\n";  
        createDir();
    }
    else
        cout << "Directory file created\n\n";     
}

void FileEditor::createFile()
{
    cout << "Enter new file name\n";

    string fileName;
    cin >> fileName;
    cin.ignore(INT_MAX, '\n');      // flush out cin buffer

    if(fileName == "0")       // input is 0, return to main menu
    {
        cout << "\n";
        return;
    }
    
    ofstream file (fileName);
    file.close();
    cout << "Regular file created\n\n";
}

void FileEditor::writeFile()
{
    cout << "Enter file name to write to (0 for main menu)\n";

    string fileName;
    getline(cin, fileName);
	cout << "\n";

	if(fileName == "0")       // return to main menu
        return;

	FILE* check;
	check = fopen(fileName.c_str(), "r");
	
	while(check == NULL)
	{
		cout << "File doesn't exist, try again\n";
		getline(cin, fileName);
		cout << "\n";
		check = fopen(fileName.c_str(), "r");
	}

	fclose(check);

	cout << "Enter content to write to file (0 for main menu)\n";

	string data;
	getline(cin, data);
	cout << "\n";

	if(data == "0")       // return to main menu
        return;

    cout << "Enter mode:\n";
	cout << "1. Insert\n";
	cout << "2. Append\n";
	cout << "3. Overwrite\n";
	cout << "0. Return to main menu\n\n";

    string mode;
    
	while(mode != "0" || mode != "1" || mode != "2" || mode != "3")
	{
		getline(cin, mode);
		cout << "\n";

		if(mode == "0")		// return to main menu
			return;
		else if(mode == "1")		// insert
		{
		    //fstream insertFile;
		    //insertFile.open(fileName.c_str());
		    
		    FILE* insertFile;
		    insertFile = fopen(fileName.c_str(), "wb");

		    cout << "Specify which byte to begin inserting\n";
		    
		    string byte;
		    getline(cin, byte);

		    try{
		        int temp = stoi(byte);
		        //insertFile.clear();
		        //insertFile.seekg(temp);

		        fseek(insertFile, temp, SEEK_SET);

		        
		        /*
		        insertFile.seekg(0, ios::end);
		        int length = insertFile.tellg();

		        while(temp > length)
		        {
		            cout << "Value specified is longer than file length\n";
		            cout << "Specify which byte to begin inserting\n";
		    
		            string byte;
		            getline(cin, byte);
		            temp = stoi(byte);
		        }
		        */
		    }
		    catch(const exception& e)
		    {
		        cout << "Please enter a valid byte\n\n";
		    }

		    /*
		    insertFile.clear();
		    insertFile.seekg(0, file.beg);
		    */

		    string test = "test test test";
		
			vector<string> testVec = {"test"};
			test = testVec[0];

		    fputs(test.c_str(), insertFile);
		    //fseek(insertFile, 0, SEEK_SET);
		    fclose(insertFile);
		    return;
		}
		else if(mode == "2")	// append
		{
			return;
		}
		else if(mode == "3")	// overwrite
		{
			return;
		}
		else
			cout << "Please enter a valid mode\n";
	}
}

    

    

        




