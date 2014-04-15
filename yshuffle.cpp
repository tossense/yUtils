#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
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

    vector<string> vec;
    vec.reserve(1024);
    string line;
    while( getline(*pis, line) )
    {
        vec.push_back(line);
    }

    ::srand(time(NULL));
    random_shuffle(vec.begin(), vec.end());
    for(size_t i=0; i<vec.size(); ++i)
    {
        cout << vec[i] << "\n";
    }

    return 0;
}