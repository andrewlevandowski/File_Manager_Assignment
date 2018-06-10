#include "FileEditor.hpp"

using namespace std;

int main()
{
    FileEditor* editor = new FileEditor;
    editor->mainMenu();
    delete editor;

    return 0;
}
