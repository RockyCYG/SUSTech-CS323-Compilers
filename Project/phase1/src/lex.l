%top{
	#include "syntax.tab.h"
	#include <math.h>
	#include <string.h>
	#include <string>
	#include <iostream>
	#include <vector>

	#define YYSTYPE Node*

	extern "C" int yylex (void);

	extern void printerror();
}

%{
    #define EXIT_OK 0
    #define EXIT_FAIL 1

    // global variables
    int ids = 0;
    int lines = 1;
    int cols = 0;
    char idmap[105][105];
	bool errorFlag = false;
%}
%x comment
letter [a-zA-Z]
letter_ {letter}|_
digit [0-9]
white [\t\n ]
id ({letter}|_)({letter}|{digit}|_)*
number ([1-9]{digit}*)|0
hexdigit [0-9abcdefABCDEF]

hexnum 0(x|X){hexdigit}+
hexchar \'\\(x|X){hexdigit}+\'
wronghexnum 0(x|X)({digit}|{letter})+
wronghexchar \'\\(x|X)({digit}|{letter})+\'
op "+"|"-"|"*"|"/"
dot "."
semi ";"
comma ","
assign "="
lt "<"
gt ">"
bitop "!"|"^"|"&"|"\|"
lp "\("
rp "\)"
lb "["
rb "]"
lc "{"
rc "}"
notmystery [_a-zA-Z0-9\'\"=;)(}{\+\-\*\/\.,\<\>!\^\&\|\[\]\t\n]
mystery [^ _a-zA-Z0-9\'\"=;)(}{\+\-\*\/\.,\<\>!\^\&\|\[\]\t\n]
all {mystery}|{notmystery}
%%

"/*"         BEGIN(comment);

<comment>[^*\r\n]*     {}   /* eat anything that's not a '*' */
<comment>"*"+[^*/\r\n]*   {}/* eat up '*'s not followed by '/'s */
<comment>\r\n             {++lines;}
<comment>"*"+"/"        BEGIN(INITIAL);
\n {lines++;}
\r\n {lines++;}
"//".* {}
{mystery} {
	/*int i;
	for(i=0;i<cols*4;i++) printf(" ");
	printf("MYSTERIOUS %s (%d)-------------------------\n",yytext,lines);*/
	printerror();
	return ERR;
}
0{digit}+ {printerror();return ERR;}
int { int i;
	/*for(i=0;i<cols*4;i++) printf(" ");printf("TYPE:int\n");/*return TYPE;*/
	yylval = new Node(lines, true, "TYPE: int");
	return TYPE_INT;
}
char { int i;
	/*for(i=0;i<cols*4;i++) printf(" ");printf("TYPE: char\n");/*return TYPE;*/
	yylval = new Node(lines, true, "TYPE: char");
	return TYPE_CHAR;
}
float { int i;
	/*for(i=0;i<cols*4;i++) printf(" ");printf("TYPE: float\n");/*return TYPE;*/
	yylval = new Node(lines, true, "TYPE: float");
	return TYPE_FLOAT;
}
struct {int i;
	/*for(i=0;i<cols*4;i++) printf(" ");
	
	printf("STRUCT\n");*/
	yylval = new Node(lines, true, "STRUCT");
	return STRUCT;
}

if {/*int i;
	for(i=0;i<cols*4;i++) printf(" ");
	printf("IF\n");*/
	yylval = new Node(lines, true, "IF");
	return IF;
}
else {/*int i;
	for(i=0;i<cols*4;i++) printf(" ");
	printf("ELSE\n");*/
	yylval = new Node(lines, true, "ELSE");
	return ELSE;
}
while {/*int i;
	for(i=0;i<cols*4;i++) printf(" ");*/
	/*printf("WHILE\n");*/
	yylval = new Node(lines, true, "WHILE");
	return WHILE;
}
return {int i;
	/*for(i=0;i<cols*4;i++) printf(" ");
	printf("RETURN\n");*/
	yylval = new Node(lines, true, "RETURN");
	return RETURN;
}


{hexnum} {
	/*printf("HEX: %s\n",yytext);*/
	int i,len=strlen(yytext),ret=0;
	for(i=2;i<len;i++){
		int num = yytext[i]>='0'&&yytext[i]<='9'?yytext[i]-'0':(yytext[i]>='a'&&yytext[i]<='f'?yytext[i]-'a'+10:yytext[i]-'A'+10);
		ret = ret*16+num;
	}
	/*printf("HEX num = %d\n",ret);*/
	yylval = new Node(lines, true, "INT: " + std::to_string(ret));
	return HEXNUM;
}
{wronghexnum} {
	/*printf("WRONG HEXNUM\n");*/
	printerror();
	return ERR;
}
{hexchar} {
	int i,len=strlen(yytext),ret=0;
	if(len>6){
		/*printf("HEX TOO LARGE\n");*/
		printerror();
		return ERR;
	}
	for(i=3;i<len-1;i++){
		int num = yytext[i]>='0'&&yytext[i]<='9'?yytext[i]-'0':(yytext[i]>='a'&&yytext[i]<='f'?yytext[i]-'a'+10:yytext[i]-'A'+10);
		ret = ret*16+num;
	}
	/*printf("HEX num = %d\n",ret);*/
	yylval = new Node(lines, true, "CHAR: " + std::string(yytext));
	return HEXCHAR;
}
{wronghexchar} {
	/*printf("WRONG HEXCHAR\n");*/
	printerror();
	return ERR;
}

{digit}+{id} {
	/*addspaces();printf("ID cannot start with digits %s (%d)-------------------------\n",yytext,lines);
	yylval.strval = strdup(yytext);*/
	printerror();
	return ERR;
}
\'.{2,}\' {
	printerror();
	return ERR;
	/*addspaces();printf("Inside \'  \' there must be only one char. %s (%d)----------------------\n",yytext,lines);*/
	/*yylval.strval = strdup(yytext);
	return INVALID_CHAR;*/
}

{number} {
	/*addspaces();printf("INT: %s\n",yytext);*/
	yylval = new Node(lines, true, "INT: " + std::string(yytext));
	return INT;
}
{number}\.({digit}+) {
	/*addspaces();printf("FLOAT: %s\n",yytext);*/
	yylval = new Node(lines, true, "FLOAT: " + std::string(yytext));
	return FLOAT;
}
{number}\.({digit}+)(\.{digit}*)+ {
	printerror();
	return ERR;
}

\'.{1}\' {
	/*addspaces();printf("CHAR: %s\n",yytext);*/
	yylval = new Node(lines, true, "CHAR: " + std::string(yytext));
	return CHAR;
}


