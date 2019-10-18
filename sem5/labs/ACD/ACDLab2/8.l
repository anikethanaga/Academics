%{
int count=0;
%}
ab .*ab
%%
{ab} {count=count+1;}
. ;
%%
void main()
{
	yylex();
	printf("count is %d\n",count);
}
