/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 01:44:05 by davmoren          #+#    #+#             */
/*   Updated: 2025/09/17 14:08:18 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_piped_segment(t_shell *shell, t_token *segment_start, int in_fd, int out_fd, int *pipes, int pipe_count)
{
	t_cmd	cmd;

	ft_memset(&cmd, 0, sizeof(t_cmd));
	cmd.in_fd = in_fd;
	cmd.out_fd = out_fd;
	cmd.cmd_argv = argv_node_print(segment_start);
	if (!cmd.cmd_argv[0])
	{
		clear_cmd(&cmd);
		exit(0);
	}
	cmd.cmd_path = comand_path(cmd.cmd_argv[0]);
	if (!cmd.cmd_path)
	{
		handle_cmd_not_found(&cmd, shell);
		clear_cmd(&cmd);
		exit(127); 
	}
	cmd.env = env_to_array(shell->env);
	if (handle_redirections(shell, segment_start, &cmd) != 0)
	{
		clear_cmd(&cmd);
		exit(1);
	}
	dup2(cmd.in_fd, STDIN_FILENO);
	dup2(cmd.out_fd, STDOUT_FILENO);
	if (cmd.in_fd != STDIN_FILENO)
		close(cmd.in_fd);
	if (cmd.out_fd != STDOUT_FILENO)
		close(cmd.out_fd);
	int j = 0;
	while (j < pipe_count * 2)
	{
		close(pipes[j]);
		j++;
	}
	execve(cmd.cmd_path, cmd.cmd_argv, cmd.env);
	my_perr("execve", true, 127);
}

void	exec_pipe_loop(t_shell *shell, int *pipes, pid_t *pids, int pipe_count, t_token *tokens)
{
	int		i;
	t_token	*current;
	t_token	*segment_start;
	int		status;
	int		j;
	int		in_fd;
	int		out_fd;

	i = 0;
	current = tokens;
	while (i <= pipe_count)
	{
		segment_start = current;
		while (current && current->type != OP_PIPE)
			current = current->next;
		pids[i] = fork();
		if (pids[i] == -1)
			my_perr("fork", true, 1);
		if (pids[i] == 0)
		{
			j = 0;
			while (j < pipe_count * 2)
			{
				close(pipes[j]);
				j++;
			}
			in_fd = STDIN_FILENO;
			if (i > 0)
				in_fd = pipes[(i - 1) * 2];
			out_fd = STDOUT_FILENO;
			if (i < pipe_count)
				out_fd = pipes[i * 2 + 1];
			execute_piped_segment(shell, segment_start, in_fd, out_fd, pipes, pipe_count);
		}
		if (current && current->type == OP_PIPE)
			current = current->next;
		i++;
	}
	j = 0;
	while (j < pipe_count * 2)
	{
		close(pipes[j]);
		j++;
	}
	j = 0;
	while (j <= pipe_count)
	{
		waitpid(pids[j], &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		j++;
	}
}

void	exec_pipe(t_shell *shell, t_token *tokens, int pipe_count)
{
	int		*pipes;
	pid_t	*pids;
	int		j;

	pipes = malloc(sizeof(int) * pipe_count * 2);
	pids = malloc(sizeof(pid_t) * (pipe_count + 1));
	if (!pipes || !pids)
		my_perr("malloc", true, 1);
	j = 0;
	while (j < pipe_count)
	{
		if (pipe(pipes + j * 2) == -1)
			my_perr("pipe", true, 1);
		j++;
	}
	exec_pipe_loop(shell, pipes, pids, pipe_count, tokens);
	free(pipes);
	free(pids);
}

int	has_command(t_token *tokens)
{
	while (tokens && tokens->type != OP_PIPE)
	{
		if (tokens->type == COMMAND)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
