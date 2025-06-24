/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_funs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:15:36 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/24 20:14:03 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int is_builtin(char *cmd)
{
    int its;

    its = 1;
    if (!cmd)
        return (1);
    if (ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "cd") == 0 
        || ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "unset") == 0 
            || ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "exit") == 0
                || ft_strcmp(cmd, "echo") == 0)
        its = 0;
    return (its);
}


int execute_builtin(char *cmd,t_env **env, char **args, t_data *d)
{
    if (!cmd)
        return (1);
    if (ft_strcmp(cmd, "env") == 0)
        env_v(*env, args);
    else if (ft_strcmp(cmd, "cd") == 0)
        cd_v(args, env, d);
    else if (ft_strcmp(cmd, "pwd") == 0)
        pwd_v();
    else if (ft_strcmp(cmd, "unset") == 0)
         unset_v(env, d, args);
    else if (ft_strcmp(cmd, "export") == 0)
        export_v(env, args, d);
    else if (ft_strcmp(cmd, "echo") == 0)
        echo_v(args);
    else if (ft_strcmp(cmd, "exit") == 0)
        exit_v(args);
    return (0);
}