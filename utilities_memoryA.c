#include "shell.h"

/**
 * is_dynamic_mem - check string if memory
 * is alocated dynamically
 * @str: string var to check
 * Return: 0 false or 1 true
 */

int is_dynamic_mem(char *str)
{
	if (str == NULL)
		return _FALSE;
	/* Check if the string pointer points to the stack */
	return ((void *)str >= (void *)&str ? (_FALSE) : (_TRUE));
}

/**
 * _free -free memory allocated to node
 * @node: node
 */

void _free_strlistnode(string_list_type *node)
{
	if (node && is_dynamic_mem(node->_string))
		node->next = NULL;
	free(node->_string);
	free(node);
}

/**
 * _free -free memory if alocated dynamically
 * @str: string var free
 */

void _free(char *str)
{
	if (is_dynamic_mem(str))
		free(str);
}

void _free_array(char **arr)
{
	int iter;

	if (arr)
	{
		for (iter = 0; *arr; iter++)
			/*check to see if its dynamic memory before freeing*/
			_free(arr[iter]);

		free(arr);
		arr = NULL;
	}
}

void _free_string_list(char **str_list)
{
	int index;
	for (index = 0; str_list[index]; index++)
		_free(str_list[index]);
	free(str_list);
}
