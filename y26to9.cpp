#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const char g_data[] = {
    '2', '2', '2',
    '3', '3', '3',
    '4', '4', '4',
    '5', '5', '5',
    '6', '6', '6',
    '7', '7', '7', '7',
    '8', '8', '8',
    '9', '9', '9', '9'
};

char trans(char c)
{
    return g_data[c - 'a'];
}

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

    string line;
    while(getline(*pis, line))
    {
        
        bool ill = false;
        for(size_t i=0; i<line.length(); ++i)
        {
            if(line[i] == '\t' || line[i] == ' ')
            {
                //only trans the first field
                break;
            }

            if(line[i] >= 'a' && line[i] <= 'z')
                line[i] = trans(line[i]);
            else
                ill = true;
        }
        if(ill)
            cerr << line << " has char out of 26 keys.\n";
        cout << line << "\n";
    }

    return 0;
}