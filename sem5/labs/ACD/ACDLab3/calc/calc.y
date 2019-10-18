%{
    #include<stdio.h>
    #define YYSTYPE double
    #include<math.h>
    int flag=0;

%}

%token NUMBER SQRT POW SIN COS TAN LN LOG10 EXP
%left '+' '-'
%left '*' '/' '%'

%left '(' ')'

%%

ArithmeticExpression    :   E{
                                printf("\nResult=%f\n",(double)$$);
                                return 0;
                            };

E                       :   '('E')' {$$=$2;}
                            |SIN'('E')' {$$=sin($3);}
                            |COS'('E')' {$$=cos((float)$3);}
                            |TAN'('E')' {$$=tan($3);}
                            |SQRT'('E')' {$$=sqrt($3);}
                            |POW'('E','E')' {$$=pow($3, $5);}
                            |LN'('E')' {$$=log($3);}
                            |LOG10'('E')' {$$=log10($3);}
                            |EXP'('E')' {$$=pow(2.71828, $3);}
                            |E'+'E {$$=$1+$3;}
                            |E'-'E {$$=$1-$3;}
                            |E'*'E {$$=$1*$3;}
                            |E'/'E {$$=$1/$3;}
                            |NUMBER {$$=$1;}
                            ;

%%

#include "lex.yy.c"

void main()
{
    printf("\nEnter Any Arithmetic Expression:\n");
    yyparse();
    if(flag==0)
    printf("\nEntered arithmetic expression is Valid\n\n");

}
