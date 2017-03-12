#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <regex.h>

#define SIZE 63

regex_t *makeRegexObj(void);

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


int main()
{
    int i,flag;
    char input[1000];

    fgets(input, 1000, stdin);

    printf("%s\n",input);

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


regex_t *makeRegexObj(void)
{
    regex_t re[SIZE];
    regcomp(&re[0]  , "^create\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[1]  , "^table\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re[2]  , "^insert\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[3]  , "^into\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[4]  , "^select\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[5]  , "^from\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[6]  , "^where\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re[7]  , "^update\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[8]  , "^primary\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re[9]  , "^index\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re[10] , "^foreign\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re[11] , "^key\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[12] , "^default\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re[13] , "^not\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[14] , "^null\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[15] , "^and\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[16] , "^or\\b"                                                      , REG_ICASE | REG_NEWLINE );
    regcomp(&re[17] , "^xor\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[18] , "^all\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[19] , "^some\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[20] , "^any\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[21] , "^bit\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[22] , "^int\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[23] , "^integer\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re[24] , "^bigint\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[25] , "^real\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[26] , "^double\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[27] , "^float\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re[28] , "^decimal\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re[29] , "^char\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[30] , "^varchar\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re[31] , "^references\\b"                                              , REG_ICASE | REG_NEWLINE );
    regcomp(&re[32] , "^order\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re[33] , "^by\\b"                                                      , REG_ICASE | REG_NEWLINE );
    regcomp(&re[34] , "^delete\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[35] , "^values\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[36] , "^auto_increment\\b"                                          , REG_ICASE | REG_NEWLINE );
    regcomp(&re[37] , "^asc\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[38] , "^desc\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[39] , "^unique\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[40] , "^in\\b"                                                      , REG_ICASE | REG_NEWLINE );
    regcomp(&re[41] , "^true\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[42] , "^false\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re[43] , "^distinct\\b"                                                , REG_ICASE | REG_NEWLINE );
    regcomp(&re[44] , "^set\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[45] , "^drop\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[46] , "^alter\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re[47] , "^add\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[48] , "^column\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[49] , "^\\=\\|^!\\=\\|^<>\\|^>\\=\\|^<\\=\\|^>\\|^<"                , REG_ICASE | REG_NEWLINE );
    regcomp(&re[50] , "^int\\|^integer\\|^double\\|^char\\|^varchar\\|^bit\\|^text" , REG_ICASE | REG_NEWLINE );
    regcomp(&re[51] , "^\*"                                                         , REG_ICASE | REG_NEWLINE );
    regcomp(&re[52] , "^\("                                                         , REG_ICASE | REG_NEWLINE );
    regcomp(&re[53] , "^\)"                                                         , REG_ICASE | REG_NEWLINE );
    regcomp(&re[54] , "^,"                                                          , REG_ICASE | REG_NEWLINE );
    regcomp(&re[55] , "^[a-zA-Z][a-zA-Z0-9_]*\\b"                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re[56] , "^`[a-zA-Z][a-zA-Z0-9_]*`\\b"                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re[57] , "^[+-]?[0-9][0-9]*"                                           , REG_ICASE | REG_NEWLINE ); // may be wrong
    regcomp(&re[58] , "^\"[^\"]*\""                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re[59] , "^\'[^\"]*\'"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re[60] , "^[ \t\r\n][ \t\r\n]+"                                        , REG_ICASE | REG_NEWLINE );
    regcomp(&re[61] , "^;"                                                          , REG_ICASE | REG_NEWLINE );
    regcomp(&re[62] , "^."                                                          , REG_ICASE | REG_NEWLINE ); // may be wrong
    return re;
}
