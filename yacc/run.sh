yacc -d -Wnone sql.y
lex sql.l 
gcc y.tab.c lex.yy.c
./a.out < ../input/1.txt
