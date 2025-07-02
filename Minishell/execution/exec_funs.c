/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:24:39 by ielouarr          #+#    #+#             */
/*   Updated: 2025/07/02 03:49:05 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	execute_external_cmd(t_cmd *cmd, t_data *d)
{
	char	**paths;
	char	*path;
	char	**envs;
	int		status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	status = 0;
	paths = get_path(d);
	path = right_path(paths, cmd, d, &status);
	if (!path)
		return (status);
	envs = get_env(d);
	if (!envs)
	{
		ft_putstr_fd("minishell: failed to get environment\n", 2);
		return (1);
	}
	if (execve(path, cmd->args, envs) == -1)
	{
		perror("execve");
		return (126);
	}
	return (status);
}

int	execute_single_cmd(t_cmd *cmd, t_data *d, t_fds fds)
{
	if (handling_heredocs(cmd, fds.input_fd, fds.output_fd) != 0)
		return (1);
	if (apply_heredoc_redirection(cmd) != 0)
		return (1);
	if (cmd->files && apply_redirections(cmd->files) != 0)
		return (1);
	if (is_builtin(cmd->cmd) == 0)
		return (execute_builtin(cmd->cmd, cmd->args, d));
	return (execute_external_cmd(cmd, d));
}

int	execute_single_builtin(t_cmd *cmds, t_data *d)
{
	int	saved_stdin;
	int	saved_stdout;
	int	result;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		perror("dup");
		return (1);
	}
	if (apply_heredoc_redirection(cmds) != 0)
	{
		duping(saved_stdin, saved_stdout);
		return (1);
	}
	if (cmds->files && apply_redirections(cmds->files) != 0)
	{
		duping(saved_stdin, saved_stdout);
		return (1);
	}
	result = execute_builtin(cmds->cmd, cmds->args, d);
	duping(saved_stdin, saved_stdout);
	return (result);
}

int	execute_single_external(t_cmd *cmds, t_data *d)
{
	pid_t	pid;
	t_fds	fds;
	int		status;

	fds.input_fd = STDIN_FILENO;
	fds.output_fd = STDOUT_FILENO;
	pid = fork();
	if (pid == 0)
		exit(execute_single_cmd(cmds, d, fds));
	else if (pid > 0)
	{
		signal(SIGINT,SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT,handle_sigint);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    		exit_status(1, 130);
		else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
    		exit_status(1, 131);
		return (WEXITSTATUS(status));
	}
	perror("fork");
	return (1);
}

int	execute_pipeline(t_data *d)
{
	int	cmd_count;
	int	execute;

	if (!d->cmds)
		return (0);
	if (process_heredocs_before_fork(d) != 0)
		return (1);
	if (!has_pipeline(d->cmds))
		return (ft_has_no_pipe(d));
	cmd_count = count_commands(d->cmds);
	execute = execute_pipeline_commands(d, cmd_count);
	if (execute != 0)
		exit_status(1, execute);
	unlink_all_heredocfiles(d->cmds);
	return (execute);
}
