#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    // assume sorted

    ifstream ifs;
    istream *pis = NULL;
    if( argc == 2 )
    {
        ifs.open(argv[1]);
        pis = &ifs;
    }
    else if( argc == 1 )
    {
        pis = &cin;
    }

    if( argc > 2 )
    {
        cerr << "Too Many Arguments.\n";
        return 1;
    }
    if( !pis->good() )
    {
        cerr << "Can not Open File.\n";
        return 1;
    }

    string lastline;
    getline(*pis, lastline);

    string line;
    unsigned long long cnt = 1;
    while( getline(*pis, line) )
    {
        if( line != lastline )
        {
            cout << lastline << "\t" << cnt << "\n";
            cnt = 1;
            lastline = line;
        }
        else
        {
            ++cnt;
        }
    }

    cout << lastline << "\t" << cnt << "\n";
    return 0;
}
