
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
 * @head: Pointer to the head of the linked list
 * @str: String to be stored in the new node
 * @num: Number to be stored in the new node
 * Return: Pointer to the newly added node or NULL on failure
 */
string_list_type *_prepend_node(string_list_type **head, char *str, int num)
{
	string_list_type *new_head;

	if (!head)
		return (NULL);
	new_head = _create_node();
	if (new_head)
	{
		new_head->_num = num;
		if (str)
			new_head->_string = _strdupl(str);

		/*point the new_node to head */
		new_head->next = *head;

		/* point head to new_node */
		*head = new_head;
		return (new_head);
	}
	return (NULL);
}
/**
 * _append_node - Add a node to the end of a linked list
 * @head: Pointer to the head of the linked list
 * @str: String to be stored in the new node
 * @num: Number to be stored in the new node
 * Return: Pointer to the newly added node or NULL on failure
 */
string_list_type *_append_node(string_list_type **head, char *str, int num)
{
	string_list_type *end_node, *last_node;

	if (!head)
		return (NULL);
	last_node = _create_node();
	if (last_node)
	{
		last_node->_num = num;
		if (str)
			last_node->_string = _strdupl(str);
		last_node->next = NULL;
		if (*head == NULL)
		{	/* if the link list is empty , make last node as head*/
			*head = last_node;
			return (last_node);
		}
		end_node = *head;
		while (end_node->next != NULL)
			end_node = end_node->next; /* find the last node attached */
		end_node->next = last_node; 	/* point the end node to the last node */
		return (last_node);
	}
	return (NULL);
}

/**
 * _remove_node_at - Remove a node at a specific position in a linked list
 * @head: Pointer to the head of the linked list
 * @position: Position of the node to be removed
 * Return: TRUE if the node is successfully removed, FALSE otherwise
 */
int _remove_node_at(string_list_type **head, unsigned int position)
{
	string_list_type *temp_node, *del_node, *prev_node;
	unsigned int index = 0;

	if (!head || !(*head))
		return (_FALSE);
	temp_node = *head;
	if (position == 0)
	{
		*head = (*head)->next; /*if position is head advance the head */
		_free_strlistnode(temp_node); /* temp node is the removed node(head) */
		return (_TRUE);
	}
	while (temp_node->next != NULL)
	{
		if (index == position)
		{ /*while not second to last */
			del_node = temp_node->next;
			temp_node->next = temp_node->next->next;
			_free_strlistnode(del_node);
			return (_TRUE);
		}
		prev_node = temp_node; /*record the current node and advance*/
		temp_node = temp_node->next;
		index++;
	}
	if (index == position) /* temp_node is the is last node */
	{	/*if position is last node*/
		prev_node->next = NULL; /* terminate link to last node*/
		_free_strlistnode(temp_node);
		return (_TRUE);
	}
	return (_FALSE);
}
