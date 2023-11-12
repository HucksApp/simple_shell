
#include "shell.h"





ssize_t _get_node_index(string_list_type *head, string_list_type *node)
{
    size_t index ;
    string_list_type * current_node;

    current_node = head;
    for(index=0; current_node != NULL; index++, current_node = current_node->next)
        if(current_node == node)
            return (index);
    return (SYS_ERROR);
        
}


size_t _node_length(string_list_type *head)
{
    size_t length;
    string_list_type * current_node;

    current_node = head;
    for(length = 0; current_node; length++, current_node = current_node->next)
        ;
    return(length);
}





char ** _node_to_stringlist(string_list_type *head)
{
    string_list_type * current_node;
    char ** str_list ;
    char * str;
    size_t  str_list_len, iter;


    if (!head)
		return (NULL);

    current_node = head;
    str_list_len = _node_length(current_node);

   if(!str_list_len)
        return (NULL);
    
    str_list = malloc(sizeof(char) * (str_list_len + 1));

    if(!str_list)
        return (NULL);

    for (iter = 0; current_node; iter++, current_node = current_node->next)
    {
        str = malloc(sizeof(char) * str_len(current_node->_string));
        if(str == NULL)
        {
            _free_string_list(str_list);
            return (NULL);
        }
       str =  _strcpy(str, current_node->_string);
       str_list[iter] = str;
    }

    /*terminate the string list*/
    str[iter] = null;
    return (str_list);
}





string_list_type *_match_node_str(string_list_type *node,
                                             char *key, char c)
{
    char *str = NULL;

    while (node != NULL)
    {
        str =_match_str_path(node->_string, key);
        if(str && ((c == -1) || (*str == c)))
            return (node);
        node = node->next;
    }
    return (NULL);
}