{id} {
/*addspaces();*/
	int prev = 0;
	int i;
	for(i = ids;i>=0;i--){
		if(strcmp(yytext,idmap[i])==0){
			prev = 1;
			break;
		}
	}
	yylval = new Node(lines, true, "ID: " + std::string(yytext));
	if(prev == 1){
		/*printf("old ID %s\n",yytext);*/
		/*printf("ID: %s\n",yytext);*/
		return ID;
		/*TODO return a existing ID*/
	}else{
		ids ++;
		strcpy(idmap[ids-1],yytext);
		/*printf("new ID %s\n",yytext);*/
		/*printf("ID: %s\n",yytext);*/
		return ID;
		/*TODO return a new ID*/
	}
}

\. {
	/*printf("DOT\n");*/
	yylval = new Node(lines, true, "DOT");
	return DOT;
}
\; {
	/*printf("SEMI\n");*/
	yylval = new Node(lines, true, "SEMI");
	return SEMI;
}
\, {
	/*printf("COMMA\n");*/
	yylval = new Node(lines, true, "COMMA");
	return COMMA;
}
\<\= {
	/*printf("LE\n");*/
	yylval = new Node(lines, true, "LE");
	return LE;
}
\>\= {
	/*printf("GE\n");*/
	yylval = new Node(lines, true, "GE");
	return GE;
}
\=\= {
	/*printf("EQ\n");*/
	yylval = new Node(lines, true, "EQ");
	return EQ;
}
\!\= {
	/*printf("NE\n");*/
	yylval = new Node(lines, true, "NE");
	return NE;
}
\= {
	/*printf("ASSIGN\n");*/
	yylval = new Node(lines, true, "ASSIGN");
	return ASSIGN;
}
\< {
	/*printf("LT\n");*/
	yylval = new Node(lines, true, "LT");
	return LT;
}
\> {
	/*printf("GT\n");*/
	yylval = new Node(lines, true, "GT");
	return GT;
}
\+ {
	/*printf("PLUS\n");*/
	yylval = new Node(lines, true, "PLUS");
	return PLUS;
}
\- {
	/*printf("MINUS\n");*/
	yylval = new Node(lines, true, "MINUS");
	return MINUS;
}
\* {
	/*printf("MUL\n");*/
	yylval = new Node(lines, true, "MUL");
	return MUL;
}
\/ {
	/*printf("DIV\n");*/
	yylval = new Node(lines, true, "DIV");
	return DIV;
}
\&\& {
	/*printf("AND\n");*/
	yylval = new Node(lines, true, "AND");
	return AND;
}
\|\| {
	/*printf("OR\n");*/
	yylval = new Node(lines, true, "OR");
	return OR;
}
\! {
	/*printf("NOT\n");*/
	yylval = new Node(lines, true, "NOT");
	return NOT;
}
\( {
	/*printf("LP\n");*/
	yylval = new Node(lines, true, "LP");
	return LP;
}
\) {
	/*printf("RP\n");*/
	yylval = new Node(lines, true, "RP");
	return RP;
}
\[ {
	/*printf("LB\n");*/
	yylval = new Node(lines, true, "LB");
	return LB;
}
\] {
	/*printf("RB\n");*/
	yylval = new Node(lines, true, "RB");
	return RB;
}

\{ {
	/*TODO: add functions for []*/
	/*printf("LC\n");
	cols++;
	addspaces();*/
	yylval = new Node(lines, true, "LC");
	return LC;
}
\} {
	/*printf("RC\n");
	cols--;
	if(cols<0) printf("COL MISMATCH: not enough LC (%d)\n",lines);
	else addspaces();*/
	yylval = new Node(lines, true, "RC");
	return RC;
}

[\t\r ]+ { /* does nothing when seeing white spaces except new line */ }
. { printerror();return ERR;

/* a final rule that matches when seeing any character but new line */ }


%%
void printerror(){
	errorFlag = true;
	printf("Error type A at Line %d: unknown lexeme %s\n",lines,yytext);
	/*char c;
	while(1){
		c = yyinput();
		if(c=='\n'){
			lines++;
			return;		
		}
	}*/
}
/*void addspaces(){
	int i;
	for(i=0;i<cols*4;i++) printf(" ");
}*/