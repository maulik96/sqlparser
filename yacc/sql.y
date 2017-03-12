%{
void yyerror(const char *s);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int yylex();

enum treetype {nonterminal_node, keyword_node, number_node, string_node, identifier_node};
typedef struct tree {
    enum treetype nodetype;
    struct tree *children[10];
    int number, size;
    char label[20];
    char keyword[100];
    char string[100];
} tree;

tree *make_nonterminal(char label[], int n, ...){
    tree *result= (tree*) malloc (sizeof(tree));
    result->nodetype = nonterminal_node;
    strcpy(result->label, label);
    result->size = n;
    int i;
    va_list valist;
    va_start(valist, n);
    for(i=0;i<n;i++)
        result->children[i] = va_arg(valist, tree *);
    return result;
}

tree *make_number(int n) {
    tree *result= (tree*) malloc (sizeof(tree));
    result->nodetype= number_node;
    result->number= n;
    return result;
}


tree *make_string (char v[]) {
    tree *result= (tree*) malloc (sizeof(tree));
    result->nodetype= string_node;
    strcpy(result->string, v);
    return result;
}

tree *make_kw (char kw[], char str[]) {
    tree *result= (tree*) malloc (sizeof(tree));
    result->nodetype= keyword_node;
    strcpy(result->keyword, kw);
    strcpy(result->string, str);
    return result;
}

tree *make_identifier (char v[]) {
    tree *result= (tree*) malloc (sizeof(tree));
    result->nodetype= identifier_node;
    strcpy(result->string, v);
    return result;
}


void printTree(tree *root, int level)
{
    int i;
    if(root->nodetype == nonterminal_node)
    {
        printf("%*s%s\n", level, "", root->label);
        for(i=0;i<root->size;i++)
            printTree(root->children[i], level + 4);
    }
    else if(root->nodetype == number_node)
        printf("%*sNUM_LITERAL -- %d\n", level, "", root->number);
    else if(root->nodetype == keyword_node)
        printf("%*s%s -- %s\n", level, "", root->keyword, root->string);
    else if(root->nodetype == string_node)
        printf("%*sSTRING_LITERAL -- %s\n", level, "", root->string);
    else
        printf("%*sIDENTIFIER -- %s\n",level, "", root->string);
}

%}

%define parse.error verbose

%start stmts

%union {
    int intval;
    char *strval;
    struct tree *a_tree;
}

%token <strval> IDENTIFIER
%token <strval> STRING_LITERAL
%token <intval> INT_LITERAL


%token <strval> CREATE
%token <strval> TABLE
%token <strval> INSERT
%token <strval> INTO
%token <strval> SELECT
%token <strval> FROM
%token <strval> WHERE
%token <strval> UPDATE
%token <strval> PRIMARY
%token <strval> INDEX
%token <strval> FOREIGN
%token <strval> KEY
%token <strval> DEFAULT
%token <strval> NOT
%token <strval> NULL_TOKEN
%token <strval> AND
%token <strval> OR
%token <strval> XOR
%token <strval> ALL
%token <strval> SOME
%token <strval> ANY
%token <strval> BIT
%token <strval> INT
%token <strval> INTEGER
%token <strval> BIGINT
%token <strval> REAL
%token <strval> DOUBLE
%token <strval> FLOAT
%token <strval> DECIMAL
%token <strval> CHAR
%token <strval> VARCHAR
%token <strval> COMPARATOR
%token <strval> REFERENCES
%token <strval> ORDER
%token <strval> BY
%token <strval> DELETE
%token <strval> DATATYPE
%token <strval> VALUES
%token <strval> AUTO_INCREMENT
%token <strval> ASC
%token <strval> DESC
%token <strval> UNIQUE
%token <strval> IN
%token <strval> TRUE
%token <strval> FALSE
%token <strval> DISTINCT
%token <strval> SET
%token <strval> DROP
%token <strval> ALTER
%token <strval> ADD
%token <strval> COLUMN
%token <strval> ALL_COLUMN
%token <strval> BRACKET_OPEN
%token <strval> BRACKET_CLOSE
%token <strval> SEMICOLON
%token <strval> COMMA
%token <strval> INVALID

