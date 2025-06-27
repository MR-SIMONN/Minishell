/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:46:33 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/27 16:24:45 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int apply_output_redirection(t_str *files)
{
	int fd;

	fd = -1;
	if (files->type == APPEND_FILE)
		fd = open(files->s, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(files->s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(files->s);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int apply_input_redirection(t_str *files)
{
	int fd;
	
	fd = -1;
	fd = open(files->s, O_RDONLY);
	if (fd == -1)
	{
		perror(files->s);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int apply_redirections(t_str *files)
{
    t_str *last_input = NULL;
    t_str *last_output = NULL;
    t_str *current = files;
    
    while (current)
    {
        if (current->type == IN_FILE)
            last_input = current;
        else if (current->type == OUT_FILE || current->type == APPEND_FILE)
            last_output = current;
        current = current->next;
    }
    
    if (last_input && apply_input_redirection(last_input) != 0)
        return (1);
    if (last_output && apply_output_redirection(last_output) != 0)
        return (1);
    
    return (0);
}

void signal_herdoc(int sig)
{
    (void)sig;
    exit_status(1, 1);
    write(STDOUT_FILENO, "\n", 1);
    exit(130);
}

int apply_herdoc(t_cmd *cmd, t_data *d, int index)
{
    t_str *current;
    int fd = -1;
    char *exp;
    char *name;
    int status;
    // struct termios  tty;

    current = cmd->heredoc_del;
    if (fd >= 0)
            close(fd);
    name = ft_strjoin(".heredoc_", ft_itoa(index, d), d);
    cmd->heredocfilename = ft_strdup(name, d);
    fd = open(cmd->heredocfilename, O_CREAT | O_RDWR, 0644);
    while(current)
    {
        signal(SIGINT,SIG_IGN);
        int pid = fork();
        if(pid == 0)
        {
            signal(SIGINT, handle_sigint);
            if(fd < 0)
			{
				perror("open .heredoc file");
				return (1);
			}
            while(1)
            {
                d->line = readline(">");
                if (!d->line)
                    break;
                if(ft_strcmp(current->s, d->line) == 0)
                {
                    free(d->line);
                    d->line = NULL;
                    break;
                }
                if(current->expendable != 0)
                {
                    exp = expand_heredoc(d->line, d);
                    ft_putstr_fd(exp, fd);
                    ft_putstr_fd("\n", fd);
                    if (exp != d->line)
                        free(exp);
                }
                else
                {
                    ft_putstr_fd(d->line, fd);
                    ft_putstr_fd("\n", fd);
                }
                free(d->line);
                d->line = NULL;
            }
            exit(0);
        }
        else
        {
            waitpid(pid,&status,0);
            signal(SIGINT,handle_sigint);
            // tcgetattr(STDIN_FILENO, &tty);
            // tty.c_lflag |= ECHO;
            // tcsetattr(STDIN_FILENO, TCSANOW, &tty);
            if(WIFEXITED(status) == 1 && WEXITSTATUS(status) == 130)
                return (exit_status(1, 1), 130);
        }
        current = current->next;
    }
    return (0);
}
// int apply_herdoc(t_cmd *cmd, t_data *d, int index)
// {
// 	t_str *current;
// 	int fd = -1;
// 	char *exp;
// 	char *name;

// 	current = cmd->heredoc_del;
// 	if (fd >= 0)
// 			close(fd);
// 	name = ft_strjoin(".heredoc_", ft_itoa(index, d), d);
// 	cmd->heredocfilename = ft_strdup(name, d);
// 	fd = open(cmd->heredocfilename, O_CREAT | O_RDWR, 0644);
// 	while(current)
// 	{
// 		if(fd < 0)
// 		{
// 			perror("open .heredoc file");
// 			return (1);
// 		}
		
// 		while(1)
// 		{
// 			d->line = readline(">");
//     		if (!d->line)
//         	{
// 				ft_putstr_fd("\n", 1);
// 				break;
// 			}
// 			if(ft_strcmp(current->s, d->line) == 0)
// 			{
// 				free(d->line);
// 				d->line = NULL;
// 				break;
// 			}
// 			if(current->expendable != 0)
// 			{
// 				exp = expand_heredoc(d->line, d);
// 				ft_putstr_fd(exp, fd);
// 				ft_putstr_fd("\n", fd);
// 				if (exp != d->line)
// 					free(exp);
// 			}
// 			else
// 			{
// 				ft_putstr_fd(d->line, fd);
// 				ft_putstr_fd("\n", fd);
// 			}
// 			free(d->line);
// 			d->line = NULL;
// 		}
// 		current = current->next;
// 	}
// 	if(fd >= 0)
// 		close(fd);
// 	return (0);
// }