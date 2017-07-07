/*
This file has the implementation of the replacer class functions
*/

#include "replacer.h"
#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>
using namespace std;

//constructor
replacer::replacer()
{
    language = "en";                                                    //Initializes language to English
    preserveUnmatched = "false";                                        //Initializes preserveUnmatched to false
}

//function to replace the placeholders "${namespace:key}"
void replacer::nestedReplace(string& param, int index)
{
    unordered_map<string,string>  m1;
    string line,fileName,key;
    size_t index1,index2;
    m1.clear();                                                         //clear the map

    index1 = param.find(':',index+2);

    //if place holders is in "${namespace:${string}} ${namespace:key}" pattern
    if((index1 > param.find('$',index+2)))
    {
        return;
    }
    //for nested replacements of the placeholders
    if((param[index1+1]== '$') && (param[index1+2]=='{'))
    {
        nestedReplace(param,index1+1);
    }

    //get the values from the variables file to replace with placeholders
    fileName = param.substr(index+2,index1-index-2);                    //extracts the namespace value from the placeholder  to get the variables file name.
    ifs.open(language + "\/" + fileName + ".properties");               //opens the file from the respective path based on the language eg: en/colors.properties
    while (ifs >> line)
    {
        //stores the key and value from the variables file in the map
        size_t equal = line.find("=");
        string key = line.substr(0, equal);
        string value = line.substr(equal + 1);
        m1[key] = value;
    }

    //Match the keys to replace in the string
    index2 = param.find('}', index1);
    key = param.substr(index1+1,index2-index1-1);                       //extracts the key from the placeholder
    if(m1.find(key) == m1.end())
    {
        //for unmatched keys
        if(preserveUnmatched == "false")
          param.replace(index, index2 - index+1, " ");
    }
    else
    {
        param.replace(index, index2 - index+1, m1[key]);
    }
    ifs.close();
}


void replacer::multipleReplace(string& parameters)
{
	size_t index = parameters.find("$");

	//parse the string to replace all the placeholders
	while (index != string::npos)
	{
		if (parameters[index + 1] == '{')
		{
		    nestedReplace(parameters,index);
        }
		index = parameters.find("$",index+1);                        //get the next placeholder
	}

	cout<<"\n"<<parameters<<"\n"<<endl;                                          //prints the replaced string.


}
