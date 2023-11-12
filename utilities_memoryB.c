#include "shell.h"


/**
 * _set_memory - set memory 
 * is alocated dynamically
 * @ptr: pointer to memory location
 * @c: byte value to set
 * @size: number of byte to set
 * Return: pointer to memory location
*/


void *_set_memory(char *ptr, char c, unsigned int size)
{
    unsigned int iter;
    for(iter = 0; iter < size; iter++)

    /* cast to unsigned chat to ensure 'its in bytes' */
        ptr[iter] =  (unsigned char)c;
    return (ptr);
}




int _free_str_in_str(void **str)
{
    if (*str && str) 
    {
        _free(*str);
        *str = NULL;
        return(_TRUE);
    }
    return(_FALSE);
}




