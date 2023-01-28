%{
	#include <string>
	#include <iostream>
	#include <fstream>
	#include <vector>
	#include "node.hpp"
	#include "symbol.hpp"
	#include "semantic.hpp"
	#include "translate.hpp"

	Node* root;

	#define YYSTYPE Node*
    #include "lex.yy.c"

    void yyerror(char*);

	extern vector<int> LC_stack;
%}


%token INT FLOAT CHAR ID TYPE STRUCT IF ELSE WHILE RETURN DOT SEMI COMMA LC RC TYPE_INT TYPE_FLOAT TYPE_CHAR HEXNUM HEXCHAR ERR
%nonassoc LOWER_ELSE
%nonassoc ELSE
%right ASSIGN
%left OR
%left AND
%left LT LE GT GE NE EQ
%left PLUS MINUS
%left MUL DIV
%right NOT
%left DOT LP RP LB RB

%%
	Program :	
		ExtDefList	
		{
			int line = $1-> line;
			Node* res=new Node(line,false,"Program");
			res->addEdge($1);
			$$ = res;
			root= $$;
		}
		| error {printf("Error type B at Line %d: syntax error.\n",lines); }
	;
	ExtDefList :	
		ExtDef ExtDefList	
		{	
			// if ($2->line == 0){
			// 	int line = $1-> line;
			// 	Node* res=new Node(line,false,"ExtDefList");
			// 	res->addEdge($1);
			// 	$$ = res;
			// }
			// else {
			// 	int line = $1->line;
			// 	Node* res=new Node(line,false,"ExtDefList");
			// 	res->addEdge($1);
			// 	res->addEdge($2);
			// 	$$ = res;
			// }
			int line = $1->line;
			Node* res=new Node(line,false,"ExtDefList");
			res->addEdge($1);
			res->addEdge($2);
			$$ = res;
		}
	|
		{
			int line = 0;
			Node* res=new Node(line,false,"ExtDefList");
			$$ = res;
		}	
	;
	ExtDef :
	 	Specifier ExtDecList SEMI
		{
			int line=$1->line;
			Node* res=new Node(line,false,"ExtDef");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$ =res;
		}
	|	Specifier ExtDecList error { printf("Error type B at Line %d: syntax error, probably ",$2->line); printf("missing SEMI\n");}
	| 	Specifier SEMI
		{
			int line=$1->line;
			Node* res=new Node(line,false,"ExtDef");
			res->addEdge($1);
			res->addEdge($2);
			$$=res;
		}
	| 	Specifier FunDec CompSt SEMI error
	{
		printf("Error type B at Line %d: syntax error, probably ",$1->line); printf("redundant SEMI\n");
	}
	| 	Specifier error
	{
		printf("Error type B at Line %d: syntax error, probably ",$2->line); printf("missing SEMI\n");
	}
	| 	Specifier FunDec CompSt 
		{
			int line=$1->line;
			Node* res=new Node(line,false,"ExtDef");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$ =res;
		}
	|	error FunDec CompSt { printf("Error type B at Line %d: syntax error, probably ",$2->line); printf("missing specifier\n");}
	;
	ExtDecList :
		VarDec
		{
			int line=$1->line;
			Node* res=new Node(line,false,"ExtDecList");
			res->addEdge($1);
			$$=res;
		}
	| 	VarDec COMMA ExtDecList
		{
			int line=$1->line;
			Node* res=new Node(line,false,"ExtDecList");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}
	;
	
	/*specifier*/
	
	Specifier :
		TYPE_INT 	
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Specifier");
			res->addEdge($1);
			$$=res;
		}
	|	TYPE_FLOAT
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Specifier");
			res->addEdge($1);
			$$=res;
		
		}
	|	TYPE_CHAR
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Specifier");
			res->addEdge($1);
			$$=res;
		}
	|	StructSpecifier
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Specifier");
			res->addEdge($1);
			$$=res;
		}
	;
	StructSpecifier :
		STRUCT ID LC DefList RC
		{
			int line = $1->line;
			Node* res=new Node(line,false,"StructSpecifier");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			// if ($4->line!=0)res->addEdge($4);
			res->addEdge($4);
			res->addEdge($5);
			$$ = res;
		}
	|	STRUCT ID LC DefList error { printf("Error type B at Line %d: syntax error, probably ",$4->line); printf("missing RC\n");}
	|	STRUCT ID
		{
			int line = $1->line;
			Node* res=new Node(line,false,"StructSpecifier");
			res->addEdge($1);
			res->addEdge($2);
			$$=res;
		}
	;
		
	/*declarator*/
	VarDec :
		ID				
		{
			int line = $1->line;
			Node* res=new Node(line,false,"VarDec");
			res->addEdge($1);
			$$ = res;
		}
	|	ERR	
		
	|VarDec LB INT RB
		{
			int line = $1->line;
			Node* res=new Node(line,false,"VarDec");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			res->addEdge($4);
			$$ = res;
		}
	|	VarDec LB INT error { printf("Error type B at Line %d: syntax error, probably ",$3->line); printf("missing RB\n"); }
	|	error {printf("Error type B at Line %d: syntax error, probably ",$1->line); printf("Var can not be Exp\n"); }
	;
	FunDec :
		ID LP VarList RP
		{
			int line = $1->line;
			Node* res=new Node(line,false,"FunDec");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			res->addEdge($4);
			$$ = res;
		}
	|	ID LP RP 			 
		{
			int line = $1->line;
			Node* res=new Node(line,false,"FunDec");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$ = res;
		}
	|	ID LP VarList error {printf("Error type B at Line %d:",$3->line); printf("missing RP\n");}

	|	ID LP error { printf("Error type B at Line %d: syntax error, probably ",$2->line); printf("missing RP\n");}
	;	
	VarList:
		ParamDec COMMA VarList
		{	int line = $1->line;
			Node* res=new Node(line,false,"VarList");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$ = res;
		}
	|	ParamDec
		{
			int line = $1->line;
			Node* res=new Node(line,false,"VarList");
			res->addEdge($1);
			$$ = res;
		}
	;
	ParamDec:
		Specifier VarDec
		{
			int line = $1->line;
			Node* res=new Node(line,false,"ParamDec");
			res->addEdge($1);
			res->addEdge($2);
			$$ = res;
		}
	;
	/*statement*/
	CompSt :
		LC DefList StmtList RC
		{

			int line = $1->line;
			Node* res=new Node(line,false,"CompSt");
			res->addEdge($1);
			// if ($2->line!=0)res->addEdge($2);
			// if ($3->line!=0)res->addEdge($3);
			res->addEdge($2);
			res->addEdge($3);
			res->addEdge($4);
			$$ = res;
		}
	|	LC DefList StmtList error { printf("Error type B at Line %d: syntax error, probably ",$3->line); printf("missing RC\n");}
	|	LC DefList StmtList DefList error {printf("Error type B at Line %d: syntax error, probably ",$4->line); printf("missing specifier\n");}
	;
	StmtList :
		Stmt StmtList
		{
			int line = $1->line;
			Node* res=new Node(line,false,"StmtList");
			res->addEdge($1);
			// if ($2->line!=0)res->addEdge($2);
			res->addEdge($2);
			$$ = res;
		}
	|	
		{
			int line = 0;
			Node* res=new Node(line,false,"StmtList");
			$$ = res;
		}
	;
	Stmt	:
		Exp SEMI
		{
			int line = $1->line;
			Node* res=new Node(line,false,"Stmt");
			res->addEdge($1);
			res->addEdge($2);
			$$ =res;
		}
	|   SEMI error
		{
			printf("Error type B at Line %d: syntax error, probably ",$1->line); printf("Missing Expression\n");
		}
	|	Exp error { printf("Error type B at Line %d: syntax error, probably ",$1->line); printf("Missing SEMI\n");}
	|	CompSt
		{
			int line = $1->line;
			Node* res=new Node(line,false,"Stmt");
			res->addEdge($1);
			$$ =res;
		}
	|	RETURN Exp SEMI
		{
			int line = $1->line;
			Node* res=new Node(line,false,"Stmt");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$ =res;		
		}
	|	RETURN Exp error  {printf("Error type B at Line %d: syntax error, probably ",$1->line);  printf("Missing SEMI\n");}
	|	IF LP Exp RP Stmt %prec LOWER_ELSE
		{
			int line = $1->line;
			Node* res=new Node(line,false,"Stmt");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			res->addEdge($4);
			res->addEdge($5);
			$$ =res;		
		}
	|	IF LP Exp RP Stmt ELSE Stmt
		{
			int line = $1->line;
			Node* res=new Node(line,false,"Stmt");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			res->addEdge($4);
			res->addEdge($5);
			res->addEdge($6);
			res->addEdge($7);
			$$ =res;		
		}
	|	WHILE LP Exp RP Stmt
		{
			int line = $1->line;
			Node* res=new Node(line,false,"Stmt");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			res->addEdge($4);
			res->addEdge($5);
			$$ =res;		
		}
	;
	
	
	/*local definition*/
	DefList:
		Def DefList
		{
			int line = $1->line;
			Node*res=new Node(line,false,"DefList");
			res->addEdge($1);
			// if ($2->line !=0)res->addEdge($2);
			res->addEdge($2);
			$$=res;
		}
	|	
		{
			int line=0;
			Node* res=new Node(line,false,"DefList");
			$$=res;
		}
	;
	Def :
		Specifier DecList SEMI
		{
			int line=$1->line;
			Node*res=new Node(line,false,"Def");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}
		|Specifier DecList error
		{
			printf("Error type B at Line %d: syntax error, probably ",$2->line); 
			printf("Missing SEMI\n");
		}
	;
	DecList:
		Dec
		{
			int line=$1->line;
			Node*res=new Node(line,false,"DecList");
			res->addEdge($1);
			$$=res;
		}
	|	Dec COMMA DecList
		{
			int line=$1->line;
			Node*res=new Node(line,false,"DecList");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}
	;
	Dec :
		VarDec
		{
			int line=$1->line;
			Node*res=new Node(line,false,"Dec");
			res->addEdge($1);
			$$=res;
		}
	|	VarDec ASSIGN Exp
		{
			int line=$1->line;
			Node*res=new Node(line,false,"Dec");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}
	;
	/*expression*/
	Exp :
		Exp ASSIGN Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}
	| 	Exp AND Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}
	| 	Exp OR Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}
	| 	Exp LT Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}

	| 	Exp LE Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}

	| 	Exp GT Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}

	| 	Exp GE Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}

	| 	Exp NE Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}

	| 	Exp EQ Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}

	| 	Exp PLUS Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}

	| 	Exp MINUS Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}

	| 	Exp MUL Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}

	| 	Exp DIV Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}

	| 	LP Exp RP			
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}

	| 	LP Exp error  {printf("Error type B at Line %d: syntax error, probably ",$2->line);  printf("missing RP\n");}			
	| 	MINUS Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			$$=res;
		}

	| 	NOT Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			$$=res;
		}

	| 	ID LP Args RP	
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			res->addEdge($4);
			$$=res;
		}
	| 	ID LP Args error {printf("Error type B at Line %d: syntax error, probably ",$1->line);  printf("missing RP\n");}	
	| 	ID LP RP	
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}		
	| 	ID LP error { printf("Error type B at Line %d: syntax error, probably ",$1->line); printf("missing RP\n");}		
	| 	Exp LB Exp RB
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			res->addEdge($4);
			// res->addEdge(res);
			$$=res;
		}
	| 	Exp LB Exp error {printf("Error type B at Line %d: syntax error, probably ",$1->line);  printf("missing RB\n");}
	| 	Exp DOT ID
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$=res;
		}		
	| 	ID	
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			$$=res;
		}		
	| 	INT
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			$$=res;
		}		
	| 	FLOAT
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			$$=res;
		}		
	| 	CHAR
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			$$=res;
		}		
	|	HEXNUM
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			$$=res;
		}		
	|	HEXCHAR
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Exp");
			res->addEdge($1);
			$$=res;
		}		
	|	ERR 
	|	Exp ERR Exp
	;
	Args :
		Exp COMMA Args
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Args");
			res->addEdge($1);
			res->addEdge($2);
			res->addEdge($3);
			$$ = res;
		}
	|	Exp
		{
			int line=$1->line;
			Node* res=new Node(line,false,"Args");
			res->addEdge($1);
			$$ = res;	
		}
	;
%%

void yyerror(char* s) {
	errorFlag = true;
}

int main(int argc, char **argv){
    char *file_path;
    if(argc < 2){
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAIL;
    } else if(argc == 2){
        file_path = argv[1];
        if(!(yyin = fopen(file_path, "r"))){
            perror(argv[1]);
            return EXIT_FAIL;
        }
        yyparse();
		if (!errorFlag){
			LC_stack.push_back(0);
			init();
			Build(root);
		}
		if (!errorFlag) {
			// printAST(root, 0);
		}
		if (!errorFlag) {
			const string ir_code = translate(root);
			string input_file(file_path);
			string output_file = input_file.substr(0, input_file.rfind('.')) + ".ir";
			ofstream os;
			os.open(output_file);
			os << ir_code;
			os.close();
		}
	// print_all_member("Apple");
        return EXIT_OK;
    } else {
        fputs("Too many arguments! Expected: 2.\n", stderr);
        return EXIT_FAIL;
    }
	// print_all_variables();
}
