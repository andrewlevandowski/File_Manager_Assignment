/*
    Members: Cody Morgan, Andrew Levandowski
    Accounts: cssc1211 (location of assignment), cssc1214
    Class: CS 570, Summer 2018
    Assignment: Assignment 2, File Manager
    Filename: driver.cpp
*/


#include "FileEditor.hpp"
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

int main()
{
    mkdir("fileEditing", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);    // make working directory
    chdir("fileEditing");       // cd to working directory

    FileEditor* editor = new FileEditor;
    editor->mainMenu();
    delete editor;

    return 0;
}
