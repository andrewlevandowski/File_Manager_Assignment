/*
    Members: Cody Morgan, Andrew Levandowski
    Accounts: cssc1211 (location of assignment), cssc1214
    Class: CS 570, Summer 2018
    Assignment: Assignment 2, File Manager
    Filename: FileEditor.cpp
*/


#include "FileEditor.hpp"
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sstream>
#include <algorithm>

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
            readFile();
        else if(selection == "4")
            writeFile();
        else if(selection == "5")
            fileStatus();
        else if(selection == "6")
            printListing();
        else
            cout << "Please enter a valid selection\n\n";
      }
    while(true);    
}

string FileEditor::fileExists(string fileName)
{
	if(fileName == "0")       // return to main menu
        return "0";

	FILE* check;        // used to check if file exists
	check = fopen(fileName.c_str(), "r");
	
	while(check == NULL)
	{
		cout << "File doesn't exist, try again\n";
		getline(cin, fileName);
		cout << "\n";

        if(fileName == "0")       // return to main menu
            return "0";

		check = fopen(fileName.c_str(), "r");
	}

	fclose(check);
    return fileName;
}

int FileEditor::strCompare (string i, string j)     // for sorting
{
	transform(i.begin(), i.end(), i.begin(), ::tolower);
	transform(j.begin(), j.end(), j.begin(), ::tolower);
	return i > j;
}

void FileEditor::childProcesses(string fileName)
{
    pid_t pid1, pid2, pid3;

	if((pid1 = fork()) < 0)
	{
		cout << "Fork failed" << "\n";
		exit(-1);
	}
	else if(pid1 == 0)      // backup
	{
        ifstream readFile;
	    readFile.open(fileName.c_str(), ios::in);
		string backupData;

		char c = readFile.get();

		while(readFile.good())
		{
			backupData += c;
			c = readFile.get();
		}
		
		ofstream backupFile;
        string backupFileName = fileName + ".bak";
		backupFile.open(backupFileName.c_str());
		backupFile << backupData;
		backupFile.close();
		exit(0);
	}
	
	if((pid2 = fork()) < 0)
	{
		cout << "Fork failed" << endl;
		exit(-1);
	}
	else if(pid2 == 0)      // sort
	{
		ifstream inputfile(fileName);
	    string line;
	
        string sortFileName = "sort_" + fileName;
	    ofstream sortFile (sortFileName.c_str());

	    getline(inputfile, line);
	 
	    vector<string> stringvector;
	    stringstream ssin(line);

	    while (ssin >> line)
		    stringvector.push_back(line);		
	    
	    sort(stringvector.begin(), stringvector.end(), strCompare);
	
	    int sv_size;
	    while (sv_size = stringvector.size())
        {
		    sortFile << stringvector.back();
		    if(sv_size > 1)
			    sortFile << " ";
		    stringvector.pop_back();
	    }
	    sortFile.close();
		exit(0);
	}
	
	if((pid3 = fork()) < 0)
	{
		cout << "Fork failed" << endl;
		exit(-1);
	}
	else if(pid3 == 0)      // reverse sort
	{
		ifstream inputfile(fileName);
	    string line;
	
        string rsortFileName = "rsort_" + fileName;
	    ofstream rsortFile (rsortFileName.c_str());

	    getline(inputfile, line);
	 
	    vector<string> stringvector;
	    stringstream ssin(line);

	    while (ssin >> line)
		    stringvector.push_back(line);		
	    
	    sort(stringvector.begin(), stringvector.end(), strCompare);
        reverse(stringvector.begin(), stringvector.end());
	
	    int sv_size;
	    while (sv_size = stringvector.size())
        {
		    rsortFile << stringvector.back();
		    if(sv_size > 1)
			    rsortFile << " ";
		    stringvector.pop_back();
	    }
	    rsortFile.close();
		exit(0);
	}
	
	for(int i = 1; i <= 3; i++)     // parent waits for all child processes to finish
		wait(NULL);
}

void FileEditor::createDir()
{
    cout << "Enter name of new directory\n";

    string newDir;
    getline(cin, newDir);
	cout << "\n";

    if(newDir == "0")       // return to main menu
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

    FileEditor::fileName = "";
    getline(cin, FileEditor::fileName);
	cout << "\n";

    if(FileEditor::fileName == "0")       // return to main menu
    {
        cout << "\n";
        return;
    }
    
    ofstream file (FileEditor::fileName);
    file.close();
    cout << "Regular file created\n\n";
}

void FileEditor::readFile()
{
    cout << "Enter file name to read from (0 for main menu)\n";

    FileEditor::fileName  = "";
    getline(cin, FileEditor::fileName);
	cout << "\n";

    FileEditor::fileName = fileExists(FileEditor::fileName);    // check if file exists

	if(FileEditor::fileName == "0")   // return to main menu
        return;

    ifstream inputFile(FileEditor::fileName);
	string line; 

    cout << "File data:\n";
	
	while(getline(inputFile, line))
		cout << line << "\n";

    cout << "\n";
    inputFile.close();

    pid_t pid1;     // for child process backup file

    if((pid1 = fork()) < 0)
	{
		cout << "Fork failed" << endl;
		exit(-1);
	}
	else if(pid1 == 0)      // backup
	{
        ifstream inputFile(FileEditor::fileName, ios::in); 
        ofstream backupFile;
        string backupFileName = "read_" + fileName + ".bak";
		backupFile.open(backupFileName.c_str());

		while(getline(inputFile, line))
		    backupFile << line << "\n";

		backupFile.close();
        inputFile.close();
		exit(0);
	}
    
    wait(NULL);     // parent waits for child process to finish
}

