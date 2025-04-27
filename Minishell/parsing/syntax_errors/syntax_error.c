/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:20:24 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/27 01:24:03 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

// syntax error near unexpected token `|'


// 🏀 --> Group 1: Pipe errors (|)
// 👉 Pipes must be between two valid commands.

// Pipe at start.					--->

// Pipe at end.					--->

// Pipe next to another pipe.		--->

// 🚨 message to printf : "syntax error near unexpected token `|`" 🚨




// 🏀 ---> Group 2: Redirection errors (<, >, >>, <<)
// 👉 Redirections must be followed by a valid file/token.

// Redirection at end.		STR = "newline"							--->

// Redirection followed by another symbol.	STR = the second symbol	--->

// 🚨 message to printf : "syntax error near unexpected token `$STR'" 🚨


// void    handle_syntax_error(t_token *t)
// {
//     int i;
    
//     i = 0;
    
// }