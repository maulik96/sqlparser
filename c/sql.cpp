#include <bits/stdc++.h>
#include <regex.h>
using namespace std;

#define SIZE 64
char *names[]={"CREATE","TABLE","INSERT","INTO","SELECT","FROM","WHERE","UPDATE","PRIMARY","INDEX","FOREIGN","KEY","DEFAULT","NOT","NULL_TOKEN","AND","OR","XOR","ALL","SOME","ANY","BIT","INT","INTEGER","BIGINT","REAL","DOUBLE","FLOAT","DECIMAL","CHAR","VARCHAR","REFERENCES","ORDER","BY","DELETE","VALUES","AUTO_INCREMENT","ASC","DESC","UNIQUE","IN","TRUE","FALSE","DISTINCT","SET","DROP","ALTER","ADD","COLUMN","COMPARATOR","DATATYPE","ALL_COLUMN","BRACKET_OPEN","BRACKET_CLOSE","COMMA","IDENTIFIER","IDENTIFIER","INT_LITERAL","INT_LITERAL","INT_LITERAL","STRING_LITERAL","STRING_LITERAL","SPACE","SEMICOLON"};

char **next;
regex_t re_obj[SIZE];

enum treetype {nonterminal_node, keyword_node, number_node, string_node, identifier_node};

typedef struct tree {
    enum treetype nodetype;
    struct tree *children[10];
    int number, size;
    char label[20];
    char keyword[100];
    char text[100];
} tree;

tree *make_nonterminal(char label[], int n, ...);
tree *make_number(int n);
tree *make_string(char v[]);
tree *make_kw(char kw[], char str[]);
tree *make_identifier(char v[]);

tree *term(char *tok);
tree *select_stmt();
tree *create_col_list();
tree *create_definition();
tree *column_list();
tree *data_type();
tree *opt_length();
tree *create_stmt();
tree *insert_stmt();
tree *opt_col_names();
tree *insert_vals_list();
tree *stmt();
tree *start();
tree *update_asign_list():
bool create_definition_factor();

void printTree(tree *root, int level);

void makeRegexObj(void);
char **str_to_char_arr(vector<string> v);
void print(std::vector<string> v);
void print(char **v, int size);

// --------------------------------------------------

int main()
{
    int i,flag;
    char input[1000];
    std::vector<string> input_tokens_temp,name_tokens_temp;
    char *temp_token=(char*)malloc(100);

    makeRegexObj();
    fgets(input, 1000, stdin);

    char *match_string = input;
    regmatch_t matchptr[10];

    printf("--------------------------------------------------\n");
    printf("Input code:\n");
    printf("%s\n",match_string);
    printf("--------------------------------------------------\n");
    printf("Output:\n");

    while(match_string[0]!='\0')
    {
        flag = 0;
        for(i=0;i<SIZE;i++)
        {
            if(regexec(&re_obj[i], match_string, 10, matchptr, 0) == 0)
            {
                if(strcmp(names[i],"SPACE")!=0)
                {
                    free(temp_token);
                    temp_token=(char*)malloc(100);
                    strncpy(temp_token,match_string,matchptr[0].rm_eo);
                    std::string s1(temp_token), s2(names[i]);
                    input_tokens_temp.push_back(s1);
                    name_tokens_temp.push_back(s2);
                    match_string += matchptr[0].rm_eo;
                }
                else
                    match_string += matchptr[0].rm_eo;
                flag = 1;
            }
        }
        if(flag==0)
        {
            printf("\nUnexpected expression\n");
            printf("%s\n",match_string);
            printf("--------------------------------------------------\n");
            break;
        }
    }
    if(flag)
    {
        char **input_tokens = str_to_char_arr(input_tokens_temp);
        char **name_tokens = str_to_char_arr(name_tokens_temp);
        // print(input_tokens,input_tokens_temp.size());
        // print(name_tokens,name_tokens_temp.size());
        next = name_tokens;
        print(next,input_tokens_temp.size());
        printTree(start(),0);
    }

    return 0;
}

// --------------------------------------------------

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

tree *make_string(char v[])
{
    tree *result= (tree*) malloc (sizeof(tree));
    result->nodetype= string_node;
    strcpy(result->text, v);
    return result;
}

tree *make_kw(char kw[], char str[])
{
    tree *result= (tree*) malloc (sizeof(tree));
    result->nodetype= keyword_node;
    strcpy(result->keyword, kw);
    strcpy(result->text, str);
    return result;
}

tree *make_identifier(char v[])
{
    tree *result= (tree*) malloc (sizeof(tree));
    result->nodetype= identifier_node;
    strcpy(result->text, v);
    return result;
}

// --------------------------------------------------

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



bool factor()
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
    if(a && !factor())
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
    if(a && !factor())
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

