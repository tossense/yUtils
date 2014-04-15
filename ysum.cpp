#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

    string line;
    string item, lastItem;
    unsigned long long cnt=0, sumCnt=0;
    while(getline(*pis, line))
    {
        stringstream ss(line);
        ss >> item >> cnt;
        if(item == lastItem)
        {
            sumCnt += cnt;
        }
        else
        {
            if( sumCnt >= 0 && !lastItem.empty() )
                cout << lastItem << "\t" << sumCnt << "\n";
            sumCnt = cnt;
            lastItem = item;
        }
    }

    if( sumCnt >= 0 && !lastItem.empty() )
        cout << lastItem << "\t" << sumCnt << "\n";
    return 0;
}
