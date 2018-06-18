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


