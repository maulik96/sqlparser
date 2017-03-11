%{
void yyerror(char *s);
#include <stdio.h>
#include <stdlib.h>

%}

%start stmts

%union {
	int intval;
	double floatval;
	char *strval;
	int subtok;
}

%token <strval> IDENTIFIER
%token <strval> STRING_LITERAL
%token <intval> INT_LITERAL


%token CREATE
%token TABLE
%token INSERT
%token INTO
%token SELECT
%token FROM
%token WHERE
%token UPDATE
%token PRIMARY
%token INDEX
%token FOREIGN
%token KEY
%token DEFAULT
%token NOT
%token NULL_TOKEN
%token AND
%token OR
%token XOR
%token ALL
%token SOME
%token ANY
%token BIT
%token INT
%token INTEGER
%token BIGINT
%token REAL
%token DOUBLE
%token FLOAT
%token DECIMAL
%token COMPARATOR
%token REFERENCES
%token ORDER
%token BY
%token DELETE
%token DATATYPE
%token VALUES
%token AUTO_INCREMENT
%token ASC
%token DESC
%token UNIQUE
%token IN
%token TRUE
%token FALSE
%token DISTINCT
%token SET
%token DROP
%token ALTER
%token ADD
%token COLUMN
%token ALL_COLUMN
%token BRACKET_OPEN
%token BRACKET_CLOSE
%token SEMICOLON
%token COMMA
%token INVALID

%%

stmts: stmt SEMICOLON 
  | stmts stmt SEMICOLON 
  ;

stmt: select_stmt
	| create_stmt
	| insert_stmt
	| update_stmt
	| delete_stmt
	| drop_table_stmt
	| drop_col_stmt
	| add_col_stmt
	;

create_stmt: CREATE TABLE IDENTIFIER BRACKET_OPEN create_col_list BRACKET_CLOSE
	;

create_col_list: create_definition 
    | create_col_list COMMA create_definition 
    ;

create_definition : IDENTIFIER data_type column_atts
	| PRIMARY KEY BRACKET_OPEN column_list BRACKET_CLOSE
	| KEY BRACKET_OPEN column_list BRACKET_CLOSE        
	| INDEX BRACKET_OPEN column_list BRACKET_CLOSE 
	;

column_list: IDENTIFIER
	| column_list COMMA IDENTIFIER
	;

data_type :
	  BIT opt_length
	| INT opt_length
	| INTEGER opt_length
	| BIGINT opt_length
	| REAL opt_length
	| DOUBLE opt_length
	| FLOAT opt_length
	| DECIMAL opt_length 
  	;

opt_length :
	| BRACKET_OPEN INT_LITERAL BRACKET_CLOSE
	;

column_atts: 
    | column_atts NOT NULL_TOKEN            
    | column_atts DEFAULT STRING_LITERAL       
    | column_atts DEFAULT INT_LITERAL       
    | column_atts AUTO_INCREMENT    
    ;   

insert_stmt : INSERT INTO IDENTIFIER opt_col_names VALUES BRACKET_OPEN insert_vals_list BRACKET_CLOSE
	;

insert_vals_list : expr
	| insert_vals_list COMMA expr

opt_col_names : 
	| BRACKET_OPEN column_list BRACKET_CLOSE
	;


update_stmt : UPDATE IDENTIFIER SET update_asign_list opt_where
	;

update_asign_list : IDENTIFIER COMPARATOR expr
	| update_asign_list COMMA IDENTIFIER COMPARATOR expr


delete_stmt : DELETE FROM IDENTIFIER opt_where

drop_table_stmt : DROP TABLE IDENTIFIER

drop_col_stmt : ALTER TABLE IDENTIFIER DROP COLUMN IDENTIFIER

add_col_stmt : ALTER TABLE IDENTIFIER ADD COLUMN create_definition

select_stmt: SELECT select_opts select_expr_list FROM IDENTIFIER opt_where 
	;

select_opts:	
	| DISTINCT
	| ALL
	;

select_expr_list: expr 
    | select_expr_list COMMA expr 
    | ALL_COLUMN
    ;

opt_where: 
	| WHERE expr 
	;



expr: expr COMPARATOR expr
	| expr OR expr
	| expr AND expr
	| expr XOR expr
	| NOT expr
	| expr COMPARATOR BRACKET_OPEN select_stmt BRACKET_CLOSE
	| expr COMPARATOR ANY BRACKET_OPEN select_stmt BRACKET_CLOSE
	| expr COMPARATOR SOME BRACKET_OPEN select_stmt BRACKET_CLOSE
	| expr COMPARATOR ALL BRACKET_OPEN select_stmt BRACKET_CLOSE
	;

expr: IDENTIFIER          { printf("Identifier\n"); free($1); }
	| STRING_LITERAL {printf("string literal %s\n", $1);}   
	| INT_LITERAL {printf("int literal %d\n", $1);}   
   	;
%%

int main(void)
{
	return yyparse();
}

void yyerror(char *s)
{
	fprintf(stderr, "%s\n", s);
}