
#include "shell.h"
/**
 * _get_node_index - Get the index of a node in a linked list
 * @head: Pointer to the head of the linked list
 * @node: Pointer to the node whose index is to be found
 * Return: Index of the node if found, or SYS_ERROR if not found
 */
ssize_t _get_node_index(string_list_type *head, string_list_type *node)
{
	size_t index;
	string_list_type *current_node;

	current_node = head;
	for (index = 0; current_node != NULL;
		 index++, current_node = current_node->next)
		if (current_node == node)
			return (index);
	return (SYS_ERROR);
}
/**
 * _node_length - Calculate the length of a linked list
 * @head: Pointer to the head of the linked list
 * Return: Length of the linked list
 */
size_t _node_length(string_list_type *head)
{
	size_t length;
	string_list_type *current_node;

	current_node = head;
	for (length = 0; current_node; length++, current_node = current_node->next)
		;
	return (length);
}
/**
 * _node_to_stringlist - Convert a linked list of strings to a string array
 * @head: Pointer to the head of the linked list
 * Return: String array containing the strings from the linked list
 */

char **_node_to_stringlist(string_list_type *head)
{
	string_list_type *current_node;
	char **str_list;
	size_t str_list_len, iter;

	if (!head)
		return (NULL);
	current_node = head;
	str_list_len = _node_length(current_node);
	if (!str_list_len)
		return (NULL);
	str_list = malloc(sizeof(char *) * (str_list_len + 1));
	if (!str_list)
		return (NULL);
	for (iter = 0; current_node; iter++, current_node = current_node->next)
	{
		str_list[iter] = strdup(current_node->_string);
		if (str_list[iter] == NULL)
		{
			_free_string_list(str_list);
			return (NULL);
		}
	}
	str_list[iter] = NULL; /*terminate the string list*/
	return (str_list);
}
/**
 * _match_node_str - Find a node in a linked list with a matching key string
 * @node: Pointer to the head of the linked list
 * @key: Key string to match
 * @c: Character to match in the key string, or -1 to match any character
 * Return: Pointer to the matched node, or NULL if not found
 */

string_list_type *_match_node_str(string_list_type *node,
								  char *key, char c)
{
	char *str = NULL;

	while (node)
	{
		str = _match_str_path(node->_string, key);
		if (str && ((c == -1) || (*str == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
