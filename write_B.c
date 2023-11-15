#include "shell.h"





int _write_char_to_stdeout(char next_char, UNUSED int file_descriptor)
{
    static char buffer[BUFFER_SIZE];
    

    /* static index to keep track of error buffer */
    static int buffer_index;
    int buff_flush;
    
     buff_flush = _buffer_flush(next_char, &buffer_index, buffer);
     if(buff_flush)
    {
        
        write(1, buffer, buffer_index);
        /* buffer flushed reset buffer index */
        buffer_index = 0;
    }
    return (1);
}




void _buffer_remove_comment(char *buffer)
{
    int index;

    for(index = 0; buffer[index] != null; index++)

        if(buffer[index] == '#' && (buffer[index - 1] == ' ' || index == 0))
        {
            buffer[index] = null;
            break;
        }
}

