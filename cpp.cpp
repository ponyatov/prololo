#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { glob_init(); return yyparse(); }

Sym::Sym(string T,string V) { tag=T; val=V; share(); }
Sym::Sym(string V):Sym("sym",V) {}
void Sym::push(Sym*o) { nest.push_back(o); }
void Sym::pushV(Sym*o) {
	for (auto it=o->nest.begin(),e=o->nest.end();it!=e;it++,arity++)
		push(*it); }
string Sym::ar() { ostringstream os; os << arity; return os.str(); }
void Sym::share() { glob[val]=this; }


string Sym::ptr() { ostringstream os; os << " @" << this; return os.str(); }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::head() { return "<"+tag+":"+val+">"+ptr(); }
string Sym::dump(int depth) { string S = "\n"+pad(depth)+head();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }

Term::Term(string V):Sym("term",V){}
string Term::head() { return val+"/"+ar(); }

Var::Var(string V):Sym("var",V){}

Vector::Vector():Sym("vector","[]"){}
void Vector::share(){}

map<string,Sym*> glob;
void glob_init(){}

int Sym::X=0;
string Sym::flat(int depth) { ostringstream os;
	if (depth==0) X=0; // reset
	os << 'X'<<X++<<" = " << head() << endl;
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		os << (*it)->flat(depth+1);
	return os.str(); }
