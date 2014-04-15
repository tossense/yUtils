#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

using namespace std;

int usage()
{
	cerr << "Usage:\n\tyblack [arg1:blacklist file]\n";
    cerr << "\tyblack [arg1:param(such as -v)] [arg2:blacklist file], Use -v for white list.\n";
	cerr << "The content to be filtered comes from stdin,\n";
	cerr << "  if the first field of a line match black list, the line will be filtered.\n";
	cerr << "  The output is stdout.\n";
	cerr << "  Notice: Each line from blacklist turns to be a item in black list.";
	cerr << " You'd better place NO 'SPACE CHARACTOR' in black keyword.\n";
	return 0;
}

int main(int argc, char *argv[])
{
	if( argc == 1 )
	{
		usage();
		return 0;
	}

	ifstream ifs;
	set<string> blackList;
    const char* fn = NULL;
    bool bReverse = false;
    if( argc == 2 )
    {
        fn = argv[1];
    }

    if( argc == 3 )
    {
        fn = argv[2];
        if(string(argv[1]) == "-v")
            bReverse = true;
    }

    if( argc > 3 )
    {
        cerr << "Too Many Arguments.\n";
        return 1;
    }

    ifs.open(fn);
    if( !ifs.good() )
    {
        cerr << "Can not Open File: " << fn << "\n";
        return 1;
    }

    string line;
    while(getline(ifs, line))
    {
        if(line.length() > 0)
            blackList.insert(line);
    }

    while( getline(cin, line) )
    {
        stringstream ss(line);
		string f1;
		ss >> f1;
		if(blackList.find(f1) == blackList.end())
		{
            if( !bReverse )
			    cout << line << "\n";
		}
        else if( bReverse )
        {
            cout << line << "\n";
        }
    }

    return 0;
}