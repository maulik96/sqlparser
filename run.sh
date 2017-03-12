yacc -d -Wnone sql.y
lex sql.l 
gcc y.tab.c lex.yy.c
./a.out < in.txt
