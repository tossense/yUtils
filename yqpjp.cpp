#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*
gonglue 'gong'lue
gongl   'gong'lue
gonglve 'gong'lue
gl      'gong'lue
glue    'gong'lue
gonl    'gong'lue
gonlue  'gong'lue
gognl   'gong'lue
gognlue 'gong'lue
gongnue 'gong'lue
*/

enum e_typePy
{
	QP, JP
};

int gao(vector<e_typePy>& res
		, const string& inputStr, int curPosInputStr
		, const vector<string>& pys, int curPy, int curPyPos);

string toStr(const vector<e_typePy>& res);

bool pyEqual(char a, char b)
{
	if(a == b)
	{
		return true;
	}
	else if( (a=='u' && b=='v') || (a=='v' && b=='u') )
	{
		return true;
	}
	else
	{
		return false;
	}
}

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

    string line;
    while( getline(*pis, line) )
    {
		stringstream ss(line);
		string inputStr, pysStr;
		ss >> inputStr >> pysStr;
		for(size_t i=0; i<pysStr.length(); ++i)
		{
			if(pysStr[i] == '\'')
				pysStr[i] = ' ';
		}
		stringstream ss1(pysStr);
		string py;
		vector<string> pys;
		while(ss1 >> py)
		{
			pys.push_back(py);
		}
		//pys.push_back("__DUMMY__");

		vector<e_typePy> res;
		if( inputStr.length() > pysStr.length() - pys.size()
			|| gao(res, inputStr, 0, pys, 0, 0) != 0 )
		{
			cout << line << "\tNA" << "\n";
		}
		else
		{
			cout << line << "\t" << toStr(res) << "\n";
			
		}
    }

    return 0;
}

int gao( vector<e_typePy>& res
		, const string& inputStr, int curPosInputStr
		, const vector<string>& pys, int curPy, int curPyPos )
{	
	if( curPy >= pys.size() )
	{
		if( curPosInputStr < inputStr.length() )
			return 1;
		else
			return 0;
	}

	if( curPosInputStr >= inputStr.length() )
	{
		if( curPy == pys.size() )
		{
			return 0;
		}
		else if( curPy == pys.size() - 1 )
		{
            if( pys[curPy][curPyPos] == 'g' && curPyPos >= 2 )
            {
                return 1;
            }
			res.push_back(JP);
			return 0;
		}
		else
		{
			return 1;
		}
	}

	if( inputStr[curPosInputStr] == '\'' )
	{
		//currently, not support ' separator
		return 1;
	}

	if( !pyEqual(inputStr[curPosInputStr], pys[curPy][curPyPos] ) 
		&& ( curPy == pys.size() - 1
			||!pyEqual(inputStr[curPosInputStr], pys[curPy+1][0]) )
		)
	{
		return 1;
	}

	if( pyEqual(inputStr[curPosInputStr], pys[curPy][curPyPos]) )
	{
		if( curPyPos == pys[curPy].length() - 1)
		{
			res.push_back(QP);
			if( curPosInputStr == inputStr.size() - 1 
				&& curPy < pys.size() - 1 )
			{
				return 1;
			}
			else
			{
				return gao( res, inputStr, curPosInputStr+1, pys, curPy+1, 0 );
			}
		}
		else
		{
			return gao( res, inputStr, curPosInputStr+1, pys, curPy, curPyPos+1 );
		}
	}
	else if ( pyEqual(inputStr[curPosInputStr], pys[curPy+1][0]) )
	{
        if( pys[curPy][curPyPos] == 'g' && curPyPos >= 2 )
        {
            //anshou 'ang'shou
            //mintian 'ming'tian ≤ªÀ„ºÚ∆¥
            return 1;
        }
		res.push_back(JP);
		return gao( res, inputStr, curPosInputStr+1, pys, curPy+1, 1);
	}
}

string toStr( const vector<e_typePy>& res )
{
	string ret;
	for(size_t i=0; i<res.size(); ++i)
	{
		if(res[i] == QP)
			ret += 'q';
		else
			ret += 'j';
	}
	return ret;
}
