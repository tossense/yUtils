#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/*
1 262997185       
1 159698044       
2 237595561       
2 145424642       
3 166872806       
3 131158581       
4 253872155       
4 38696185
*/

const char *INVALID_KEY = "@INVALID_KEY@";

struct t_resStat
{
	vector<double> ratio;
	double avg;
	double variance;
};

t_resStat calc(const vector<double>& vals);

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
    string lastKey(INVALID_KEY);
	vector<double> vals;
	vector<string> lines;
    while( getline(*pis, line) )
    {
		string key;
		double val;
		stringstream ss(line);
		ss >> key >> val;
		if( key != lastKey && lastKey != INVALID_KEY )
		{
			t_resStat resStat = calc(vals);
			for(size_t i=0; i<lines.size(); ++i)
			{
				cout << lines[i] << "\t"
					<< resStat.ratio[i] << "\t"
					<< resStat.avg << "\t" << resStat.variance << "\n";
			}
			vals.clear();
			lines.clear();
		}
		
		vals.push_back(val);
		lines.push_back(line);

		lastKey = key;
    }

	t_resStat resStat = calc(vals);
	for(size_t i=0; i<lines.size(); ++i)
	{
		cout << lines[i] << "\t"
			<< resStat.ratio[i] << "\t"
			<< resStat.avg << "\t" << resStat.variance << "\n";
	}

    return 0;
}

t_resStat calc( const vector<double>& vals )
{
	t_resStat ret;
	double sum = 0.0;
	for(size_t i=0; i<vals.size(); ++i)
	{
		sum += vals[i];
	}

	double avg = sum / vals.size();
	double sumTmp = 0.0;
	for(size_t i=0; i<vals.size(); ++i)
	{
		sumTmp += (avg - vals[i])*(avg - vals[i]);
		ret.ratio.push_back(vals[i]/sum);
	}

	ret.avg = avg;
	ret.variance = sumTmp / vals.size();
	return ret;
}