void FileEditor::writeFile()
{
    cout << "Enter file name to write to (0 for main menu)\n";

    FileEditor::fileName  = "";
    getline(cin, FileEditor::fileName);
	cout << "\n";

	FileEditor::fileName = fileExists(FileEditor::fileName);    // check if file exists

	if(FileEditor::fileName == "0")   // return to main menu
        return;

	cout << "Enter data to write to file (0 for main menu)\n";

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
    
	while(mode != "0" || mode != "1" || mode != "2" || mode != "3")     // input verification
	{
		getline(cin, mode);
		cout << "\n";

		if(mode == "0")		// return to main menu
			return;
		else if(mode == "1")		// insert
		{
		    cout << "Specify which byte to begin inserting (0 indexed)\n";
		    
		    string s_byte;
			bool valid = false;
			
			while(!valid)   // checks if byte specified is a valid entry
			{
				try{
					getline(cin, s_byte);
					cout << "\n";
				    FileEditor::byte = stoi(s_byte);

					ifstream readFile;
	    			readFile.open((FileEditor::fileName).c_str(), ios::in);
					readFile.seekg(0, ios::end);
					int length = readFile.tellg();
					readFile.seekg(0, ios::beg);
					
					while(FileEditor::byte > length)
					{
						cout << "Byte specified is out of bounds\n";
						getline(cin, s_byte);
						cout << "\n";
				    	FileEditor::byte = stoi(s_byte);
					}

					readFile.close();
					valid = true;
				}
				catch(const exception& e)
				{
				    cout << "Please enter a valid byte\n";
				}
			}
			
			ifstream readFile;
		    readFile.open((FileEditor::fileName).c_str(), ios::in);
			readFile.seekg(0, ios::end);
			int length = readFile.tellg();      // length of file
			readFile.seekg(0, ios::beg);
            int i = 0;      // counter used for every character in file
            string insertData;      // string that includes all previous and newly inserted chars
			
			if(length == FileEditor::byte)      // user inserts at end, aka an append
			{
				ofstream appFile;
		    	appFile.open((FileEditor::fileName).c_str(), ios::app);
				appFile << data;
				appFile.close();
			}
			else        // user inserts anywhere else in file
			{
				char c = readFile.get();

				while(readFile.good())
				{
					if(i == FileEditor::byte)       // location of user specified insert
						insertData += data;

					i++;
					insertData += c;        // concat remaining previous chars
					c = readFile.get();
				}
				
				ofstream insertFile;
				insertFile.open((FileEditor::fileName).c_str());
				insertFile << insertData;       // put final string after insertion into file
				insertFile.close();
			}

			readFile.close();
			childProcesses(FileEditor::fileName);       // create child processes as required
			cout << "Data inserted into file\n\n";
		    return;
		}
		else if(mode == "2")	// append
		{
			ofstream appFile;
		    appFile.open((FileEditor::fileName).c_str(), ios::app);
			appFile << data;
			appFile.close();
	        childProcesses(FileEditor::fileName);   // create child processes as required
			cout << "Data appended to file\n\n";
			return;
		}
		else if(mode == "3")	// overwrite
		{
			ofstream overFile;
			overFile.open((FileEditor::fileName).c_str());
			overFile << data;
			overFile.close();
			childProcesses(FileEditor::fileName);   // create child processes as required
			cout << "Data overwritten to file\n\n";
			return;
		}
		else
			cout << "Please enter a valid mode\n";
	}
}

void FileEditor::fileStatus()
{
    cout << "Enter file for status:\n";

    FileEditor::fileName  = "";
    getline(cin, FileEditor::fileName);
	cout << "\n";

    FileEditor::fileName = fileExists(FileEditor::fileName);

	if(FileEditor::fileName == "0")   // return to main menu
        return;

    struct stat buf;
	int status;
	status = stat((FileEditor::fileName).c_str(), &buf);

	cout << "File: " << FileEditor::fileName << "\t"
	<< "Blocks: " << buf.st_blocks << "\t"
	<< "IO Block: " << buf.st_blksize << "\n";
	cout << "Size: " << buf.st_size << "\t"
	<< "Device ID: " << buf.st_dev << "\t"
	<< "I-Node: " << buf.st_ino << "\n";
	cout << "Accessed: " << ctime(&buf.st_atime);
	cout << "Modified: " << ctime(&buf.st_mtime);
	cout << "Status Changed: " << ctime(&buf.st_ctime) << "\n";
}

void FileEditor::printListing()
{
    cout << "Contents of current working directory:\n";

    DIR* dirp = opendir(".");       // current source directory
	struct dirent* dp;

	while ((dp = readdir(dirp)) != NULL)      // prints file names
		cout << (dp->d_name) << "\n";

    cout << "\n";
	closedir(dirp);
}
