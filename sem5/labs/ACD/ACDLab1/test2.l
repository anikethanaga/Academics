%{
int count=0;
%}

%%
.*com\n {count++;ECHO;}
. ;

%%

main()
{
	yylex();
	printf("\nCount = %d\n",count);
	return 0;
}