tree *expr()
{
    char **save=next;
    tree *a=term("IDENTIFIER");
    if(a)
        return make_nonterminal("IDENTIFIER",1);

    next=save;
    a=term("STRING_LITERAL");
        
    if(a)
        return make_nonterminal("STRING_LITERAL",1);
    next=save;

    a=term("INT_LITERAL");
    if(a)
        return make_nonterminal("INT_LITERAL",1);

    next=save;
    a = term("BRACKET_OPEN");
    tree *b = term("IDENTIFIER"); 
    tree *c = term("BRACKET_CLOSE"); 
    if(a&&b&&c)
        return make_nonterminal("expr",3,a,b,c);
    next=save;
    return NULL;

}

tree *select_expr_list()
{
    char **save = next;
    tree *a = expr();
    if(a && !factor())
    {
        return make_nonterminal("select_expr_list",1,a);
    }
    next = save;
    tree *b = expr();
    tree *c = term("COMMA");
    tree *d = select_expr_list();
    if(b && c && d)
    {
        return make_nonterminal("select_expr_list",3,b,c,d);
    }
    next = save;
    tree *e = term("ALL_COLUMN");
    if(e)
        return make_nonterminal("select_expr_list",1,e);
    next = save;
    return NULL;
}


tree *select_stmt()
{
    tree *a = term("SELECT");
    tree *b = select_expr_list();
    tree *c = term("FROM");
    tree *d = term("IDENTIFIER");
    tree *e = opt_where;
    if(a && b && c && d && e)
        return make_nonterminal("select_stmt", 5, a, b, c, d, e);
    return NULL;
}

tree *opt_where()
{
    char **save = next;
    tree *a = term("WHERE");
    tree *b = expr1();
    if(a&&b)
        return make_nonterminal("opt_where",2,a,b);
    next = save;
    return make_nonterminal("opt_where",0);
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
    tree *a = expr();
    if(a && !factor())
        return make_identifier("insert_vals_list",1,a);
    next = save;
    a = expr();
    tree *b = term("COMMA");
    tree *c = insert_vals_list();
    if(a && b && c)
        return make_identifier("insert_vals_list",3,a,b,c);
    next = save;
    return NULL;
}

tree *update_stmt()
{
    tree *a = term("UPDATE");    
    tree *b = term("IDENTIFIER");    
    tree *c = term("SET");    
    tree *d = update_assign_list();    
    tree *e = opt_where();
    if(a && b && c && d && e)
        return make_nonterminal("update_stmt",5,a,b,c,d,e);
    return NULL;    
}

tree *expr2()
{
    tree *a = expr();
    tree *b = term("COMPARATOR");
    tree *c = expr();
    if(a && b && c)
        return make_nonterminal("expr", 3, a, b, c);
}

tree *expr1()
{
    char **save = next;
    tree *a = expr();
    tree *b = term("COMPARATOR");
    tree *c = expr();
    if(a && b && c)
        return make_nonterminal("expr", 3,a,b,c);
    next = save;
    a = expr2();
    b = term("OR");
    c = expr1();
    if(a && b && c)
        return make_nonterminal("expr", 3,a,b,c);
    next = save;
    a = expr2();
    b = term("AND");
    c = expr1();
    if(a && b && c)
        return make_nonterminal("expr", 3,a,b,c);
    next = save;
    b = term("NOT");
    c = expr1();
    if(a && b && c)
        return make_nonterminal("expr", 2,b,c);
    next = save;
    a = expr();
    b = term("AND");
    c = expr();
    if(a && b && c)
        return make_nonterminal("expr", 3,a,b,c);
    next = save;
    a = expr();
    b = term("COMPARATOR");
    c = term("BRACKET_OPEN");
    d = select_stmt();
    e = term("BRACKET_CLOSE");
    if(a && b && c && d && e)
        return make_nonterminal("expr", 5,a,b,c,d,e);
    next = save;
    a = expr();
    b = term("COMPARATOR");
    c = term("ANY");
    d = term("BRACKET_OPEN");
    e = select_stmt();
    f = term("BRACKET_CLOSE");
    if(a && b && c && d && e && f)
        return make_nonterminal("expr", 6,a,b,c,d,e,f);
    next = save;
    a = expr();
    b = term("COMPARATOR");
    c = term("SOME");
    d = term("BRACKET_OPEN");
    e = select_stmt();
    f = term("BRACKET_CLOSE");
    if(a && b && c && d && e && f)
        return make_nonterminal("expr", 6,a,b,c,d,e,f);
    next = save;
    a = expr();
    b = term("COMPARATOR");
    c = term("ALL");
    d = term("BRACKET_OPEN");
    e = select_stmt();
    f = term("BRACKET_CLOSE");
    if(a && b && c && d && e && f)
        return make_nonterminal("expr", 6,a,b,c,d,e,f);
    next = save;
    return NULL;
}

tree *delete_stmt()
{
    tree *a=term("DELETE");
    tree *b=term("FROM");
    tree *c=term("IDENTIFIER");
    tree *d=opt_where();

    if(a && b&& c &&d)
        return make_nonterminal("delete_stmt",4,a,b,c,d);

    return NULL;
}

tree *drop_table_stmt()
{
    tree *a=term("DROP");
    tree *b=term("TABLE");
    tree *c=term("IDENTIFIER");

    if(a&&b&&c)
        return make_nonterminal("drop_table_stmt",3,a,b,c);

    return NULL;
}

