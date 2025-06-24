/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_funs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:28:10 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/24 20:52:14 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char **get_path(t_env *env, t_data *d)
{
    t_env *current = env;
    
    while(current)
    {
        if(ft_strcmp(current->key, "PATH") == 0)
            break;
        current = current->next;
    }
    
    if (!current || !current->value)
        return (NULL);
        
    return (ft_splits(current->value, ':', d));
}

char **get_env(t_env *env, t_data *d)
{
    t_env *current = env;
    t_env *saved_current = current;
    char **envs;
    int i = 0;

    while(current)
    {
        i++;
        current = current->next;
    }
    
    envs = ft_malloc((i + 1) * sizeof(char *), d);
    i = 0;
    
    while(saved_current)
    {
        envs[i] = ft_strdup(saved_current->both, d);
        saved_current = saved_current->next;
        i++;
    }
    envs[i] = NULL;
    
    return envs;
}

char *get_fullpath(char *path, char *command, t_data *d)
{
    char *slash;
    char *full_path;
    slash = ft_strjoin(path, "/", d);
    full_path = ft_strjoin(slash, command, d);
    return (full_path);
}

int	is_directory(char *path)
{
	DIR *dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int last_char(char *path)
{
    int i;

    i=0;
    while(path[i])
        i++;
    return (i - 1);
}

int	is_exec(char *path, t_cmd *cmds, int silent)
{
	if(path[last_char(path)] == '/')
    {
        if (is_directory(path))
	    {
		    if (!silent)
			    this_is_a_directory(cmds->cmd);
		    return (126);
	    }
        else
        {
            ft_putstr_fd("minishell: ", 1);
            ft_putstr_fd(path, 1);
            ft_putstr_fd(": No such file or directory\n", 1);
            return(127);
        }
    }
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) != 0)
		{
			if (!silent)
				return (permission_denied_error(path));
			return (126);
		}
		return (0);
	}
	if (!silent)
		return (command_not_found_error(cmds->cmd));
	return (127);
}


char *right_path(char **paths, t_cmd *cmds, t_data *d)
{
    int i = 0;
    char *full_path;

    if (!cmds->cmd)
        return (NULL);
    
    if (cmds->cmd[0] == '/' || cmds->cmd[0] == '.')
    {
        if (is_exec(cmds->cmd, cmds, 0) == 0)
            return (ft_strdup(cmds->cmd, d));
        return (NULL);
    }
    
    if(cmds->cmd[last_char(cmds->cmd)] == '/')
    {
        if (is_directory(cmds->cmd))
	    {
			this_is_a_directory(cmds->cmd);
		    return (NULL);
	    }
        else
        {
            ft_putstr_fd("minishell: ", 1);
            ft_putstr_fd(cmds->cmd, 1);
            ft_putstr_fd(": No such file or directory\n", 1);
            return(NULL);
        }
    }
    if (!paths)
    {
        command_not_found_error(cmds->cmd);
        return (NULL);
    }

    while (paths[i])
    {
        full_path = get_fullpath(paths[i], cmds->cmd, d);
        if (is_exec(full_path, cmds, 1) == 0)
            return (full_path);
        i++;
    }
    
    command_not_found_error(cmds->cmd);
    return (NULL);
}