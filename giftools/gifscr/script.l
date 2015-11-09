%{
char *func=0;
char *strKeep(char *);
%}
%%
^[^ \t\n]+/[ \t]*\n	{ printf("%s[]\n", yytext); }
^[^ \t\n]+		func = strKeep(yytext);
[^ \t\n]+		{
			  if(func) printf("%s(%s)\n", func, yytext);
			  else printf("???[%s]\n", yytext);
			}
%%
char *strKeep(char *str){
  static char keep[256];
/*  printf("mode:%s\n", str);
*/
  strncpy(keep, str, 256);
}
