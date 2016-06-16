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
	Sym(string,string); Sym(string);
	vector<Sym*> nest; void push(Sym*);
	virtual void share();
	virtual string dump(int=0); virtual string head();
	string ptr(); string pad(int);
};

extern map<string,Sym*> glob;
extern void glob_init();

struct Vector: Sym { Vector(); void share(); };

struct Term: Sym { Term(string); };
struct Var: Sym { Var(string); };

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = glob[yytext]; \
	if (!yylval.o) yylval.o=new C(yytext); \
	return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_HPP
