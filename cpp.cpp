#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { glob_init(); return yyparse(); }

Sym::Sym(string T,string V) { tag=T; val=V; share(); }
Sym::Sym(string V):Sym("sym",V) {}
void Sym::push(Sym*o) { nest.push_back(o); }
void Sym::share() { glob[val]=this; }

string Sym::ptr() { ostringstream os; os << this; return os.str(); }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::head() { return "<"+tag+":"+val+"> @"+ptr(); }
string Sym::dump(int depth) { string S = "\n"+pad(depth)+head();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }

Vector::Vector():Sym("vector","[]"){}
void Vector::share(){} // unshareble

Term::Term(string V):Sym("term",V){};
Var::Var(string V):Sym("var",V){}

map<string,Sym*> glob;
void glob_init() {

}
