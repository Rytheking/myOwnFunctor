#include <iostream>
#include <string>
#include <regex>
#include "vectorf.h"

int main()
{
    string s="/";
    smatch sm;
    regex keywordExpr("/");
	regex nameExpr("^[a-zA-Z]+");
	cout<<s<<endl;
	if (regex_search(s,sm,keywordExpr) )
        cout<<"sucess"<<endl;
    return 1;
}