%{
#include <stdlib.h>
#include "Practica.tab.h"
%}

%%
[0-9]+ {yylval = atoi(yytext); return ENTERO;//Asigna valores a los tokens con yylval y lo asiga a ENTERO}
\+     {return MAS;}
\n     {return ENTER;}
.

%%