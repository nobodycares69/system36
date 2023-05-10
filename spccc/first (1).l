%{
	#define NUM 1
	#define KEY 2
	#define ID 3
	#define DEC 4
%}

%%
[0-9]+ {return NUM;}
int|char|float|return {return KEY;}
[a-zA-Z]+[a-zA-Z0-9]* {return ID;}
[0-9]+\.[0-9]+ {return DEC;}
%%

#include<stdio.h>
int yywrap(){}
int main(int argc, char *argv[])
	{
		int val;
		while(val=yylex())
		{
			switch(val){
				case 1: printf("\n %s Number", yytext);
						break;
				case 2: printf("\n %s Key", yytext);
						break;
				case 3: printf("\n &s Id", yytext);
						break;
				case 4: printf("\n %s Decimal",yytext);
						break;
				default: printf("error");
			}
		}
	}
