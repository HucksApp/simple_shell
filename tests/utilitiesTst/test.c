#include <stdio.h>
#include <unistd.h>
#include "../../shell.h"





int main() {

    char strc[] = "This,is;a,sample,string";
    const char delimitersc[] = ",;";


    char s[] = "i love you,";
    char d[] = "my darling";
/*
    char strf[] = "This,is;a,sample,string";
    const char delimitersf[] = ",;";






    char *tokenc = _strtok(strc, delimitersc);
    char *tokenf = strtok(strf, delimitersf);

    for (int i = 0; i <= 17; i++)
    {
        printf("Tokenc: %s\n", tokenc);
        tokenc = _strtok(NULL, delimitersc);   

        printf("Tokef: %s\n", tokenf);
        tokenf = strtok(NULL, delimitersf); 
    }
*/

     //_reverse_str(strc);
     printf("Tokenc: %i\n",_strcmpr(d,s,1));


    return 0;
}
