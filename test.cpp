#include <iostream>
#include <fstream>
using namespace std;

int main() {
    char arr[] = {0xF, 0xB};
    streampos size;
    char * memblock;
    ifstream file ("TRACE1.DAT", ios::in|ios::binary|ios::ate);
    int pos = 0;
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [size];
        file.seekg (0, ios::beg);
        file.read (memblock, size);
        file.close();

        for (int i = 0; i < 10; i++) {
            cout << std::hex << (int)memblock[i] << " ";
        }
        cout << "\n";

    }

    return 0;
}