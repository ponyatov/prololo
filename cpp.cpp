#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { glob_init(); return yyparse(); }

Sym::Sym(string V){ val=V; }
string Sym::ptr() { ostringstream os; os << this; return os.str(); }
string Sym::dump() { return "<"+val+"@"+ptr()+">"; }

map<string,Sym*> glob;
void glob_init() {

}
