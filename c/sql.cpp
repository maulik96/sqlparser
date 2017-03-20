#include <bits/stdc++.h>
#include <regex.h>
using namespace std;

#define SIZE 64
char *names[]={"CREATE","TABLE","INSERT","INTO","SELECT","FROM","WHERE","UPDATE","PRIMARY","INDEX","FOREIGN","KEY","DEFAULT","NOT","NULL_TOKEN","AND","OR","XOR","ALL","SOME","ANY","BIT","INT","INTEGER","BIGINT","REAL","DOUBLE","FLOAT","DECIMAL","CHAR","VARCHAR","REFERENCES","ORDER","BY","DELETE","VALUES","AUTO_INCREMENT","ASC","DESC","UNIQUE","IN","TRUE","FALSE","DISTINCT","SET","DROP","ALTER","ADD","COLUMN","COMPARATOR","DATATYPE","ALL_COLUMN","BRACKET_OPEN","BRACKET_CLOSE","COMMA","IDENTIFIER","IDENTIFIER","INT_LITERAL","INT_LITERAL","INT_LITERAL","STRING_LITERAL","STRING_LITERAL","SPACE","SEMICOLON"};

regex_t re_obj[SIZE];

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
void makeRegexObj(void);
void print(std::vector<string> v);


int main()
{
    int i,flag;
    char input[1000];
    std::vector<string> input_tokens,name_tokens;

    makeRegexObj();
    fgets(input, 1000, stdin);

    char *match_string = input;
    regmatch_t matchptr[10];

    printf("--------------------------------------------------\n");
    printf("Input code:\n");
    printf("%s\n",match_string);
    printf("--------------------------------------------------\n");
    printf("Output:\n");

    char *temp_token=(char*)malloc(100);
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
                    input_tokens.push_back(s1);
                    name_tokens.push_back(s2);
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
        print(input_tokens);
        print(name_tokens);
    }

    return 0;
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
