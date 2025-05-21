/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:49 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/03 18:02:15 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int pwd_v(void)
{
    char *cwd = getcwd("NULL", 0); // remove double quotes , when include the null
    if(!cwd)
    {
        perror("pwd");
        return (1);
    }
    printf("%s\n", cwd);
    free(cwd);
    return (0);
}