%type <a_tree>  stmts stmt create_stmt create_col_list create_definition  column_list data_type  opt_length  column_atts insert_stmt  insert_vals_list  opt_col_names  update_stmt  update_asign_list  delete_stmt  drop_table_stmt  drop_col_stmt  add_col_stmt  select_stmt select_opts select_expr_list opt_where expr

%%

stmts: stmt SEMICOLON {$$ = make_nonterminal("stmts", 2,$1,make_kw("SEMICOLON", $2)); printTree($$,0);}
  ;

stmt: select_stmt       { $$ = make_nonterminal("stmt",1,$1); }
    | create_stmt       { $$ = make_nonterminal("stmt",1,$1); }
    | insert_stmt       { $$ = make_nonterminal("stmt",1,$1); }
    | update_stmt       { $$ = make_nonterminal("stmt",1,$1); }
    | delete_stmt       { $$ = make_nonterminal("stmt",1,$1); }
    | drop_table_stmt       { $$ = make_nonterminal("stmt",1,$1); }
    | drop_col_stmt     { $$ = make_nonterminal("stmt",1,$1); }
    | add_col_stmt  { $$ = make_nonterminal("stmt",1,$1); }
    ;



create_stmt: CREATE TABLE IDENTIFIER BRACKET_OPEN create_col_list BRACKET_CLOSE {
    $$ = make_nonterminal("create_stmt", 6, make_kw("CREATE", $1),make_kw("TABLE", $2),make_identifier($3),make_kw("BRACKET_OPEN",$4),$5,make_kw("BRACKET_CLOSE", $6));
}
    ;

create_col_list: create_definition {$$ = make_nonterminal("create_col_list",1,$1);}
    | create_col_list COMMA create_definition {$$ = make_nonterminal("create_col_list",3,$1,make_kw("COMMA",$2),$3);}
    ;

create_definition : IDENTIFIER data_type column_atts {$$ = make_nonterminal("create_definition",3,make_identifier($1),$2,$3);}
    | PRIMARY KEY BRACKET_OPEN column_list BRACKET_CLOSE {$$ = make_nonterminal("create_definition",5,make_kw("PRIMARY",$1),make_kw("KEY",$2),make_kw("BRACKET_OPEN",$3),$4,make_kw("BRACKET_CLOSE",$5));}
    | KEY BRACKET_OPEN column_list BRACKET_CLOSE    {$$ = make_nonterminal("create_definition",4,make_kw("KEY",$1),make_kw("BRACKET_OPEN",$2),$3,make_kw("BRACKET_CLOSE",$4));}    
    | INDEX BRACKET_OPEN column_list BRACKET_CLOSE  {$$ = make_nonterminal("create_definition",4,make_kw("INDEX",$1),make_kw("BRACKET_OPEN",$2),$3,make_kw("BRACKET_CLOSE",$4));}
    ;

column_list: IDENTIFIER {$$ = make_nonterminal("column_list", 1, make_identifier($1));}
    | column_list COMMA IDENTIFIER {$$ = make_nonterminal("column_list", 3,$1,make_kw("COMMA",$2), make_identifier($3));}
    ;

data_type :
      BIT opt_length    {$$ = make_nonterminal("data_type", 2, make_kw("BIT", $1), $2);}
    | INT opt_length    {$$ = make_nonterminal("data_type", 2, make_kw("INT", $1), $2);}
    | INTEGER opt_length    {$$ = make_nonterminal("data_type", 2, make_kw("INTEGER", $1), $2);}
    | BIGINT opt_length {$$ = make_nonterminal("data_type", 2, make_kw("BIGINT", $1), $2);}
    | REAL opt_length   {$$ = make_nonterminal("data_type", 2, make_kw("REAL", $1), $2);}
    | DOUBLE opt_length {$$ = make_nonterminal("data_type", 2, make_kw("DOUBLE", $1), $2);}
    | FLOAT opt_length  {$$ = make_nonterminal("data_type", 2, make_kw("FLOAT", $1), $2);}
    | DECIMAL opt_length    {$$ = make_nonterminal("data_type", 2, make_kw("DECIMAL", $1), $2);}
    | CHAR opt_length   {$$ = make_nonterminal("data_type", 2, make_kw("CHAR", $1), $2);}
    | VARCHAR opt_length    {$$ = make_nonterminal("data_type", 2, make_kw("VARCHAR", $1), $2);}
    ;

