#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream f1(argv[1]);
    ifstream f2(argv[2]);

    // assume small first
    string line;
    std::unordered_set<string> set1;
    while( f1 >> line )
    {
        set1.insert(line);
    }
    f1.close();

    while( f2 >> line )
    {
        if( set1.find(line) != set1.end() )
            cout << line << "\n";
    }
    return 0;
}
