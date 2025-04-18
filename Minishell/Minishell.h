/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:17:27 by moel-hai          #+#    #+#             */
/*   Updated: 2025/04/18 14:19:43 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
// #include <>
// #include <>
// #include <>
// #include <>

typedef enum s_redir_type {
    REDIR_IN,       // <
    REDIR_OUT,      // >
    REDIR_APPEND,   // >>
    REDIR_HEREDOC   // <<
} t_redir_type;

typedef struct s_redir
{
    t_redir_type type;
    char *file;
    struct s_redir *next;
} t_redir;

typedef struct s_cmd
{
    char *cmd;         // command name (e.g., "echo")
    char **args;       // arguments including cmd
    t_redir *redir;    // list of redirections
    bool pipe;         // true if pipe to next
    struct s_cmd *next;
} t_cmd;

typedef struct s_heap
{
    void    *address;
    struct s_heap   *next;
}   t_heap;

typedef struct s_cmd
{
    char *cmd;         // command name (e.g., "echo")
    char **args;       // arguments including cmd
    t_redir *redir;    // list of redirections
    bool pipe;         // true if pipe to next
    struct s_cmd *next;
} t_cmd;

typedef struct s_data
{
    char    *line;
    t_heap  *heap;
    char    *path;
    //
}   t_data;

# endif