/*
    Members: Cody Morgan, Andrew Levandowski
    Accounts: cssc1211 (location of assignment), cssc1214
    Class: CS 570, Summer 2018
    Assignment: Assignment 2, File Manager
    Filename: FileEditor.hpp
*/


#include <string>

using namespace std;

class FileEditor
{
    private:
        int byte;
        string fileName;
        string fileExists(string fileName);
        static int strCompare(string i, string j);
        void childProcesses(string fileName);
        void createDir();
        void createFile();
        void readFile();
        void writeFile();
        void fileStatus();
        void printListing();
        
        
    public:
        FileEditor();
        ~FileEditor();
        void mainMenu();
};


