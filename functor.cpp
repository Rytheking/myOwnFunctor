#include <iostream>

using namespace std;
enum Token {FUNCTOR, VAR, OP};

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
	// 
	Token peek() {
		Token t=EMPTYTOKEN;
		name="";
		regex keywordExpr("^(A|B|turn|sew|fun|let|in|end|val|=|\\(|\\)|,|[a-zA-Z]+|*|+|-|/|[|])");
		regex nameExpr("^[a-zA-Z]+");
		if (regex_search(s,sm,keywordExpr) ) {
			if (sm[0]=="A") t=A;
			else if (sm[0]=="B") t=B;
			else if (sm[0]=="fun") t=FUN;
			else if (sm[0]=="let") t=LET;
			else if (sm[0]=="in") t=IN;
			else if (sm[0]=="end") t=END;
			else if (sm[0]=="=") t=EQUALS;
			else if (sm[0]=="(") t=OPENPAREN;
			else if (sm[0]==")") t=CLOSEPAREN;
            else if (sm[0]=="[") t=OPENBRAKE;
			else if (sm[0]=="]") t=CLOSEBRAKE;
			else if (sm[0]==",") t=COMMA;
            else if (sm[0]=="fn(x)=>") t=FUNCTOR;
            else if (sm[0]=="*") t=MUL;
            else if (sm[0]=="-") t=SUB;
            else if (sm[0]=="/") t=DIV;
            else if (sm[0]=="+") t=PLUS;
			else if (sm[0]=="const") t=CONST;
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

bool functorDecleration(Tokenizer tokens)
{
    Tokenizer temp=tokens;
	Token t=temp.next();
	if (t==FUNCTOR) {
        t=tokens.next();
		
		funUse->setName(tokens.name);
		t=tokens.next(); // Remove the OpenParen token
        tokens.check();
        QuiltNode *temp=new QuiltNode();
        if (quiltExpression(tokens,temp)) {
		    QuiltNode *argActual=new QuiltNode(PARAMETER);
			argActual->addChild(temp);
			funUse->addChild(argActual);
			return true;
			} 
			else throw SyntaxError("Expected Quilt Expression parameter in function use",tokens.location());
	} 
	return false;
    return false;
}

int main(int argc, char argv[])
{

    return 0;
}