tree *drop_col_stmt()
{
    tree *a=term("ALTER");
    tree *b=term("TABLE");
    tree *c=term("IDENTIFIER");
    tree *d=term("DROP");
    tree *e=term("COLUMN");
    tree *f=term("IDENTIFIER");

    if(a && b && c && d && e && f)
        return make_nonterminal("drop_col_stmt",6,a,b,c,d,e,f);

    return NULL;
}

tree *add_col_stmt()
{
    tree *a=term("ALTER");
    tree *b=term("TABLE");
    tree *c=term("IDENTIFIER");
    tree *d=term("ADD");
    tree *e=term("COLUMN");
    tree *f=create_definition();

    if(a && b && c && d && e && f)
        return make_nonterminal("add_col_stmt",6,a,b,c,d,e,f);

    return NULL;
}

tree *update_asign_list()
{
    char **save=next;
    tree *a=term("IDENTIFIER");
    tree *b=term("COMPARATOR");
    term *c=expr();

    if(a && b && c)
    {
        if(factor())
        {
            next=save;
            a=term("IDENTIFIER");
            b=term("COMPARATOR");
            c=expr();
            tree *d=term("COMMA");
            term *e=update_asign_list();
            return make_nonterminal("update_asign_list",5,a,b,c,d,e);
        }

        return make_nonterminal("update_asign_list",3,a,b,c);
    }

    return NULL;
}

tree *stmt()
{
    char **save = next;
    tree *a = create_stmt();
    if(a)
        return make_nonterminal("stmt",1,a); 
    next = save;
    a = insert_stmt();
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

// --------------------------------------------------

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
        printf("%*s%s -- %s\n", level, "", root->keyword, root->text);
    else if(root->nodetype == string_node)
        printf("%*sSTRING_LITERAL -- %s\n", level, "", root->text);
    else
        printf("%*sIDENTIFIER -- %s\n",level, "", root->text);
}

// --------------------------------------------------

void makeRegexObj(void)
{
    regcomp(&re_obj[0]  , "^create\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[1]  , "^table\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[2]  , "^insert\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[3]  , "^into\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[4]  , "^select\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[5]  , "^from\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[6]  , "^where\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[7]  , "^update\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[8]  , "^primary\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[9]  , "^index\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[10] , "^foreign\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[11] , "^key\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[12] , "^default\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[13] , "^not\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[14] , "^null\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[15] , "^and\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[16] , "^or\\b"                                                      , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[17] , "^xor\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[18] , "^all\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[19] , "^some\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[20] , "^any\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[21] , "^bit\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[22] , "^int\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[23] , "^integer\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[24] , "^bigint\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[25] , "^real\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[26] , "^double\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[27] , "^float\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[28] , "^decimal\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[29] , "^char\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[30] , "^varchar\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[31] , "^references\\b"                                              , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[32] , "^order\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[33] , "^by\\b"                                                      , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[34] , "^delete\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[35] , "^values\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[36] , "^auto_increment\\b"                                          , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[37] , "^asc\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[38] , "^desc\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[39] , "^unique\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[40] , "^in\\b"                                                      , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[41] , "^true\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[42] , "^false\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[43] , "^distinct\\b"                                                , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[44] , "^set\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[45] , "^drop\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[46] , "^alter\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[47] , "^add\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[48] , "^column\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[49] , "^\\=\\|^!\\=\\|^<>\\|^>\\=\\|^<\\=\\|^>\\|^<"                , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[50] , "^int\\|^integer\\|^double\\|^char\\|^varchar\\|^bit\\|^text" , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[51] , "^\*"                                                         , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[52] , "^\("                                                         , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[53] , "^\)"                                                         , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[54] , "^,"                                                          , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[55] , "^[a-zA-Z][a-zA-Z0-9_]*\\b"                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[56] , "^`[a-zA-Z][a-zA-Z0-9_]*`\\b"                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[57] , "^[0-9][0-9]*"                                                , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[58] , "^+[0-9][0-9]*"                                               , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[59] , "^-[0-9][0-9]*"                                               , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[60] , "^\"[^\"]*\""                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[61] , "^\'[^\"]*\'"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[62] , "^[ ][ ]*"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re_obj[63] , "^;"                                                          , REG_ICASE | REG_NEWLINE );
}


void print(std::vector<string> v)
{
    int i;
    cout<<"[";
    if(v.size()>0)
    {
        cout<<" "<<v[0];
        for(i=1;i<v.size();i++)
            cout<<", "<<v[i];
    }
    cout<<" ]"<<endl;
}

void print(char **v, int size)
{
    int i;
    cout<<"[";
    cout<<" "<<v[0];
    for(i=1;i<size;i++)
        cout<<", "<<v[i];
    cout<<" ]"<<endl;
}


char **str_to_char_arr(vector<string> v)
{
    char** cstrings = new char*[v.size()];

    for(size_t i = 0; i < v.size(); ++i)
    {
        cstrings[i] = new char[v[i].size() + 1];
        std::strcpy(cstrings[i], v[i].c_str());
    }

    return cstrings;
}
