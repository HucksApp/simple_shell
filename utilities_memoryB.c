#include "shell.h"

/**
 * _set_memory - Set memory to a specific byte value
 * @ptr: Pointer to the memory location
 * @c: Byte value to set
 * @size: Number of bytes to set
 * Return: Pointer to the memory location
 */

char *_set_memory(char *ptr, char c, unsigned int size)
{
	unsigned int iter;

	for (iter = 0; iter < size; iter++)
		/* cast to unsigned chat to ensure 'its in bytes' */
		ptr[iter] = (unsigned char)c;
	return (ptr);
}
/**
 * _free_str_in_str - Free memory allocated for a string pointer
 * @str: Pointer to the string pointer
 * Return: TRUE if memory is successfully freed, FALSE otherwise
 */

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
/**
 * _realloc - Reallocate memory for a pointer to a new size
 * @ptr: Pointer to the memory location to be reallocated
 * @old_size: Old size of the memory block
 * @new_size: New size of the memory block
 * Return: Pointer to the reallocated memory block
 */
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
/**
 * _free_node_lists - Free memory allocated for a linked list of nodes
 * @head_ptr: Pointer to the head of the linked list
 */
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
/**
 * _free_string_list - Free memory allocated for an array of strings
 * @str_list: Pointer to the array of strings
 */
void _free_string_list(char **str_list)
{
	int index;

	if (str_list)
	{
		for (index = 0; str_list[index]; index++)
			_free(str_list[index]);
		free(str_list);
	}
}
