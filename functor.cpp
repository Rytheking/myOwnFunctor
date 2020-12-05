#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <cmath>

using namespace std;

vector<int> list;
int i=0,c;
enum Token {EMPTYTOKEN,NAME, OPENBRACK, CLOSEBRACK, DATA, OPENPAREN, CLOSEPAREN, FUNCTOR, VAR, MUL, DIV, SUB, ADD, FUNCVAR, COMMA, FUNCSYM, DIGIT, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

class Tokenizer 
{
	private:
	  string s;
	  smatch sm;
	  int originalLength;
	  int lineNumber;
	  string filename;
	  int charNumber;
	public:
	string name;
    string location() {
		stringstream ss;
		ss << filename <<":"<<lineNumber << ":"<< charNumber<<":";
		return ss.str();
	}
	Tokenizer(string newString,string newFilename,int newLineNumber=0) {
	   lineNumber=newLineNumber;
	   filename=newFilename;
       s=newString;
        
	}
	Token peek() {
		Token t=EMPTYTOKEN;
		name="";
		regex keywordExpr("^(var|\\(|\\)|,|[a-zA-Z]+|\\*|\\+|\\-|\\[|\\]|=>|[0-9]|\\/)");
		regex nameExpr("^[a-zA-Z]+");
		cout<<s<<endl;
		if (regex_search(s,sm,keywordExpr) ) {
			
			if (sm[0]=="(") t=OPENPAREN;
			else if (sm[0]==")") t=CLOSEPAREN;
            else if (sm[0]=="[") t=OPENBRACK;
			else if (sm[0]=="]") t=CLOSEBRACK;
			else if (sm[0]==",") t=COMMA;
            else if (sm[0]=="fn") t=FUNCTOR;
            else if (sm[0]=="*") t=MUL;
            else if (sm[0]=="-") t=SUB;
            else if (sm[0]=="/") t=DIV;
            else if (sm[0]=="+") t=ADD;
            else if (sm[0]=="0") t=ZERO;
			else if (sm[0]=="1") t=ONE;
			else if (sm[0]=="2") t=TWO;
			else if (sm[0]=="3") t=THREE;
			else if (sm[0]=="4") t=FOUR;
			else if (sm[0]=="5") t=FIVE;
			else if (sm[0]=="6") t=SIX;
			else if (sm[0]=="7") t=SEVEN;
			else if (sm[0]=="8") t=EIGHT;
			else if (sm[0]=="9") t=NINE;
			else if (sm[0]=="=>") t=FUNCSYM;
			else if (regex_search(s,sm,nameExpr)) {
				t=NAME;
				name=sm[0];
			}
		}		
		return t;		
	}
	void pop() {
		// Remove next token
		s=sm.suffix().str();
		charNumber=originalLength-s.size();
		if (s[0]==' ') s=s.substr(1);
    }
	Token next() {
		//check();
		Token t=peek();
		pop();
		return t;
	}
	void check() {
		cerr << "Tokenizer String is :" <<s << ":" <<endl;
	}
};

int digit(Token t)
{
	if(t==ONE)
	{
		return 1;
	}
	else if(t==TWO)
	{
		return 2;
	}
	else if(t==THREE)
	{
		return 3;
	}
	else if(t==FOUR)
	{
		return 4;
	}
	else if(t==FIVE)
	{
		return 5;
	}
	else if(t==SIX)
	{
		return 6;
	}
	else if(t==SEVEN)
	{
		return 7;
	}
	else if(t==EIGHT)
	{
		return 8;
	}
	else if(t==NINE)
	{
		return 9;
	}
	return 0;
}

int findC(Tokenizer tokens)
{
	int column=0, tempInt=0;
	vector<int> temp;
	Token t=tokens.next();
	while(t!=MUL && t!=DIV&&t!=ADD&&t!=SUB&&t!=EMPTYTOKEN)
	{
		column++;
		temp.push_back(digit(t));
		t=tokens.next();
	}
	for(int i=0; i<temp.size(); i++)
	{
		column-=1;
		tempInt+=(pow(10, column)*temp[i]);
	}
	c=tempInt;
	return c;
}

vector<int> operationVarFirst(Tokenizer tokens)
{
	Token t=tokens.next();
	if(t==MUL)
	{
		c=findC(tokens);
		i=0;
		while(i<list.size())
		{
			list[i]=list[i]*c;
			i++;
		}
								
	}
	else if(t==DIV)
	{
		c=findC(tokens);
		i=0;
		while(i<list.size())
		{						
			list[i]=list[i]/c;
			i++;				
		}
	}
	else if(t==ADD)
	{
		c=findC(tokens);
		i=0;
		while(i<list.size())
		{
									
			list[i]=list[i]+c;
			i++;
		}
	}
	else if(t==SUB)
	{
		c=findC(tokens);
		i=0;
		while(i<list.size())
		{
									
			list[i]=list[i]-c;
			i++;
		}
	}
	return list;
}
vector<int> operationCostFirst(Token tokens)
{
	Token t=tokens;
	if(t==MUL)
	{
		i=0;
		while(i<list.size())
		{
			list[i]=c*list[i];
			i++;
		}
								
	}
	else if(t==DIV)
	{
		i=0;
		while(i<list.size())
		{						
			list[i]=c/list[i];
			i++;				
		}
	}
	else if(t==ADD)
	{
		i=0;
		while(i<list.size())
		{
									
			list[i]=c+list[i];
			i++;
		}
	}
	else if(t==SUB)
	{
		i=0;
		while(i<list.size())
		{
									
			list[i]=c-list[i];
			i++;
		}
	}
	return list;
}


Tokenizer arrayCon(Tokenizer tokens)
{
	Token t=tokens.next();
	vector<int> temp;
	int column=0, curr=0, c;
	while(t!=CLOSEBRACK){

			if(t!=COMMA)
			{
				temp.push_back(digit(t));
				column++;
			}
			else if(t==COMMA)
			{
				for(int i=0; i<temp.size();i++)
				{
					column-=1;
					curr+=(pow(10,column)*temp[i]);
				}
				list.push_back(curr);
				curr=0;
				column=0;
				temp.clear();
			}
			t=tokens.next();
        }
		for(int i=0; i<temp.size();i++)
		{
			column-=1;
			curr+=(pow(10,column)*temp[i]);
		}
		list.push_back(curr);
		int j=0;
		return tokens;
}

bool isFunctor(Tokenizer tokens)
{
    Token t=tokens.next();
    Token t2=tokens.next();
    if(t==NAME && t2==OPENBRACK)
    {
        //t=tokens.next();
		i=-1;
        tokens=arrayCon(tokens);
		t=tokens.next();
		t2=tokens.next();
        if(t==FUNCTOR && t2==OPENPAREN)
        {
			t=tokens.next();
            if(t==NAME)
            {
				t=tokens.next();
				t2=tokens.next();
                if(t==CLOSEPAREN and t2 == FUNCSYM)
                {
					t=tokens.next();
					if(t!=NAME)
					{
						vector<int> temp;
						int column=0;
						c=findC(tokens);
						operationCostFirst(t);
					}
					else if(t==NAME)
					{
						//t=tokens.next();
						operationVarFirst(tokens);
					}
				}
				else
				{
					cout<<"expected ) followed by =>"<<endl;
				} 
            } 
			else
			{
				cout<<"expected a NAME"<<endl;
			} 
        } 
		else
		{
			cout<<"expected fn followed by ("<<endl;
		} 
    } 
	else
	{
		cout<<"expected an array"<<endl;
	} 
	return false;
}

int main(int argc, char* argv[])
{
    //NAME OPENBRACK DATA CLOSEPAREN FUNCTOR OPENPAREN FUNCVAR CLOSEPAREN FUNCTORSYM VAR|NUMBER OP VAR|NUMBER
    string a = "args[10,240,3,4,5] fn(x)=> x/2";
	Tokenizer to(a,"a",1);
	isFunctor(to);
	int j=0;
	while(j<list.size())
	{
		cout<<list[j]<<endl;
		j++;
	}
    return 0;
}