%{
	#include<stdio.h>
	#include<string.h>
	char p[50],q[50];

%}
word [a-zA-Z]+
eol "\n"
%%
{word} {if (strcmp(p,yytext)==0){printf("%s",q);}else{printf("%s",yytext);}}
. {printf("%s",yytext);}
%%
void main()
{
	printf("Enter the word to be found\n");
	scanf("%s",p);
	printf("Enter the word to replace the above word with\n");
	scanf("%s",q);
	yylex();
}