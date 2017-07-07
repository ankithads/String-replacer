/*
This program replaces the placeholders ${namespace:key} in the string with the value from the variables files
Input: <keyword> [parameters]
       1. language [country_code]
       2. replace "[String to process]" [preserveUnmatched=false]
       3. quit
output: string with placeholders replaced
*/
#include<iostream>
#include<string>
#include "replacer.h"

using namespace std;

//Error code description
#define INVALID_REPLACE_FORMAT "Please enter valid replace format : replace \"[String to process]\" [true/false] "
#define INVALID_KEYWORD "Please enter valid keyword: language/replace/quit"
#define INVALID_LANGUAGE_FORMAT "Please enter the country code: language [country_code]"

void trim(string& s);

int main()
{
	string command, keyword, parameters;
	replacer rep;
	size_t index;

	cout<<"Please enter any of the below command"<<endl;
	cout<<"\t-language [country_code]\n\t-replace \"[String to process]\" [preserveUnmatched=false]\n\t-quit"<<endl;

	while (1)
	{
		getline(cin, command);
		trim(command);                                               //reads the command from STDIN
		index = command.find(" ");
		keyword = command.substr(0, index);                                  //extracts the keyword

		if (keyword == "quit")
        {
            return 0;
        }
		else if (keyword == "replace")
		{
		    size_t index1 = command.find_first_of('"',index+1);
		    if(index1 == string::npos || command[command.find_first_not_of(" \t",index)] != '"')
            {
                cerr<<INVALID_REPLACE_FORMAT<<endl;
                continue;
            }

		    size_t index2 = command.find_last_of('"');
		    if(index2 == index1)
            {
                cerr<<INVALID_REPLACE_FORMAT<<endl;
                continue;
            }

            //defaults preserveUnmatched parameter to false if not provided

            if(index2 == command.length()-1)
            {

                rep.preserveUnmatched = "false";
            }
		    else
            {
                rep.preserveUnmatched = command.substr(index2+2);
                if(rep.preserveUnmatched != "false" && rep.preserveUnmatched != "true")
                {
                    cerr<<INVALID_REPLACE_FORMAT<<endl;
                    continue;
                }
            }

            //extracts the string to be parsed
            parameters = command.substr(index1+1,index2-index1-1);
            rep.multipleReplace(parameters);


		}
		else if (keyword == "language")
        {
            //if country code is not present
            if(command.length() == keyword.length())
            {
                cerr<<INVALID_LANGUAGE_FORMAT<<endl;
                continue;
            }

            rep.language = command.substr(index+1);
        }
        else
        {
            cerr<<INVALID_KEYWORD<<endl;
        }
	}

	return 0;
}

//removes the leading and trailing whitespaces from the string
void trim(string& s)
{
   size_t p = s.find_first_not_of(" \t");
   s.erase(0, p);

   p = s.find_last_not_of(" \t");
   if (string::npos != p)
      s.erase(p+1);
}
