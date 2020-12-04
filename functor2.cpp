#include <iostream>
#include <string>
#include <regex>
#include <vector>

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

bool isFunctor(Tokenizer tokens)
{
	
    Token t=tokens.next();
    Token t2=tokens.next();
    if(t==NAME && t2==OPENBRACK)
    {
        t=tokens.next();
		i=-1;
        while(t!=CLOSEBRACK){
			if(t!=COMMA)
            if(t==ZERO)
            {
                list.push_back(0);
            }
			else if(t==ONE)
			{
				list.push_back(1);
			}
			else if(t==TWO)
			{
				list.push_back(2);
			}
			else if(t==THREE)
			{
				list.push_back(3);
			}
			else if(t==FOUR)
			{
				list.push_back(4);
			}
			else if(t==FIVE)
			{
				list.push_back(5);
			}
			else if(t==SIX)
			{
				list.push_back(6);
			}
			else if(t==SEVEN)
			{
				list.push_back(7);
			}
			else if(t==EIGHT)
			{
				list.push_back(8);
			}
			else if(t==NINE)
			{
				list.push_back(9);
			}
			t=tokens.next();
        }
		int j=0;
		while(j<list.size())
		{
			cout<<list[j]<<endl;
			j++;
		}
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
						if(t== ZERO|t== ONE|t== TWO|t== THREE|t== FOUR|t== FIVE|t== SIX|t== SEVEN|t== EIGHT|t== NINE)
						{
							if(t==ZERO)
							{
								c=0;
							}
							else if(t==ONE)
							{
								c=1;
							}
							else if(t==TWO)
							{
								c=2;
							}
							else if(t==THREE)
							{
								c=3;
							}
							else if(t==FOUR)
							{
								c=4;
							}
							else if(t==FIVE)
							{
								c=5;
							}
							else if(t==SIX)
							{
								c=6;
							}
							else if(t==SEVEN)
							{
								c=7;
							}
							else if(t==EIGHT)
							{
								c=8;
							}
							else if(t==NINE)
							{
								c=9;
							}
							t=tokens.next();
							if(t==MUL)
							{
								i=0;
								cout<<list.size()<<endl;
								while(i<list.size())
								{
									list[i]=list[i]*c;
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
									
									list[i]=list[i]+c;
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
							
						}
						else
						{
							t=tokens.next();
							if(t==MUL)
							{
								i=0;
								t=tokens.next();
								cout<<t<<endl;
							if(t==ZERO)
							{
								c=0;
							}
							else if(t==ONE)
							{
								c=1;
							}
							else if(t==TWO)
							{
								c=2;
							}
							else if(t==THREE)
							{
								c=3;
							}
							else if(t==FOUR)
							{
								c=4;
							}
							else if(t==FIVE)
							{
								c=5;
							}
							else if(t==SIX)
							{
								c=6;
							}
							else if(t==SEVEN)
							{
								c=7;
							}
							else if(t==EIGHT)
							{
								c=8;
							}
							else if(t==NINE)
							{
								c=9;
							}
								while(i<list.size())
								{
									list[i]=list[i]*c;
									i++;
								}
							}
							else if(t==DIV)
							{
								i=-1;
								t=tokens.next();
							if(t==ZERO)
							{
								c=0;
							}
							else if(t==ONE)
							{
								c=1;
							}
							else if(t==TWO)
							{
								c=2;
							}
							else if(t==THREE)
							{
								c=3;
							}
							else if(t==FOUR)
							{
								c=4;
							}
							else if(t==FIVE)
							{
								c=5;
							}
							else if(t==SIX)
							{
								c=6;
							}
							else if(t==SEVEN)
							{
								c=7;
							}
							else if(t==EIGHT)
							{
								c=8;
							}
							else if(t==NINE)
							{
								c=9;
							}
								while(i<list.size())
								{
									
									list[i]=list[i]/c;
									i++;
								}
							}
							else if(t==ADD)
							{
								int i=0;
								t=tokens.next();
							if(t==ZERO)
							{
								c=0;
							}
							else if(t==ONE)
							{
								c=1;
							}
							else if(t==TWO)
							{
								c=2;
							}
							else if(t==THREE)
							{
								c=3;
							}
							else if(t==FOUR)
							{
								c=4;
							}
							else if(t==FIVE)
							{
								c=5;
							}
							else if(t==SIX)
							{
								c=6;
							}
							else if(t==SEVEN)
							{
								c=7;
							}
							else if(t==EIGHT)
							{
								c=8;
							}
							else if(t==NINE)
							{
								c=9;
							}
								while(i<list.size())
								{
									
									list[i]=list[i]+c;
									i++;
								}
							}
							else if(t==SUB)
							{
								int i=0;
								t=tokens.next();
							if(t==ZERO)
							{
								c=0;
							}
							else if(t==ONE)
							{
								c=1;
							}
							else if(t==TWO)
							{
								c=2;
							}
							else if(t==THREE)
							{
								c=3;
							}
							else if(t==FOUR)
							{
								c=4;
							}
							else if(t==FIVE)
							{
								c=5;
							}
							else if(t==SIX)
							{
								c=6;
							}
							else if(t==SEVEN)
							{
								c=7;
							}
							else if(t==EIGHT)
							{
								c=8;
							}
							else if(t==NINE)
							{
								c=9;
							}
								i=-1;
								while(i<list.size())
								{
									
									list[i]=list[i]-c;
									i++;
								}
							}
							
						} 
						j=-1;
						while(j<list.size())
						{
							cout<<list[j++]<<endl;
						}
						//return true;
                } 
				else{
					cout<<"hey4"<<endl;
					} 
            } 
			else{
				cout<<"hey3"<<endl;
				} 
        } 
		else{
			cout<<"hey2"<<endl;
			} 
    } 
	else{
		cout<<"hey1"<<endl;
		} 
	return false;
}

int main(int argc, char* argv[])
{
    //NAME OPENBRACK DATA CLOSEPAREN FUNCTOR OPENPAREN FUNCVAR CLOSEPAREN FUNCTORSYM VAR|NUMBER OP VAR|NUMBER
    string a = "args[1,2,3,4,5] fn(x)=> x*2";
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