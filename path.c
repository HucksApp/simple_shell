#include "shell.h"


char *_copy_path(char *path, int start, int stop)
{
    static char buffer[BUFFER_SIZE];
    int iter = 0, index = 0;
    char path_delim = ':';


    for (index = 0, iter = start; iter < stop; iter++)
        if (path[iter] != path_delim)
            buffer[index++] = path[iter];

    /*terminate buffer*/
    buffer[index] = 0;
    return (buffer);
}



int _is_eXe(char *path)
{
    struct stat file_stats;

    if(!path)
        return (_FALSE);
    if(stat(path , &file_stats))
        return (_FALSE);

    if(file_stats.st_mode & S_IFREG)
        return(_TRUE);

    return(_FALSE);

}





/* for futher path handling the shell obj passed as unsed */

char *_get_path(UNUSED shell_type *obj, char *paths, char *cmd_name)
{
    char *path;
    int is_valid = 0, iter = 0, index = 0;
    char path_delim = ':';

     printf("\n \n cmd => %s \n \n match => %s \n \n str len => %d \n \n", cmd_name, _match_str_path(cmd_name, "./"), str_len(cmd_name));
    if(!paths)
    {

        puts("return null.....");
        return (NULL);
    }
   
    if(is_valid && _is_eXe(cmd_name))

    is_valid = ((str_len(cmd_name) > 2) && _match_str_path(cmd_name, "./"))?
                        (_TRUE) : (_FALSE);
    
    {
        puts("in  get path");
        return (cmd_name);
    }

    while(_TRUE)
    {

        if (!paths[iter] || paths[iter] == path_delim)
        {
            path = _copy_path(paths, index, iter);
            
            if(!path)
                /* path is empty  add new path */
                _strconcat(path, cmd_name);
            
            else
            {
                /* add new path to path */
                _strconcat(path, "/");
                _strconcat(path, cmd_name);

            }

            if(!path[iter])
                break;

            if(_is_eXe(path))
                return(path);
            index = iter;
        }
        iter++;
    }
    return (NULL);

}


