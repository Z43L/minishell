/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:21:44 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/22 18:45:05 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	launch_pipe_processes(t_input *px, char **fullcomand, char **env)
{
	int	i;

	i = 0;
	while (i <= px->pipe_count)
	{
		px->pid[i] = fork();
		if (px->pid[i] == -1)
			return (perror("fork"), 1);
		if (px->pid[i] == 0)
		{
			if (i != 0)
				dup2(px->pipes[(i - 1) * 2], STDIN_FILENO);
			if (i != px->pipe_count)
				dup2(px->pipes[i * 2 + 1], STDOUT_FILENO);
			close_pipes(px->pipes, px->pipe_count);
			execute_command(fullcomand[i], env);
			exit(127);
		}
		i++;
	}
	return (0);
}

int	pipex(char **fullcomand, char **env, int countpipex)
{
	t_input	px;
	int		i;

	i = 0;
	px.pipe_count = countpipex;
	px.pipes = malloc(sizeof(int) * 2 * countpipex);
	if (!px.pipes)
		return (perror("malloc"), 1);
	if (create_pipes(px.pipes, countpipex) != 0)
		return (free(px.pipes), 1);
	px.pid = malloc(sizeof(pid_t) * (countpipex + 1));
	if (!px.pid)
		return (free(px.pipes), perror("malloc"), 1);
	if (launch_pipe_processes(&px, fullcomand, env) != 0)
		return (free(px.pipes), free(px.pid), 1);
	close_pipes(px.pipes, px.pipe_count);
	while (i <= px.pipe_count)
		waitpid(px.pid[i++], NULL, 0);
	free(px.pipes);
	free(px.pid);
	return (0);
}
