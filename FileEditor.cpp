#include "FileEditor.hpp"
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <dirent.h>

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

	FILE* check;
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
    

void FileEditor::createDir()
{
    cout << "Enter name of new directory\n";

    string newDir;
    getline(cin, newDir);
	cout << "\n";

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

    FileEditor::fileName = "";
    getline(cin, FileEditor::fileName);
	cout << "\n";

    if(FileEditor::fileName == "0")       // input is 0, return to main menu
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

    FileEditor::fileName = fileExists(FileEditor::fileName);

	if(FileEditor::fileName == "0")   // return to main menu
        return;

    ifstream inputfile(FileEditor::fileName);
	string line; 

    cout << "File data:\n";
	
	while(getline(inputfile, line))
	{
		cout << line << endl;
	}

	inputfile.close();
    cout << "\n";
}

void FileEditor::writeFile()
{
    cout << "Enter file name to write to (0 for main menu)\n";

    FileEditor::fileName  = "";
    getline(cin, FileEditor::fileName);
	cout << "\n";

	FileEditor::fileName = fileExists(FileEditor::fileName);

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
    
	while(mode != "0" || mode != "1" || mode != "2" || mode != "3")
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
			
			while(!valid)
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
			string insertData;
			int i = 0;
			readFile.seekg(0, ios::end);
			int length = readFile.tellg();
			readFile.seekg(0, ios::beg);
			
			if(length == FileEditor::byte)
			{
				ofstream appFile;
		    	appFile.open((FileEditor::fileName).c_str(), ios::app);
				appFile << data;
				appFile.close();
			}
			else
			{
				char c = readFile.get();

				while(readFile.good())
				{
					if(i == FileEditor::byte)
						insertData += data;

					i++;
					insertData += c;
					c = readFile.get();
				}
				
				ofstream insertFile;
				insertFile.open((FileEditor::fileName).c_str());
				insertFile << insertData;
				insertFile.close();
			}

			readFile.close();
			
			cout << "Data inserted into file\n\n";
		    return;
		}
		else if(mode == "2")	// append
		{
			ofstream appFile;
		    appFile.open((FileEditor::fileName).c_str(), ios::app);
			appFile << data;
			appFile.close();
	
			cout << "Data appended to file\n\n";
			return;
		}
		else if(mode == "3")	// overwrite
		{
			ofstream overFile;
			overFile.open((FileEditor::fileName).c_str());
			overFile << data;
			overFile.close();
			
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

    

    

        




