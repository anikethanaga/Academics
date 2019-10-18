%{
	int plus=0,sub=0,mul=0,division=0,idt=0;
	int lb=0,rb=0;
%}
id [a-zA-Z][a-zA-Z]*|[0-9]
lbr [\(]
rbr [\)]
%%
{id} {idt++;printf("\n%s is an identifier",yytext);}
"+" {plus++;printf("\n%s is a operator",yytext);}
"-" {sub++;printf("\n%s is a operator",yytext);}
"*" {mul++;printf("\n%s is a operator",yytext);}
"/" {division++;printf("\n%s is a operator",yytext);}
{lbr} {lb++;}
{rbr} {rb++;}
%%
void main()
{
	yylex();
	if((lb==rb) && (idt-(plus+sub+mul+division)==1))
	{
		printf("\nThe expression is consistent\n");
		if(idt>0){printf("The expression  contains %d operands\n",idt);}
		if((plus+sub+mul+division)>0){printf("The expression contains %d operators\n",plus+sub+mul+division);}
		if(plus>0){printf("There are %d Plus operators\n",plus);}
		if(sub>0)
		{printf("There are %d Subtraction operators\n",sub);}
		if(mul>0){printf("There are %d Multiplication operators\n",mul);}
		if(division>0){printf("There are %d Division operators\n",division);}

	}
	else{printf("The expression is incorrect\n");}
}