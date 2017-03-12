%{
    #include "y.tab.h"
%}

%option caseless

%%

create                                     { yylval.strval = strdup(yytext); return CREATE; }
table                                      { yylval.strval = strdup(yytext); return TABLE; }
insert                                     { yylval.strval = strdup(yytext); return INSERT; }
into                                       { yylval.strval = strdup(yytext); return INTO; }
select                                     { yylval.strval = strdup(yytext); return SELECT; }
from                                       { yylval.strval = strdup(yytext); return FROM; }
where                                      { yylval.strval = strdup(yytext); return WHERE; }
update                                      { yylval.strval = strdup(yytext); return UPDATE; }
primary                                    { yylval.strval = strdup(yytext); return PRIMARY; }
index                                    { yylval.strval = strdup(yytext); return INDEX; }
foreign                                    { yylval.strval = strdup(yytext); return FOREIGN; }
key                                        { yylval.strval = strdup(yytext); return KEY; }
default                                    { yylval.strval = strdup(yytext); return DEFAULT; }
not                                        { yylval.strval = strdup(yytext); return NOT; }
null                                       { yylval.strval = strdup(yytext); return NULL_TOKEN; }
and                                        { yylval.strval = strdup(yytext); return AND; }
or                                         { yylval.strval = strdup(yytext); return OR; }
xor											{ yylval.strval = strdup(yytext); return XOR;}
all											{ yylval.strval = strdup(yytext); return ALL;}
some											{ yylval.strval = strdup(yytext); return SOME;}
any											{ yylval.strval = strdup(yytext); return ANY;}
bit										   { yylval.strval = strdup(yytext); return BIT;}
int										   { yylval.strval = strdup(yytext); return INT;}
integer									   { yylval.strval = strdup(yytext); return INTEGER;}
bigint									   { yylval.strval = strdup(yytext); return BIGINT;}
real									   { yylval.strval = strdup(yytext); return REAL;}
double									   { yylval.strval = strdup(yytext); return DOUBLE;}
float									   { yylval.strval = strdup(yytext); return FLOAT;}
decimal									   { yylval.strval = strdup(yytext); return DECIMAL;}
char									   { yylval.strval = strdup(yytext); return CHAR;}
varchar									   { yylval.strval = strdup(yytext); return VARCHAR;}
=|!=|<>|>=|<=|>|<                          { yylval.strval = strdup(yytext); return COMPARATOR; }
references                                 { yylval.strval = strdup(yytext); return REFERENCES; }
order                                      { yylval.strval = strdup(yytext); return ORDER; }
by                                         { yylval.strval = strdup(yytext); return BY; }
delete                                     { yylval.strval = strdup(yytext); return DELETE; }
(int|integer|double|char|varchar|bit|text) { yylval.strval = strdup(yytext); return DATATYPE; }
values                                     { yylval.strval = strdup(yytext); return VALUES; }
auto_increment                             { yylval.strval = strdup(yytext); return AUTO_INCREMENT; }
asc                                        { yylval.strval = strdup(yytext); return ASC; }
desc                                       { yylval.strval = strdup(yytext); return DESC; }
unique                                     { yylval.strval = strdup(yytext); return UNIQUE; }
in                                         { yylval.strval = strdup(yytext); return IN; }
true                                       { yylval.strval = strdup(yytext); return TRUE; }
false                                      { yylval.strval = strdup(yytext); return FALSE; }
distinct                                   { yylval.strval = strdup(yytext); return DISTINCT; }
set                                        { yylval.strval = strdup(yytext); return SET; }
drop                                       { yylval.strval = strdup(yytext); return DROP; }
alter                                      { yylval.strval = strdup(yytext); return ALTER; }
add                                        { yylval.strval = strdup(yytext); return ADD; }
column                                     { yylval.strval = strdup(yytext); return COLUMN; }
\*                                         { yylval.strval = strdup(yytext); return ALL_COLUMN; }
\(                                         { yylval.strval = strdup(yytext); return BRACKET_OPEN; }
\)                                         { yylval.strval = strdup(yytext); return BRACKET_CLOSE; }
,                                          { yylval.strval = strdup(yytext); return COMMA;; }
[a-zA-Z][a-zA-Z0-9_]*                      { yylval.strval = strdup(yytext); return IDENTIFIER; }
`[a-zA-Z][a-zA-Z0-9_]*`                    { yylval.strval = strdup(yytext); return IDENTIFIER; }
[+-]?[0-9]+                                { yylval.intval = atoi(yytext); return INT_LITERAL; }
\"[^\"]*\"                                 { yylval.strval = strdup(yytext); return STRING_LITERAL; }
\'[^\"]*\'                                 { yylval.strval = strdup(yytext); return STRING_LITERAL; }
[ \t\r\n]+                                 { }
;                                          { yylval.strval = strdup(yytext); return SEMICOLON; }
.                                          { yylval.strval = strdup(yytext); return INVALID; }

%%


int yywrap(void)
{
    return 1;
}
