#include "shell.h"



int _shell_exit(shell_type *obj)
{
    int _is_exit;

    if(obj->_tokens[1])
    {
        _is_exit = _atoi(obj->_tokens[1]);
        if(_is_exit == SYS_ERROR)
        {
            obj->_status = 2;
            _print_error_msg (obj, "can't cd to ");
            _write_string(obj->_tokens[1], STDERR_FILENO);
            _write_char_to_stderr('\n', STDERR_FILENO);
            return(_FALSE);
        }
        obj->_error_num = _atoi(obj->_tokens[1]);
        return (EXIT_SIG); 
    }
    obj->_error_num = SYS_ERROR;
    return(EXIT_SIG);
}






int _shell_cd(shell_type *obj)
{

    char *str, *dir, buffer[BUFFER_SIZE];
    int ch_dir ;

    str = getcwd(buffer, BUFFER_SIZE);

    if(!str)
    /* ADD BETTER HANDLING*/
        exit(EXIT_FAILURE); 


        /* cd alone is passed*/
    if(!obj->_tokens[1])
    {
        dir = _shell_getenv(obj, "HOME=");
        if(dir)
            ch_dir = chdir(dir);
        else
            ch_dir = chdir((dir = _shell_getenv(obj, "PWD="))? dir : "/");
    }
    else if (_strcmpr(obj->_tokens[1], "-",1))
    {
        /* if no old pwd */
        if(!_shell_getenv(obj, "OLDPWD="))
        {
            _write_string(str,STDOUT_FILENO);
            _write_char_to_stdeout('\n', STDOUT_FILENO);
            return(EXIT_SUCCESS);
        }
        _write_string(_shell_getenv(obj, "OLDPWD="), STDOUT_FILENO);
        ch_dir = chdir(dir = _shell_getenv(obj, "OLDPWD="));
    }
    else
        ch_dir = chdir(obj->_tokens[1]);

    if(ch_dir == SYS_ERROR )
    {
        _print_error_msg(obj, "can't cd to ");
        _write_string(obj->_tokens[1], STDERR_FILENO);
        _write_char_to_stderr('\n', STDERR_FILENO);
    }
    else
    {
        _set_env(obj,  "OLDPWD", _shell_getenv(obj, "PWD="));
        _set_env(obj,"PWD", getcwd(buffer, BUFFER_SIZE));
    }
    return(EXIT_SUCCESS);

}




int _shell_help(shell_type *obj)
{
    int length, index;
    char *msgs[6] = {NULL};

    msgs[0] = HELP_MSG;
    msgs[1] = HELP_EXIT_MSG;
	msgs[2] = HELP_ENV_MSG;
	msgs[3] = HELP_SETENV_MSG;
	msgs[4] = HELP_UNSETENV_MSG;
	msgs[5] = HELP_CD_MSG;

    if(obj->_tokens[1] == NULL)
    {
        _write_string(msgs[0]+ 6,STDOUT_FILENO);
        return (EXIT_SUCCESS);

    }
    if(obj->_token_count <= 1 )
    {
        errno = E2BIG;
        perror(obj->_tokens[1]);
        return(EXIT_FAILURE);
    }

    length = str_len(obj->_tokens[1]);
    for (index = 0; msgs[index]; index++)
    
        if (_strcmpr((obj->_tokens[1]), msgs[index], length))
        {
            _write_string(msgs[index]+ length +1 ,STDOUT_FILENO);
            return (EXIT_SUCCESS);
        }
    
    errno = EINVAL;
    perror(obj->_tokens[1]);
    return (EXIT_FAILURE);
}
