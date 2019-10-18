%{
    #include<stdio.h>

    extern YYSTYPE yylval;
%}

%%
"sin"     return SIN;
"cos"     return COS;
"tan"     return TAN;
"sqrt"    return SQRT;
"pow"     return POW;
"ln"	  return LN;
"log10"	  return LOG10;
"exp"	  return EXP;

[0-9]+  {
            yylval=atoi(yytext);
            return NUMBER;
        }
[\t]    ;
[\n]    return 0;
.       return yytext[0];

%%

int yywrap()
{
    return 1;
}