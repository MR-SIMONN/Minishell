/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:46:33 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/25 16:20:00 by moel-hai         ###   ########.fr       */
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

void signal_herdoc(int sig)
{
    (void)sig;
	exit_status(1, 1);
	printf ("\n");
    exit(130);
}
int apply_herdoc(t_str *heredocs, t_data *d)
{
	struct termios  tty;
    t_str *current;
    int fd = 0;
    int status ;
    char *exp;
    current = heredocs;
    unlink(".heredoc");
    while(current)
    {
        int pid = fork();
		if(pid == 0)
        {
            signal(SIGINT,signal_herdoc);
            fd = open(".heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
            if(fd < 0)
                exit (1);
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
                	exp = expand_heredoc(d->line, d);
            	else
                	exp = d->line;
            	ft_putstr_fd(exp, fd);
            	ft_putstr_fd("\n", fd);
            	store_addr(d->line, d);
        	}
        	close (fd);
        	exit(0);
        }
        else
        {
			signal(SIGINT,SIG_IGN);
            waitpid(pid,&status,0);
            signal(SIGINT,handle_sigint);
			tcgetattr(STDIN_FILENO, &tty);
            tty.c_lflag |= ECHO;
            tcsetattr(STDIN_FILENO, TCSANOW, &tty);
            if(WIFEXITED(status) == 1 && WEXITSTATUS(status) == 130)
                return (exit_status(1, 1), 130);
        }
        current = current->next;
    }
    return (0);
}
