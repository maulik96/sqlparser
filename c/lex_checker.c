#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define SIZE 43

char *names[]={"CREATE","TABLE","INSERT","INTO","SELECT","FROM","WHERE","PRIMARY","FOREIGN","KEY","DEFAULT","NOT","TOKEN_NULL","AND","OR","COMPARATOR","REFERENCES","ORDER","BY","DELETE","DATATYPE","VALUES","AUTO_INCREMENT","ASC","DESC","UNIQUE","IN","TRUE","FALSE","DISTINCT","SET","DROP","ALTER","ADD","COLUMN","ALL_COLUMN","BRACKET_OPEN","BRACKET_CLOSE","IDENTIFIER","INT_LITERAL","STRING_LITERAL","","SEMICOLON\n"};

int main(int argc, char const *argv[])
{
    int i,flag;
    char input[1000];
    regex_t re[SIZE];


    regcomp(&re[0]  , "^create\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[1]  , "^table\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re[2]  , "^insert\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[3]  , "^into\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[4]  , "^select\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[5]  , "^from\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[6]  , "^where\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re[7]  , "^primary\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re[8]  , "^foreign\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re[9]  , "^key\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[10] , "^default\\b"                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re[11] , "^not\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[12] , "^null\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[13] , "^and\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[14] , "^or\\b"                                                      , REG_ICASE | REG_NEWLINE );
    regcomp(&re[15] , "^<\\|^>\\|^\\=\\|^<\\=\\|^>\\=\\|^<>\\|^!\\="                , REG_ICASE | REG_NEWLINE );
    regcomp(&re[16] , "^references\\b"                                              , REG_ICASE | REG_NEWLINE );
    regcomp(&re[17] , "^order\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re[18] , "^by\\b"                                                      , REG_ICASE | REG_NEWLINE );
    regcomp(&re[19] , "^delete\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[20] , "^int\\|^integer\\|^double\\|^char\\|^varchar\\|^bit\\|^text" , REG_ICASE | REG_NEWLINE );
    regcomp(&re[21] , "^values\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[22] , "^auto_increment\\b"                                          , REG_ICASE | REG_NEWLINE );
    regcomp(&re[23] , "^asc\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[24] , "^desc\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[25] , "^unique\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[26] , "^in\\b"                                                      , REG_ICASE | REG_NEWLINE );
    regcomp(&re[27] , "^true\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[28] , "^false\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re[29] , "^distinct\\b"                                                , REG_ICASE | REG_NEWLINE );
    regcomp(&re[30] , "^set\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[31] , "^drop\\b"                                                    , REG_ICASE | REG_NEWLINE );
    regcomp(&re[32] , "^alter\\b"                                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re[33] , "^add\\b"                                                     , REG_ICASE | REG_NEWLINE );
    regcomp(&re[34] , "^column\\b"                                                  , REG_ICASE | REG_NEWLINE );
    regcomp(&re[35] , "^\*"                                                         , REG_ICASE | REG_NEWLINE );
    regcomp(&re[36] , "^\("                                                         , REG_ICASE | REG_NEWLINE );
    regcomp(&re[37] , "^\)"                                                         , REG_ICASE | REG_NEWLINE );
    regcomp(&re[38] , "^[a-zA-Z][a-zA-Z0-9_]*\\b"                                   , REG_ICASE | REG_NEWLINE );
    regcomp(&re[39] , "^[0-9][0-9]*"                                                , REG_ICASE | REG_NEWLINE );
    regcomp(&re[40] , "^\"[^\"]*\""                                                 , REG_ICASE | REG_NEWLINE );
    regcomp(&re[41] , "^[ \t\r\n][ \t\r\n]*"                                        , REG_ICASE | REG_NEWLINE );
    regcomp(&re[42] , "^;"                                                          , REG_ICASE | REG_NEWLINE );

    while(fgets(input, 1000, stdin))
    {       
        char pattern[1000];
        strcpy(pattern, input);

        char *match_string = pattern;
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
                if(regexec(&re[i], match_string, 10, matchptr, 0) == 0)
                {
                    match_string += matchptr[0].rm_eo;
                    printf("%s ", names[i]);
                    flag = 1;
                }
            }
            if(flag==0)
            {
                printf("\n");
                printf("\nUnexpected expression\n");
                printf("%s\n",match_string);
                printf("--------------------------------------------------\n\n\n");
                break;
            }
        }
        printf("\n");
    }
    return 0;
}