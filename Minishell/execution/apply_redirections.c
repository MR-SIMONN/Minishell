/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:46:33 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/22 17:57:46 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int setup_redirections(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			return (1);
		}
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			return (1);
		}
		close(output_fd);
	}
	return (0);
}



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

int	apply_redirections (t_str *files)
{
	while (files)
	{
		if(files->type == APPEND_FILE && apply_output_redirection(files) != 0)
			return(1);
		if(files->type == OUT_FILE && apply_output_redirection(files) != 0)
			return(1);
		if(files->type == IN_FILE && apply_input_redirection(files) != 0)
			return(1);
		files=files->next;
	}
	return(0);
}

int process_heredocs_before_fork(t_cmd *cmds, t_data *d)
{
    t_cmd *current = cmds;
    
    while (current)
    {
        if (current->heredoc && current->heredoc_del != NULL)
        {
            if (apply_herdoc(current->heredoc_del, d) != 0)
                return (1);
        }
        current = current->next;
    }
    return (0);
}

int	apply_heredoc_redirection(t_cmd *cmd)
{
	int	fd;

	if (cmd->heredoc && cmd->heredoc_del != NULL)
	{
		fd = open(".heredoc", O_RDONLY);
		if (fd == -1)
		{
			perror(".heredoc");
			return (1);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc");
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}

int apply_herdoc(t_str *heredocs, t_data *d)
{
	t_str *current;
	int fd = -1;
	char *exp;

	current = heredocs;
	unlink(".heredoc");
	while(current)
	{
		if (fd >= 0)
			close(fd);
		fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if(fd < 0)
		{
			if (fd >= 0)
				close(fd);
			return (1);
		}
		
		while(1)
		{
			d->line = readline(">");
    		if (!d->line)
        	{
				ft_putstr_fd("\n", 1);
				break;
			}
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
		current = current->next;
	}
	return (0);
}

// void signal_herdoc(int sig)
// {
//     (void)sig;
//     printf("\n");
//     exit(130);
// }

// int apply_herdoc(t_str *heredocs, t_data *d)
// {
//     t_str *current;
//     int fd = -1;
//     char *exp;
    
//     current = heredocs;
//     unlink(".heredoc");
    
//     while(current)
//     {
//         if (fd >= 0)
//             close(fd);
//         void (*original_sigint)(int) = signal(SIGINT, SIG_IGN);
        
//         int pid = fork();
//         int status;
        
//         if(pid == 0)
//         {
//             signal(SIGINT, signal_herdoc);
            
//             fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
//             if(fd < 0)
//             {
//                 perror("open .heredoc");
//                 exit(1);
//             }

//             while(1)
//             {
//                 d->line = readline(">");
//                 if (!d->line)
//                     break;
//                 if(ft_strcmp(current->s, d->line) == 0)
//                 {
//                     free(d->line);
//                     d->line = NULL;
//                     break;
//                 }
//                 if(current->expendable != 0)
//                 {
//                     exp = expand_heredoc(d->line, d);
//                     ft_putstr_fd(exp, fd);
//                     ft_putstr_fd("\n", fd);
//                     if (exp != d->line)
//                         free(exp);
//                 }
//                 else
//                 {
//                     ft_putstr_fd(d->line, fd);
//                     ft_putstr_fd("\n", fd);
//                 }
//                 free(d->line);
//                 d->line = NULL;
//             }
//             close(fd);
//             exit(0);
//         }
//         else if (pid > 0)
//         {
//             waitpid(pid, &status, 0);
//             signal(SIGINT, original_sigint);
//             if(WIFEXITED(status) && WEXITSTATUS(status) == 130)
//             {
//                 return (130);
//             }
//             else if(WIFSIGNALED(status))
//             {
//                 return (130);
//             }
//         }
//         else
//         {
//             perror("fork");
//             return (1);
//         }
        
//         current = current->next;
//     }
    
//     return (0);
// }