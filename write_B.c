#include "shell.h"





int _write_char_to_stdeout(char next_char, UNUSED int file_descriptor)
{
    static char buffer_out[BUFFER_SIZE];
    

    /* static index to keep track of error buffer */
    static int buffer_index;
    int buff_flush;

     buff_flush = _buffer_flush(next_char, buffer_index, buffer_out);
     if(buff_flush)
    {
        write(STDOUT_FILENO, buffer_out, buffer_index);
        /* buffer flushed reset buffer index */
        buffer_index = 0;
    }
    return (1);
}
