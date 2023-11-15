#include "shell.h"




char *_read_file(char *file_name, int *read_length, ssize_t *file_size)
{
    ssize_t file_descriptor;
    struct stat file_info;
    char *buffer = NULL;
    

    
    file_descriptor = open(file_name, O_RDONLY);
    if(file_descriptor == SYS_ERROR)
        return (NULL);
    
    if(fstat(file_descriptor,&file_info) == 0)
        /* if file info is filled sucessfully */
            *file_size = file_info.st_size;
    if(*file_size < 2)
        return (NULL);

    buffer = malloc(sizeof(char) * ((*file_size) + 1));
    if(!buffer)
        return (NULL);

   
    *read_length = read(file_descriptor,buffer, (*file_size));

    /*terminate the buffer*/
    buffer[(*file_size)] = 0;

    if(*read_length <= 0)
    {
        free(buffer);
        return(NULL);
    }
    close(file_descriptor);
    return (buffer);
     
}



ssize_t _read_buffer(shell_type *obj, char *buffer, size_t *index)
{
    ssize_t read_index = 0;

    if(*index != 0)
        return (_FALSE);

    read_index = read(obj->_file_descriptor, buffer, BUFFER_SIZE);
    if(read_index >= 0)
        *index = read_index;
        
    return(read_index);
}

