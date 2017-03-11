%{
    #include "y.tab.h"
%}

%option caseless

%%

create                                     { return CREATE; }
table                                      { return TABLE; }
insert                                     { return INSERT; }
into                                       { return INTO; }
select                                     { return SELECT; }
from                                       { return FROM; }
where                                      { return WHERE; }
update                                      { return UPDATE; }
primary                                    { return PRIMARY; }
index                                    { return INDEX; }
foreign                                    { return FOREIGN; }
key                                        { return KEY; }
default                                    { return DEFAULT; }
not                                        { return NOT; }
null                                       { return NULL_TOKEN; }
and                                        { return AND; }
or                                         { return OR; }
xor											{ return XOR;}
all											{ return ALL;}
some											{ return SOME;}
any											{ return ANY;}
bit										   { return BIT;}
int										   { return INT;}
integer									   { return INTEGER;}
bigint									   { return BIGINT;}
real									   { return REAL;}
double									   { return DOUBLE;}
float									   { return FLOAT;}
decimal									   { return DECIMAL;}
=|!=|<>|>=|<=|>|<                          { return COMPARATOR; }
references                                 { return REFERENCES; }
order                                      { return ORDER; }
by                                         { return BY; }
delete                                     { return DELETE; }
(int|integer|double|char|varchar|bit|text) { return DATATYPE; }
values                                     { return VALUES; }
auto_increment                             { return AUTO_INCREMENT; }
asc                                        { return ASC; }
desc                                       { return DESC; }
unique                                     { return UNIQUE; }
in                                         { return IN; }
true                                       { return TRUE; }
false                                      { return FALSE; }
distinct                                   { return DISTINCT; }
set                                        { return SET; }
drop                                       { return DROP; }
alter                                      { return ALTER; }
add                                        { return ADD; }
column                                     { return COLUMN; }
\*                                         { return ALL_COLUMN; }
\(                                         { return BRACKET_OPEN; }
\)                                         { return BRACKET_CLOSE; }
,                                          { return COMMA;; }
[a-zA-Z][a-zA-Z0-9_]*                      { yylval.strval = strdup(yytext); return IDENTIFIER; }
`[a-zA-Z][a-zA-Z0-9_]*`                    { yylval.strval = strdup(yytext); return IDENTIFIER; }
[+-]?[0-9]+                                { yylval.intval = atoi(yytext); return INT_LITERAL; }
\"[^\"]*\"                                 { yylval.strval = strdup(yytext); return STRING_LITERAL; }
\'[^\"]*\'                                 { yylval.strval = strdup(yytext); return STRING_LITERAL; }
[ \t\r\n]+                                 { }
;                                          { return SEMICOLON; }
.                                          { return INVALID; }

%%


int yywrap(void)
{
    return 1;
}
