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
