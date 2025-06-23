/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_funs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:24:39 by ielouarr          #+#    #+#             */
/*   Updated: 2025/06/23 18:18:47 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

int	execute_external_cmd (t_env **env, t_cmd *cmd, t_data *d)
{
	char	**paths;
	char	*path;
	char	**envs;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	paths = get_path(*env, d);
	if (!paths)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		return (127);
	}
	path = right_path(paths, cmd, d);
	if (!path)
		return (127);
	envs = get_env(*env, d);
	if (execve(path, cmd->args, envs) == -1)
	{
		perror("execve");
		return (1);
	}
	return (0);
}

int	execute_single_cmd(t_cmd *cmd, t_env **env, t_data *d,
				int input_fd, int output_fd)
{
	if (apply_heredoc_redirection(cmd) != 0)
		return (1);
	if (cmd->heredoc == 0 && setup_redirections(input_fd, output_fd) != 0)
		return (1);
	if(cmd->files && apply_redirections(cmd->files) != 0)
		return (1);
	if (is_builtin(cmd->cmd) == 0)
		return (execute_builtin(cmd->cmd, env, cmd->args, d));
	else
		return (execute_external_cmd(env, cmd, d));
}

int	execute_single_builtin(t_cmd *cmds, t_env **env, t_data *d)
{
	int	saved_stdin;
	int	saved_stdout;
	int	result;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
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
	result = execute_builtin(cmds->cmd, env, cmds->args, d);
	duping(saved_stdin, saved_stdout);
	return (result);
}

int	execute_single_external(t_cmd *cmds, t_env **env, t_data *d)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exit(execute_single_cmd(cmds, env, d, STDIN_FILENO, STDOUT_FILENO));
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	else
	{
		perror("fork");
		return (1);
	}
}

int	execute_pipeline(t_env **env, t_cmd *cmds, t_data *d)
{
	int	cmd_count;

	if (!cmds)
		return (0);
	if (process_heredocs_before_fork(cmds, d) != 0)
        return (1);
	if (!has_pipeline(cmds))
	{
		if (is_builtin(cmds->cmd) == 0)
			return (execute_single_builtin(cmds, env, d));
		else
			return (execute_single_external(cmds, env, d));
	}
	cmd_count = count_commands(cmds);
	return (execute_pipeline_commands(env, cmds, d, cmd_count));
}
