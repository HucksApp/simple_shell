#include "shell.h"

/**
 * is_dynamic_mem - Check if memory is dynamically allocated for a string
 * @str: String variable to check
 * Return: 0 (false) or 1 (true)
 */

int is_dynamic_mem(char *str)
{
	if (str == NULL)
		return (_FALSE);
	/* Check if the string pointer points to the stack */
	return ((void *)str >= (void *)&str ? (_FALSE) : (_TRUE));
}

/**
 * _free_strlistnode - Free memory allocated for a node in a linked list
 * @node: Node to be freed
 */

void _free_strlistnode(string_list_type *node)
{
	if (node && is_dynamic_mem(node->_string))
		node->next = NULL;
	free(node->_string);
	free(node);
}

/**
 * _free_strlistnode2 - Free memory allocated for a linked list of nodes
 * @node: Head of the linked list
 */

void _free_strlistnode2(string_list_type *node)
{
	string_list_type *current = node;
	string_list_type *next;

	while (current != NULL)
	{
		next = current->next;
		free(current->_string);
		free(current);
		current = next;
	}
}

/**
 * _free - Free memory if allocated dynamically
 * @str: String variable to be freed
 */

void _free(char *str)
{
	if (is_dynamic_mem(str))
		free(str);
}
/**
 * _free_array - Free memory allocated for an array of strings
 * @arr: Array of strings to be freed
 */
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
