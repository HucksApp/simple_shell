#include "shell.h"

/**
 * _set_memory - set memory
 * is alocated dynamically
 * @ptr: pointer to memory location
 * @c: byte value to set
 * @size: number of byte to set
 * Return: pointer to memory location
 */

char *_set_memory(char *ptr, char c, unsigned int size)
{
	unsigned int iter;
	for (iter = 0; iter < size; iter++)
		/* cast to unsigned chat to ensure 'its in bytes' */
		ptr[iter] = (unsigned char)c;
	return (ptr);
}

int _free_str_in_str(char **str)
{
	if (*str && str)
	{
		_free(*str);
		*str = NULL;
		return (_TRUE);
	}
	return (_FALSE);
}

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int indexes;
	char *new_ptr = NULL;

	if (!ptr || !old_size)
		return (malloc(new_size));

	if (!new_size)
	{
		_free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);
	new_ptr = malloc(new_size);

	/* copy old pointer pointer address to new pointer*/
	indexes = (new_size > old_size) ? (old_size) : (new_size);

	while (indexes--)
		new_ptr[indexes] = ((char *)ptr)[indexes];
	_free(ptr);

	if (!new_ptr)
		return (NULL);
	return (new_ptr);
}

void _free_node_lists(string_list_type **head_ptr)
{
	string_list_type *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->_string);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
