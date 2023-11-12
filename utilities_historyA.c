#include "shell.h"

void _history_size_monitor(shell_type *obj)
{
	int size;

	size = obj->_history_count;
	for (; size >= HISTORY_SIZE; size--)
		_remove_node_at(&(obj->_history), 0);
	_history_indexing(obj);
}
