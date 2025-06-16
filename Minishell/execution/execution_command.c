/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:43:49 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/16 10:36:59 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char **get_env(t_env *env, t_data *d)
{
	t_env	*current;
	t_env 	*saved_current;
	char	**envs;
	int i;

	current = env;
	saved_current = current;
	i = 0;
	while(current)
	{
		i++;
		current = current->next;
	}
	envs = ft_malloc(i + 1 * sizeof(char *), d);
	i = 0;
	while(saved_current)
	{
		envs[i] = ft_strdup(saved_current->both, d);
		saved_current = saved_current->next;
	}
	envs[i] = NULL;
	return(envs);
}
int execution(t_env **env, t_cmd *cmds, t_data *d)
{
	int saved_stdin;
	int saved_stdout;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	
	if (apply_redirection(cmds, d) != 0)
	{
		duping(saved_stdin,saved_stdout);
		return (1);
	}
	if (is_builtin(cmds->cmd) == 0 && cmds->pipe == 0)
	{
		

		if (execute_builtin(cmds->cmd, env, cmds->args, d) != 0)
		{
			duping(saved_stdin,saved_stdout);
			return (1);
		}
		duping(saved_stdin,saved_stdout);
	}
	else
	{
		char **str = get_path(*env, d);
		if (!str)
		{
    		ft_putstr_fd("minishell: command not found\n", 2);
   			return (1);
		}
		char *path = right_path(str, cmds, d);
		char **envs = get_env(*env, d);
		if(execve(path, cmds->args, envs) != 0)
		{
			if(path)
				perror("execve");
			exit(1);
		}
		duping(saved_stdin,saved_stdout);
	}
	return (0);
}