opt_length :    {$$ = make_nonterminal("opt_length",0);}
    | BRACKET_OPEN INT_LITERAL BRACKET_CLOSE    {$$ = make_nonterminal("opt_length",3,make_kw("BRACKET_OPEN",$1),make_number($2),make_kw("BRACKET_CLOSE",$3));}
    ;

column_atts: {$$ = make_nonterminal("column_atts",0);}
    | column_atts NOT NULL_TOKEN            {$$ = make_nonterminal("column_atts", 3, $1,make_kw("NOT",$2),make_kw("NULL_TOKEN",$3));}
    | column_atts DEFAULT STRING_LITERAL       {$$ = make_nonterminal("column_atts", 3, $1,make_kw("DEFAULT",$2),make_string($3));}
    | column_atts DEFAULT INT_LITERAL       {$$ = make_nonterminal("column_atts", 3, $1,make_kw("DEFAULT",$2),make_number($3));}
    | column_atts AUTO_INCREMENT    {$$ = make_nonterminal("column_atts", 2, $1,make_kw("AUTO_INCREMENT",$2));}
    ;   

insert_stmt : INSERT INTO IDENTIFIER opt_col_names VALUES BRACKET_OPEN insert_vals_list BRACKET_CLOSE {
    $$ = make_nonterminal("insert_stmt", 8, make_kw("INSERT",$1), make_kw("INTO",$2), make_identifier($3), $4,make_kw("VALUES",$5),make_kw("BRACKET_OPEN",$6),$7,make_kw("BRACKET_CLOSE",$8));
};

insert_vals_list : expr {$$ = make_nonterminal("insert_vals_list",1,$1);}
    | insert_vals_list COMMA expr {$$ = make_nonterminal("insert_vals_list", 3, $1,make_kw("COMMA",$2),$3);}

opt_col_names : {$$ = make_nonterminal("opt_col_names",0);}
    | BRACKET_OPEN column_list BRACKET_CLOSE {$$ = make_nonterminal("opt_col_names",3, make_kw("BRACKET_OPEN",$1),$2,make_kw("BRACKET_CLOSE",$3));}
    ;


update_stmt : UPDATE IDENTIFIER SET update_asign_list opt_where {
    $$ = make_nonterminal("update_stmt", 5, make_kw("UPDATE",$1),make_identifier($2),make_kw("SET",$3),$4,$5);
}
    ;

update_asign_list : IDENTIFIER COMPARATOR expr  {$$ = make_nonterminal("update_asign_list", 3, make_identifier($1),make_kw("COMPARATOR",$2),$3);}
    | update_asign_list COMMA IDENTIFIER COMPARATOR expr    {$$ = make_nonterminal("update_asign_list", 5, $1,make_kw("COMMA",$2), make_identifier($3),make_kw("COMPARATOR",$4),$5);}
    ;

delete_stmt : DELETE FROM IDENTIFIER opt_where  {$$ = make_nonterminal("delete_stmt",4, make_kw("DELETE",$1), make_kw("FROM",$2), make_identifier($3), $4);}
    ;

drop_table_stmt : DROP TABLE IDENTIFIER {$$ = make_nonterminal("drop_table_stmt",3,make_kw("DROP",$1),make_kw("TABLE",$2),make_identifier($3));}
    ;

drop_col_stmt : ALTER TABLE IDENTIFIER DROP COLUMN IDENTIFIER {
    $$ = make_nonterminal("drop_col_stmt",6, make_kw("ALTER",$1), make_kw("TABLE", $2), make_identifier($3), make_kw("DROP", $4), make_kw("COLUMN", $5), make_identifier($6));
}   ;

