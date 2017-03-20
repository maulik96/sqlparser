#include <bits/stdc++.h>

using namespace std;

char **next;

enum treetype {nonterminal_node, keyword_node, number_node, string_node, identifier_node};

typedef struct tree {
    enum treetype nodetype;
    struct tree *children[10];
    int number, size;
    char label[20];
    char keyword[100];
    char string[100];
} tree;

tree *make_nonterminal(char label[], int n, ...);
tree *make_number(int n);
tree *make_string (char v[]);
tree *make_kw (char kw[], char str[]);
tree *make_identifier (char v[]);
void printTree(tree *root, int level);

tree *term(char *tok);

tree *select_stmt();

bool create_definition_factor();

tree *create_col_list();

tree *create_definition();

tree *column_list();

tree *data_type();

tree *opt_length();

tree *create_stmt();

tree *stmt();

tree *start();
tree *insert_stmt();

tree *opt_col_names();

tree *insert_vals_list();



tree *term(char *tok)
{
    if(strcmp(*next++, tok) == 0)
    {
        if(strcmp(tok, "IDENTIFIER")==0)
            return make_identifier(tok);
        else if(strcmp(tok, "STRING_LITERAL") == 0)
            return make_string(tok);
        else if(strcmp(tok, "INT_LITERAL") == 0)
            return make_number(1);
        else
            return make_kw(tok,tok);
    }
    *next--;
    return NULL;
}


tree *select_stmt()
{
    tree *a = term("select");
    if(a)
        return make_nonterminal("select_stmt", 1, a);
    return NULL;
}

bool create_definition_factor()
{
    tree *a = term("COMMA");
    if(a)
        return true;
    return false;
}

tree *create_col_list()
{
    char **save = next;
    tree *a = create_definition(); 
    if(a && !create_definition_factor())
        return make_nonterminal("create_col_list",1,a);
    next = save;
    a = create_definition(); 
    tree *b = term("COMMA");
    tree *c = create_col_list();
    if(a && b && c)
        return make_nonterminal("create_col_list",3,a,b,c);
    return NULL;

}

tree *create_definition()
{
    char **save = next;
    tree *a = term("IDENTIFIER");
    tree *b = data_type();
    if(a && b)
        return make_nonterminal("create_definition",2,a,b);
    next = save;
    a = term("PRIMARY");
    b = term("KEY");
    tree *c = term("BRACKET_OPEN");
    tree *d = column_list();
    tree *e = term("BRACKET_CLOSE");
    if(a && b && c && d && e)
        return make_nonterminal("create_definition",5,a,b,c,d,e);
    next = save;
    return NULL;
}

tree *column_list()
{
    char **save = next;
    tree *a = term("IDENTIFIER");
    if(a)
        return make_nonterminal("column_list",1,a);
    next = save;
    a = term("IDENTIFIER");
    tree *b = term("COMMA");
    tree *c = column_list();
    if(a && b && c)
        return make_nonterminal("column_list",3,a,b,c);
    next = save;
    return NULL;
}

tree *data_type()
{
    char **save = next;
    tree *a = term("BIT");
    tree *b = opt_length();
    if(a && b)
        return make_nonterminal("data_type",2,a,b);
    next = save;
    a = term("INT");
    b = opt_length();
    if(a && b)
        return make_nonterminal("data_type",2,a,b);
    next = save;
    a = term("FLOAT");
    b = opt_length();
    if(a && b)
        return make_nonterminal("data_type",2,a,b);
    next = save;
    a = term("CHAR");
    b = opt_length();
    if(a && b)
        return make_nonterminal("data_type",2,a,b);
    next = save;
    a = term("VARCHAR");
    b = opt_length();
    if(a && b)
        return make_nonterminal("data_type",2,a,b);
    next = save;
    a = term("DOUBLE");
    b = opt_length();
    if(a && b)
        return make_nonterminal("data_type",2,a,b);
    next = save;
    return NULL;
}

tree *opt_length()
{
    char **save = next;
    tree *a = term("BRACKET_OPEN");
    tree *b = term("INT_LITERAL");
    tree *c = term("BRACKET_CLOSE");
    if(a && b && c)
        return make_nonterminal("opt_length", 3,a,b,c);
    next = save;
    return make_nonterminal("opt_length",0);
}

tree *create_stmt()
{
    tree *a = term("CREATE");
    tree *b = term("TABLE");
    tree *c = term("IDENTIFIER");
    tree *d = term("BRACKET_OPEN");
    tree *e = create_col_list();
    tree *f = term("BRACKET_CLOSE");
    if(a && b && c && d && e && f)
        return make_nonterminal("create_stmt", 6, a,b,c,d,e,f);
    return NULL;
} 

tree *insert_stmt()
{
    tree *a = term("INSERT");
    tree *b = term("INTO");
    tree *c = term("IDENTIFIER");
    tree *d = opt_col_names();
    tree *e = term("VALUES");
    tree *f = term("BRACKET_OPEN");
    tree *g = insert_vals_list();
    tree *h = term("BRACKET_CLOSE");
    if(a && b && c && d && e && f && g && h)
        return make_nonterminal("insert_stmt", 8,a,b,c,d,e,f,g,h);
    return NULL;
}

tree *opt_col_names()
{
    char **save = next;
    tree *a = term("BRACKET_OPEN");
    tree *b = column_list();
    tree *c = term("BRACKET_CLOSE");
    if(a && b && c)
        return make_nonterminal("opt_col_names",3,a,b,c);
    next = save;
    return make_nonterminal("opt_col_names",0);
}

tree *insert_vals_list()
{
    char **save = next;
    return NULL;
}

tree *stmt()
{
    char **save = next;
    // tree *a = select_stmt();
    // if(a)
    //     return make_nonterminal("stmt",1,a); 
    // next = save;
    tree *a = create_stmt();
    if(a)
        return make_nonterminal("stmt",1,a); 
    next = save;
    return NULL;
}

tree *start()
{
    tree *a = stmt();
    tree *b = term("SEMICOLON");
    if(a && b)
        return make_nonterminal("start", 2, a,b);
    return NULL;
}

int main(int argc, char const *argv[])
{
    char *arr[] = {"CREATE", "TABLE" ,"IDENTIFIER", "BRACKET_OPEN", "IDENTIFIER", "INT", "COMMA","PRIMARY","KEY","BRACKET_OPEN","IDENTIFIER","BRACKET_CLOSE", "BRACKET_CLOSE","SEMICOLON"};
    next = arr;
    if(start())
    {
        next = arr;
        printTree(start(), 0);
    }
    else
        printf("Syntax error\n");
    return 0;
}


tree *make_nonterminal(char label[], int n, ...)
{
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

tree *make_number(int n)
{
    tree *result= (tree*) malloc (sizeof(tree));
    result->nodetype= number_node;
    result->number= n;
    return result;
}


tree *make_string (char v[])
{
    tree *result= (tree*) malloc (sizeof(tree));
    result->nodetype= string_node;
    strcpy(result->string, v);
    return result;
}

tree *make_kw (char kw[], char str[])
{
    tree *result= (tree*) malloc (sizeof(tree));
    result->nodetype= keyword_node;
    strcpy(result->keyword, kw);
    strcpy(result->string, str);
    return result;
}

tree *make_identifier (char v[])
{
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