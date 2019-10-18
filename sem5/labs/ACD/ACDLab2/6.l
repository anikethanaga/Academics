%{
	#include <stdio.h>
	int flag=0;
%}
conn [a-zA-Z ]*" or "|" and "|" for "|" nor "|" but "|" yet "|" so "[a-zA-Z ]*("."|"?")
%%
{conn} {printf("Compound Sentence");flag++;}
. ;
%%
void main()
{
	yylex();
	if(flag==1)
	{
		printf("Simple sentence\n");
		flag=0;
	}
}