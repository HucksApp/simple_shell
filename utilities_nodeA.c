
#include "shell.h"

/**
 * _create_node - Create a new node for a linked list
 * Return: Pointer to the newly created node or NULL on failure
 */

string_list_type *_create_node(void)
{
	string_list_type *new_node;

	new_node = malloc(sizeof(string_list_type));
	if (!new_node)
		return (NULL);
	/* init all memory bytes to null */
	_set_memory((void *)new_node, 0, sizeof(string_list_type));
	return (new_node);
}

/**
 * _prepend_node - Add a node to the beginning of a linked list
 * @headPointer: Pointer to the headPointer of the linked list
 * @str: String to be stored in the new node
 * @num: Number to be stored in the new node
 * Return: Pointer to the newly added node or NULL on failure
 */
string_list_type *_prepend_node(string_list_type **headPointer,
								char *str, int num)
{
	string_list_type *new_headPointer;

	if (!headPointer)
		return (NULL);
	new_headPointer = _create_node();
	if (new_headPointer)
	{
		new_headPointer->_num = num;
		if (str)
			new_headPointer->_string = _strdupl(str);

		/*point the new_node to headPointer */
		new_headPointer->next = *headPointer;

		/* point headPointer to new_node */
		*headPointer = new_headPointer;
		return (new_headPointer);
	}
	return (NULL);
}
/**
 * _append_node - Add a node to the end of a linked list
 * @headPointer: Pointer to the headPointer of the linked list
 * @str: String to be stored in the new node
 * @num: Number to be stored in the new node
 * Return: Pointer to the newly added node or NULL on failure
 */
string_list_type *_append_node(string_list_type **headPointer,
							   char *str, int num)
{
	string_list_type *end_node, *last_node;

	if (!headPointer)
		return (NULL);
	last_node = _create_node();
	if (last_node)
	{
		last_node->_num = num;
		if (str)
			last_node->_string = _strdupl(str);
		last_node->next = NULL;
		if (*headPointer == NULL)
		{ /* if the link list is empty , make last node as headPointer*/
			*headPointer = last_node;
			return (last_node);
		}
		end_node = *headPointer;
		while (end_node->next != NULL)
			end_node = end_node->next; /* find the last node attached */
		end_node->next = last_node;	   /* point the end node to the last node */
		return (last_node);
	}
	return (NULL);
}

/**
 * _remove_node_at - Remove a node at a specific pos in a linked list
 * @headPointer: Pointer to the headPointer of the linked list
 * @pos: index of the node to be removed
 * Return: TRUE if the node is successfully removed, FALSE otherwise
 */
int _remove_node_at(string_list_type **headPointer, unsigned int pos)
{
	string_list_type *tempNode, *del_node, *prev_node;
	unsigned int index = 0;

	if (!headPointer || !(*headPointer))
		return (_FALSE);
	tempNode = *headPointer;
	if (pos == 0)
	{
		*headPointer = (*headPointer)->next;
		_free_strlistnode(tempNode);
		return (_TRUE);
	}
	while (tempNode->next != NULL)
	{
		if (index == pos)
		{
			del_node = tempNode->next;
			tempNode->next = tempNode->next->next;
			_free_strlistnode(del_node);
			return (_TRUE);
		}
		prev_node = tempNode;
		tempNode = tempNode->next;
		index++;
	}
	if (index == pos)
	{
		prev_node->next = NULL;
		_free_strlistnode(tempNode);
		return (_TRUE);
	}
	return (_FALSE);
}
