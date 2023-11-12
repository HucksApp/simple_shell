
#include "shell.h"

/**
 * if the head(origin) which is a pointer  is needed 
 * we pass in a pointer to the pointer head
*/



string_list_type *_create_node(void)
{
    string_list_type *new_node;

    new_node = malloc(sizeof(string_list_type));

    if(!new_node)
    {
        /* if memory is not assigned */
        free(new_node);
        return (NULL);
    }
        /* init all memory bytes to null */
    _set_memory((void *) new_node,0, sizeof(string_list_type));
    return (new_node);
    
}




string_list_type * _prepend_node(string_list_type **head, char *str , int num)
{  
    string_list_type *new_head;

    if(!head)
        return (NULL);
    new_head = _create_node();
    if(new_head)
    {
        new_head->_num = num;
        if(str)
            new_head->_string = _strdupl(str);

        /*point the new_node to head */
        new_head->next = *head;

        /* point head to new_node */
        *head = new_head;
        return (new_head); 
    }
    return (NULL);
}









string_list_type * _append_node(string_list_type **head, char *str , int num)
{
    string_list_type *end_node, *last_node;


    if(!head)
        return (NULL);
    last_node = _create_node();
    if(last_node)
    {
        last_node->_num = num;
        if(str)
            last_node->_string = _strdupl(str);

        last_node->next = NULL;

        if (*head == NULL)
        {
            /* if the link list is empty , make last node as head*/
            *head = last_node;
            return (last_node);
        }
        end_node = *head;
        
        while(end_node->next != NULL )
            /* find the last node attached */
            end_node = end_node->next;


        /* point the end node to the last node */
        end_node->next = last_node;
 
        return (last_node);

    }
    return(NULL);
}





int _remove_node_at(string_list_type **head, unsigned int position)
{
    string_list_type *temp_node, *del_node, *prev_node;
    unsigned int index = 0;

    if(!head || !(*head))
        return (_FALSE);
    temp_node = *head;
    
    if(position == 0)
    {
        /*if position is head advance the head */
        *head = (*head)->next;

        /* temp node is the removed node(head) */
        _free_strlistnode(temp_node);

        return (_TRUE);
    }
    while (temp_node->next != NULL)
    {

        /*while not second to last */
        if (index == position)
        {   
            del_node = temp_node->next;
            temp_node->next = temp_node->next->next;
           
           _free_strlistnode(del_node);
        
            return(_TRUE);
        }
        /*record the current node and advance*/
        prev_node = temp_node;
        temp_node = temp_node->next;
        index++;
    }

    /* temp_node is the is last node */
    if(index == position)
    {
        /*if position is last node*/
        /* terminate link to last node*/
        prev_node->next = NULL;

        _free_strlistnode(temp_node);
        return (_TRUE);

    }
    return (_FALSE);


}

