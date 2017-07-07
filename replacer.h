#ifndef REPLACER_H_INCLUDED
#define REPLACER_H_INCLUDED

#include<string>
#include<fstream>
using namespace std;

class replacer
{

private:
    ifstream ifs;

public:
    string preserveUnmatched;                        //stores the preserveUnmatched parameter from the string to parse
    string language;                                 // stores the language with which placeholders must be replaced with

    replacer();
	void multipleReplace(string&);
	void nestedReplace(string&, int);
};

#endif // REPLACER_H_INCLUDED
