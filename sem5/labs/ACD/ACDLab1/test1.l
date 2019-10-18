%{
	int count=0;
%}
alpha [a-zA-Z]
digit [0-9]
space [ \t\n]
start ^a

%%

{start}							{count++;}
{space}(a|A)({alpha}|{digit})*	{count++;}
.								;

%%

main()
{
	yylex();
	printf("Count=%d\n",count);
}