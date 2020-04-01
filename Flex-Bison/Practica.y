%{
#include <stdio.h>
void yyerror(char *mensaje){
    printf("Error: %s", mensaje);
}
%}

%token ENTER MAS ENTERO
%%
programa: linea
| programa linea

linea: expresion ENTER                  {printf("R=%d\n", $1);}
| ENTER
;
expresion: expresion MAS ENTERO         { $$ = $1 + $3;}
| ENTERO                                { $$ = $1;}
;

%%

int main(void){
    //$2 corresponde al valor del más en la expresion MAS ENTERO
    //$1 es el valor del nodo
    //$$ es el valor del padre
    //Invoca al analizador sintactico de la lista de tokens
    return yyparse();
}