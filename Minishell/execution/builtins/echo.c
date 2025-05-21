/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:21:33 by ielouarr          #+#    #+#             */
/*   Updated: 2025/05/03 16:51:06 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int echo_v(char **args)
{
    int i;
    int new_line;

    i = 1;
    new_line = 1;
    
    if(args[1] && ft_strcmp(args[1], "-n") == 0)
    {
        new_line = 0;
        i++;
    }
    while(args[i])
    {
        printf("%s", args[i]);
        if(args[i + 1])
            printf(" ");
        i++;
    }
    if(new_line)
        printf("\n");
    return 0;
}