/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:51 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/23 17:39:07 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../Minishell.h"

// void	remove_from_env(t_env **env_lst, char **args)
// {
// 	t_env	*prev;
// 	t_env 	*curr;
// 	int		i;

// 	i = 0;
// 	prev = NULL;
// 	curr = *env_lst;
// 	while(args[i])
// 	{
// 		if (ft_strcmp(curr->key, args[i]) == 0)
// 		{
// 			if(prev)
// 				prev->next = curr->next;
// 			else
// 				*env_lst = curr->next;
// 			free(curr->key);
// 			free(curr->value);
// 			free(curr->both);
// 			free(curr);
// 			break;
// 		}
// 		prev = curr;
// 		curr = curr->next;
// 	}
// }
// void	remove_from_exp(t_exp **exp_lst, char **args)
// {
// 	t_env	*prev;
// 	t_env 	*curr;
// 	int		i;

// 	i = 0;
// 	prev = NULL;
// 	curr = *exp_lst;
// 	while(args[i])
// 	{
// 		if (ft_strcmp(curr->key, args[i]) == 0)
// 		{
// 			if(prev)
// 				prev->next = curr->next;
// 			else
// 				*exp_lst = curr->next;
// 			free(curr->key);
// 			free(curr->value);
// 			free(curr->both);
// 			free(curr);
// 			break;
// 		}
// 		prev = curr;
// 		curr = curr->next;
// 	}
// }
// int unset_v(t_env **env_lst, t_exp **exp_lst, char **args)
// {
// 	remove_from_env(env_lst, args);
// 	remove_from_exp(exp_lst, args);
// }