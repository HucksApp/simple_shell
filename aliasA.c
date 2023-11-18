#include "shell.h"



int _patch_alias(shell_type *obj)
{
    int iter,assign_index;
    char *ch;
    string_list_type *node;

    
   
    for(iter = 0; iter < MAX_ALIAS; iter++)
    {   
        node = _match_node_str(obj->_aliases, obj->_tokens[0], '=');
        
        if(!node)
            return(_FALSE);

        free(obj->_tokens[0]);
        assign_index = _strchr('=', node->_string);
        ch = node->_string;

        if(!assign_index)
            return(_FALSE);

        ch =_strdupl(ch + (assign_index + 1));
        if(!ch)
            return(_FALSE);
        obj->_tokens[0] = ch; 
    }
    return(_TRUE);

}








/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _unset_alias(shell_type *obj, char *str)
{
	char *p, c;
	int ret;

	p = _strchr_ptr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = _remove_node_at(&(obj->_aliases),
		_get_node_index(obj->_aliases, _match_node_str(obj->_aliases, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int _set_alias(shell_type *obj, char *str)
{
	char *ptr;

	ptr = _strchr_ptr(str, '=');

	if (!ptr)
		return (1);
	if (!*++ptr)
		return (_unset_alias(obj, str));

	_unset_alias(obj, str);
	return (_append_node(&(obj->_aliases), str, 0) == NULL);
}


/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _alias(shell_type *obj)
{
	int index = 0;
	char *ptr = NULL;
	string_list_type *node = NULL;

	if (obj->_token_count == 1)
	{
		node = obj->_aliases;
		for(; node; node = node->next)
		{
			
			_print_alias(node);	
		}
		printf("-------[%s]",node->_string);
		return (0);
	}
	for (index = 1; obj->_tokens[index]; index++)
	{
		ptr = _strchr_ptr(obj->_tokens[index], '=');
		printf("-----alias %s-------", ptr);
		if (ptr)
			_set_alias(obj, obj->_tokens[index]);
		else
			_print_alias(_match_node_str(obj->_aliases, obj->_tokens[index], '='));
	}
	return (0);
}
