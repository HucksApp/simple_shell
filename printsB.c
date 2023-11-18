#include "shell.h"






size_t _print_node(string_list_type *head)
{
	size_t index= 1;
	string_list_type *node = head;
		_write_string(node->_string ? node->_string : "(nil)", 1);
		_write_string("\n", 1);
	return (index);
}
