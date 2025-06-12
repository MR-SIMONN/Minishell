/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:39 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/25 17:10:49 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

char *check_if_env_set(t_env *env_lst, char *env_key)
{
    t_env *tmp = env_lst;
    
    while (tmp)
    {
        if (ft_strcmp(tmp->key, env_key) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

void update_env_var(t_env **env_lst, char *key, char *value, t_data *d)
{
    t_env *tmp = *env_lst;

    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(value, d);
            return;
        }
        tmp = tmp->next;
    }

    // If not found, add new
    t_env *new_node = ft_malloc(sizeof(t_env), d);
    if (!new_node)
        return;
    new_node->key = ft_strdup(key, d);
    new_node->value = ft_strdup(value, d);
    new_node->next = *env_lst;
    *env_lst = new_node;
}

// Updates OLDPWD and PWD after cd
void update_env_cd(t_env **env, t_data *d)
{
    char *old_pwd = check_if_env_set(*env, "PWD");
    char new_pwd[1024];

    if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
    {
        perror("getcwd");
        return;
    }

    if (old_pwd)
        update_env_var(env, "OLDPWD", old_pwd, d);
    update_env_var(env, "PWD", new_pwd, d);
}


int cd_v(char **args, t_env **env, t_data *d)
{
    const char *target_path;
    
    target_path = NULL;
    if (!args[1])
    {
        target_path = check_if_env_set(*env, "HOME");
        if (!target_path)
        {
            printf("minishell: cd: HOME not set\n");
            return (1);
        }
    }
    else if (ft_strcmp(args[1], "-") == 0)
    {
        target_path = check_if_env_set(*env, "OLDPWD");
        if (!target_path)
        {
            printf("minishell: cd: OLDPWD not set\n");
            return (1);
        }
        printf("%s\n", target_path);
    }
    else
    {
        target_path = args[1];
    }

    if (chdir(target_path) != 0)
    {
        perror("cd");
        return (1);
    }

    update_env_cd(env, d);
    return (0);
}
