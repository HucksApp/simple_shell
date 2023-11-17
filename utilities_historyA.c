#include "shell.h"
/**
 * _history_size_monitor - Monitor the size of the history
 *  and trim it if necessary
 * @obj: Shell object containing history information
 */
void _history_size_monitor(shell_type *obj)
{
	int size;

	size = obj->_history_count;
	for (; size >= HISTORY_SIZE; size--)
		_remove_node_at(&(obj->_history), 0);
	_history_indexing(obj);
}
