lower [a-z]
CAPS [A-Z]
space [ \n\t]

%%
{lower}			{printf("%c",yytext[0]-32);}
{CAPS}			{printf("%c",yytext[0]+32);}
{space}			ECHO;
.				ECHO;
%%

int main()
{
	yylex();
	return 0;
}