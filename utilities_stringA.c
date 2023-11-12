
#include  "shell.h"
 

/**
 * _strchr - searches for a specified character in a string
 * @str: string to search in 
 * @c: character to search for
 * Return: return int position found or 0
*/
 int _strchr(const char *str, int c)
 {
    unsigned int len = 1;
    while(*str != null && *str != c)
    {
        str++;
        len++;
    }  
    /* return position of character or NULL */
    return ((*str == c) ? len : _FALSE);
 }



/**
 * _strchr_ptr - searches for a specified character in a string
 * @str: string to search in 
 * @c: character to search for
 * Return: return pointer at position 
*/
 char * _strchr_ptr(char *str, int c)
 {
    unsigned int len = 1;
    while(*str != null && *str != c)
    {
        str++;
        len++;
    }  
    /* return position of character or NULL */
    return ((*str == c) ? str  : NULL);
 }


/**
 * _strtok - divide strings into words 
 * @str: string to convert
 * @delimiters:  word seperators array
 * Return: pointer to found position or null
*/
 char* _strtok(char *str, char *delimiters)
 {
    static char *start_token = NULL;
    char *end_token  = NULL;
    char *ret = NULL;
     int len, iter;

    if (str != NULL || str)
        start_token = str;
    else if (start_token == NULL)
        return NULL;   

    /* jump string to the not delimeter character */
    while (*start_token != null && _strchr(delimiters, *start_token))
        start_token++;
    /*if the string has ended return null */
    if(*start_token == null )
    {
        start_token = NULL;
        return start_token;
    }

    end_token = start_token;
   
    
    /* add 1 to accept the null terminator (len + 1) */

    len = _strchr(delimiters, *start_token);
     ret = malloc(sizeof(char) * (len + 1));
     if(!ret)
        return(NULL);

     iter = 0;
    /* search for the  end of token  or jumps to next delimter in string */
    while (*end_token != null && _strchr(delimiters, *end_token) == _FALSE)
    {
        ret[iter] = *end_token;
        end_token++;
        iter++;
    }
    ret[iter]= null;
    /* insert a null terminator at the end of the token */

    switch ((*end_token))
    {
    case null:
       start_token = NULL;
        break;
    
    default:
        *end_token  = null;
        start_token = (end_token + 1);
        break;
    }
    if(!ret)
        free(ret);

    return (ret);
    }
 






/**
 * _strdupl - creates a dublicate string 
 * @str: string to dublicate
 * Return: pointer to the new dublicate string
*/

char *_strdupl(char *str)
{
    char *str_dupl;
    int iter, length;
    if (str == NULL)
        return (NULL);
    
    length =  str_len(str) + 1;

    str_dupl = malloc(sizeof(char) * length);

    /* check for memomery allocation */
    if(str_dupl == NULL)
    {
        errno = ENOMEM;
        perror("Error");
        return (NULL);
    }

    iter = 0;
    while (*str != null)
    {
        str_dupl[iter] = (*str);
        iter++;
        str++;
    }
    /* Free heap memomry str_dupl after use */
    return (str_dupl);
}


/**
 * _reverse_str - reverse a string 
 * @str: string to reverse
*/

void _reverse_str(char *str)
{
    int frm_start, frm_end;
    char temp_char;

    if(str != NULL)
    {

        frm_start = 0;

        /* jump null char at end with -1 */
        frm_end =  str_len(str) - 1 ;

        while(frm_start < frm_end )
        {
            /* swap characters */
            temp_char = str[frm_start];
            str[frm_start] = str[frm_end];
            str[frm_end] = temp_char;
            frm_start++;
            frm_end--;
        }
    }

}


