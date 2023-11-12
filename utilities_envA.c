#include "shell.h"

/**
 * to populate the system enviroment variables
 * its Type char ** (string array)
 * its pass as as third argument in main
 * main(int argc, char ** argv, char ** env )
 * or
 *  as external variable environ
 * Type char **
 * extern char **environ
*/






char** _get_envs(shell_type *obj)
{
    if (!obj->_env || obj->_env_changed)
    {
      obj->_env = _node_to_stringlist(obj->_envs);
      obj->_env_changed = _FALSE;   
    }
    return (obj->_env);
}




int _unset_env(shell_type *obj, char *var)
{
    string_list_type *envs_head = obj->_envs;

    size_t index ;

    if(!obj || !var)
        return (_FALSE);

    for(index = 0; envs_head != NULL; index++)
    {
        if(_match_env(envs_head->_string, var))
        {

            obj->_env_changed = _remove_node_at(&(obj->_envs), index);
            index = 0;
            envs_head = obj->_envs;
            continue;
        }
        envs_head = envs_head->next;
    }
    return (obj->_env_changed);
}



int _set_env(shell_type *obj, char * var, char *var_value)
{
    string_list_type *envs_head = NULL ;
    char * buffer_tmp = NULL;

    if(!var || !var_value)
        return(_FALSE);

    buffer_tmp = malloc(sizeof(char) * (str_len(var) + str_len(var_value) + 2));
    if(!buffer_tmp)
        return (_FALSE);
    _strcpy(buffer_tmp, var);
    _strcpy(buffer_tmp, "=");
    _strcpy(buffer_tmp, var_value);
    envs_head = obj->_envs;

    for( ;envs_head != NULL; envs_head = envs_head->next)

        if(_match_env(envs_head->_string, var))
        {
            /*env match found*/
            free(envs_head->_string);
            envs_head->_string = buffer_tmp;
            obj->_env_changed = _TRUE;
            return(_TRUE);
        }
    _append_node(&(obj->_envs), buffer_tmp, 0);
    free(buffer_tmp);
    obj->_env_changed = _TRUE;
    return(_TRUE);
}



int _match_env(char *envs_path, char *env_new)
{
    int is_same;
    int len_to_compare = str_len(env_new) ;
    char can_assign = '=';

    is_same = _strcmpr(envs_path, env_new, len_to_compare);
    if (is_same && envs_path[len_to_compare] == can_assign)
        return (_TRUE);
    return (_FALSE);
  
}







