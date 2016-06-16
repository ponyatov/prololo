#ifndef _H_HPP
#define _H_HPP

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

struct Sym {
	string tag,val;
	Sym(string,string); Sym(string); virtual void share();
	vector<Sym*> nest; void push(Sym*); void pushV(Sym*);
	virtual string dump(int=0); virtual string head(); string pad(int);
	virtual string ptr();
	int arity; string ar();
	virtual Sym* at(Sym*);
	virtual Sym* flat(); static int X;
	static string i2s(int);
};

extern map<string,Sym*> glob;
extern void glob_init();

struct Term: Sym { Term(string); string head(); };
struct Var: Sym { Var(string); };

struct Xn: Sym { Xn(int,Sym*); Sym*term; void share(); string head(); };

struct Vector: Sym { Vector(); void share(); };

typedef Sym*(*FN)(Sym*);
struct Fn: Sym { Fn(string,FN); FN fn; Sym*at(Sym*); };

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = glob[yytext]; \
	if (!yylval.o) yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_HPP
