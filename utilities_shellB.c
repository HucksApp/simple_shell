#include "shell.h"




int _is_linked_stream(shell_type *obj, char *buffer, size_t *chain_pos)
{
    size_t index = *chain_pos;

    if(_strcmpr((buffer + index), "||", 2))
    {
        buffer[index] = 0;
        index++;
        obj->_chain_stream_type = CMD_OR;
    }
    else if (_strcmpr((buffer + index), "&&", 2))
    {
        buffer[index] = 0;
        index++;
        obj->_chain_stream_type = CMD_AND;
    }
    else if (_strcmpr((buffer + index), ";", 1))
    {
        buffer[index] = 0;
        index++;
        obj->_chain_stream_type = CMD_CHAIN;
    }
    else
        return (_FALSE);
    
    *chain_pos = index;
    return(_TRUE);
}








int _swap_tokens(shell_type *obj)
{
    int index;
    char *str;
    string_list_type *node;

    for(index = 0; obj->_tokens[index]; index++)
    {
        if(obj->_tokens[index][0] != '$' || obj->_tokens[index][1])
            continue;

        if(!_strcmpr(obj->_tokens[index], "$?", 2))
        {
            str = _strdupl(_convert_number(obj->_status, 10, 10));
            _swap_string(&(obj->_tokens[index]), str);
            continue;
        }

        if(!_strcmpr(obj->_tokens[index], "$$", 2))
        {
            str = _strdupl(_convert_number(getpid(), 10, 0));
            _swap_string(&(obj->_tokens[index]), str);
            continue;
        }

        node = _match_node_str(obj->_envs, &(obj->_tokens[index][1]), '=');

        if(node)
        {
            str = _strdupl(_strchr_ptr(node->_string, '=') + 1);
            _swap_string(&(obj->_tokens[index]), str);
            continue;
        }
        _swap_string(&(obj->_tokens[index]), _strdupl("") );

    }
    return (EXIT_SUCCESS);
}





void _next_linkedstream(shell_type *obj, char *buffer,
                        size_t length, size_t index, size_t *position )
{

        size_t curr_pos = *position;

        if(obj->_chain_stream_type == CMD_OR)
        {
            if(!obj->_status)
            {
                buffer[index] = 0;
                curr_pos = length;
            }
        }

        if(obj->_chain_stream_type == CMD_AND)
        {
            if(obj->_status)
            {/* terminate buffer */
                buffer[index] = 0;
                curr_pos=length;
            }
        }

        *position  = curr_pos;  
}








/*
void _find_cmd(shell_type *obj)
{
 return;
}




void _fork_cmd(shell_type *obj)
{
    return;
}
*/