add_col_stmt : ALTER TABLE IDENTIFIER ADD COLUMN create_definition  {
    $$ = make_nonterminal("add_col_stmt",6, make_kw("ALTER",$1), make_kw("TABLE", $2), make_identifier($3), make_kw("ADD", $4), make_kw("COLUMN", $5), $6);
}   ;

select_stmt: SELECT select_opts select_expr_list FROM IDENTIFIER opt_where {
    $$ = make_nonterminal("select_stmt", 6, make_kw("SELECT",$1),$2,$3,make_kw("FROM",$4),make_identifier($5),$6);
}
    ;

select_opts:        {$$ = make_nonterminal("select_opts",0);}
    | DISTINCT  {$$ = make_nonterminal("select_opts",1,make_kw("DISTINCT",$1));}
    | ALL   {$$ = make_nonterminal("select_opts",1,make_kw("ALL",$1));}
    ;

select_expr_list: expr {$$ = make_nonterminal("select_expr_list", 1, $1);}
    | select_expr_list COMMA expr {$$ = make_nonterminal("select_expr_list", 3, $1, make_kw("COMMA",$2), $3);}
    | ALL_COLUMN    {$$ = make_nonterminal("select_expr_list", 1, make_kw("ALL_COLUMN", $1));}
    ;

opt_where:              {$$ = make_nonterminal("opt_where",0);}
    | WHERE expr        {$$ = make_nonterminal("opt_where", 2, make_kw("WHERE", $1), $2);}
    ;



expr: BRACKET_OPEN expr BRACKET_CLOSE   {$$ = make_nonterminal("expr", 3, make_kw("BRACKET_OPEN", $1), $2, make_kw("BRACKET_CLOSE", $3));}
    | expr COMPARATOR expr      {$$ = make_nonterminal("expr",3, $1,make_kw("COMPARATOR",$2),$3);}
    | expr OR expr      {$$ = make_nonterminal("expr",3, $1,make_kw("OR",$2),$3);}
    | expr AND expr     {$$ = make_nonterminal("expr",3, $1,make_kw("AND",$2),$3);}
    | expr XOR expr     {$$ = make_nonterminal("expr",3, $1,make_kw("XOR",$2),$3);}
    | NOT expr          {$$ = make_nonterminal("expr",2, make_kw("NOT",$1),$2);}
    | expr COMPARATOR BRACKET_OPEN select_stmt BRACKET_CLOSE    {$$ = make_nonterminal("expr",5, $1,make_kw("COMPARATOR",$2),make_kw("BRACKET_OPEN",$3),$4,make_kw("BRACKET_CLOSE",$5));} 
    | expr COMPARATOR ANY BRACKET_OPEN select_stmt BRACKET_CLOSE    {$$ = make_nonterminal("expr",6, $1,make_kw("COMPARATOR",$2),make_kw("ANY",$3),make_kw("BRACKET_OPEN",$4),$5,make_kw("BRACKET_CLOSE",$6));}
    | expr COMPARATOR SOME BRACKET_OPEN select_stmt BRACKET_CLOSE   {$$ = make_nonterminal("expr",6, $1,make_kw("COMPARATOR",$2),make_kw("SOME",$3),make_kw("BRACKET_OPEN",$4),$5,make_kw("BRACKET_CLOSE",$6));}
    | expr COMPARATOR ALL BRACKET_OPEN select_stmt BRACKET_CLOSE    {$$ = make_nonterminal("expr",6, $1,make_kw("COMPARATOR",$2),make_kw("ALL",$3),make_kw("BRACKET_OPEN",$4),$5,make_kw("BRACKET_CLOSE",$6));}
    ;

expr: IDENTIFIER        {$$ = make_nonterminal("expr", 1, make_identifier($1));}
    | STRING_LITERAL        {$$ = make_nonterminal("expr", 1, make_string($1));}
    | INT_LITERAL       {$$ = make_nonterminal("expr", 1, make_number($1));}
    ;
%%

int main(void)
{
    return yyparse();
}

void yyerror(const char *s)
{
    fprintf(stderr, "%s\n", s);
}