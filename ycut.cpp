#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void usage()
{
    cerr << "Usage: ycut <num> <instream>\n";
}

int main(int argc, char *argv[])
{
    int aimField = 0;
    if( argc >= 2 )
    {
        string arg1(argv[1]);
        stringstream ss(arg1);
        ss >> aimField;
    }
    ifstream ifs;
    istream *pis = NULL;
    if( argc == 3 )
    {
        ifs.open(argv[2]);
        pis = &ifs;
    }
    else if( argc == 2 )
    {
        pis = &cin;
    }
    else if( argc < 2 )
    {
        usage();
        return 1;
    }

    if( argc > 3 )
    {
        cerr << "Too Many Arguments.\n";
        usage();
        return 1;
    }
    if( !pis->good() )
    {
        cerr << "Can not Open File.\n";
        return 1;
    }
    if( aimField < 1 )
    {
        cerr << "Invalid Field Number.\n";
        return 1;
    }
    
    string line;
    while( getline(*pis, line) )
    {
        stringstream ss(line);
        string str;
        int cnt = 0;
        while( ss >> str )
        {
            ++cnt;
            if(cnt == aimField)
            {
                cout << str << "\n";
                break;
            }
        }
    }
    return 0;
}
