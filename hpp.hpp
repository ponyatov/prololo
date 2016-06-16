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
	virtual string flat(int=0); static int X;
	int arity; string ar();
};

extern map<string,Sym*> glob;
extern void glob_init();

struct Term: Sym { Term(string); string head(); };
struct Var: Sym { Var(string); };

struct Vector: Sym { Vector(); void share(); };

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = glob[yytext]; \
	if (!yylval.o) yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_HPP
