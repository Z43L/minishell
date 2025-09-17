/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:10:29 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/09/17 14:22:39 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_pipes(int *pipes, int countpipex)
{
	int	n;

	n = 0;
	while (n < countpipex)
	{
		if (pipe(&pipes[n * 2]) == -1)
		{
			perror("pipe failed");
			return (1);
		}
		n++;
	}
	return (0);
}

void	close_pipes(int *pipes, int countpipex)
{
	int	j;

	j = 0;
	while (j < countpipex)
	{
		close(pipes[j * 2]);
		close(pipes[j * 2 + 1]);
		j++;
	}
}

void	setup_pipes(int n, int countpipex, int *pipes)
{
	if (n == 0)
	{
		if (countpipex > 0)
			dup2(pipes[1], STDOUT_FILENO);
	}
	else if (n == countpipex)
		dup2(pipes[(n - 1) * 2], STDIN_FILENO);
	else
	{
		dup2(pipes[(n - 1) * 2], STDIN_FILENO);
		dup2(pipes[n * 2 + 1], STDOUT_FILENO);
	}
}

void	execute_command(char *command, char **env)
{
	char	**args;
	char	*cmd_path;

	args = ft_split(command, ' ');
	if (!args)
	{
		perror("ft_split failed");
		exit(127);
	}
	cmd_path = comand_path(args[0]);
	if (cmd_path)
	{
		execve(cmd_path, args, env);
		free(cmd_path);
	}
	else
		execve(args[0], args, env);
	free_split(args);
	perror("execve failed");
	exit(127);
}
