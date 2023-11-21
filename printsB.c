#include "shell.h"
/**
 * _print_node - Prints the content of a node in a linked list
 * @head: Pointer to the head of the linked list
 * Return: Number of nodes printed
 */
size_t _print_node(string_list_type *head)
{
	size_t index = 0;
	string_list_type *node = head;

	while (node)
	{
		_write_string(node->_string ? node->_string : "(nil)", 1);
		_write_string("\n", 1);
		index++;
		node = node->next;
	}
	return (index);
}
