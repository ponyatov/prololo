#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { glob_init(); return yyparse(); }

Sym::Sym(string T,string V) { tag=T; val=V; share(); }
Sym::Sym(string V):Sym("sym",V) {}
void Sym::push(Sym*o) { nest.push_back(o); arity++; }
void Sym::pushV(Sym*o) {
	for (auto it=o->nest.begin(),e=o->nest.end();it!=e;it++)
		push(*it); }
void Sym::share() { glob[val]=this; }


string Sym::ptr() { ostringstream os; os << " @" << this; return os.str(); }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::head() { return "<"+tag+":"+val+">"+ptr(); }
string Sym::dump(int depth) { string S = "\n"+pad(depth)+head();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }

Term::Term(string V):Sym("term",V){ arity=0; }
string Sym::ar() { ostringstream os; os << arity; return os.str(); }
string Term::head() { return val+"/"+ar()+ptr(); }

Var::Var(string V):Sym("var",V){}

Vector::Vector():Sym("vector","[]"){}
void Vector::share(){}

Fn::Fn(string V, FN F):Sym("fn",V) { fn=F; }

Sym* Sym::at(Sym*o) { push(o); return this; }
Sym* Fn::at(Sym*o) { return fn(o); }

int Sym::X=0;
string Sym::i2s(int N) { ostringstream os; os<<N; return os.str(); }

Xn::Xn(Sym*o):Sym("X",i2s(X++)){ push(o); }
void Xn::share(){}
string Xn::head() { return tag+val+" = "+nest[0]->head(); }
string Xn::dump(int depth) { return "\n"+pad(depth)+head(); }

string Sym::id() { return tag+":"+val; }
string Xn::id() { return nest[0]->id(); }

Sym* flat(Sym*o) { return o->flat(); }
Sym* Sym::flat() { Sym*F = new Sym("","");
	Sym* H = new Xn(this); F->push(H);
	map<string,int> sav;
	for (auto it=nest.begin(),e=nest.end();it!=e;it++) {
		Sym *Z = (*it)->flat();
		for (auto zit=Z->nest.begin(),ze=Z->nest.end();zit!=ze;zit++)
			if (!sav[(*zit)->id()]) {
				cerr << (*zit)->id() << endl;
				sav[(*zit)->id()]=1; F->push(*zit); }
	}
	return F; }

map<string,Sym*> glob;
void glob_init(){
	glob["flat"] = new Fn("flat",flat);
}

