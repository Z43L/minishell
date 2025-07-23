/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainpipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:51:35 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/23 14:53:00 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	pxb_create_pipes(t_pipex_bonus *pipex)
{
	int	i;

	pipex->pipe = (int *)malloc((pipex->n_cmd - 1) * 2 * sizeof(int));
	if (!pipex->pipe)
	{
		perror("Error al asignar memoria para pipes");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < (pipex->n_cmd - 1))
	{
		if (pipe(pipex->pipe + 2 * i) == -1)
		{
			free(pipex->pipe);
			perror("Error al crear pipes");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	pxb_init_pipex(t_pipex_bonus *pipex, char **envp)
{
	pipex->paths_array = px_split_path(envp);
	if (!pipex->paths_array)
	{
		perror("Error al inicializar paths");
		exit(EXIT_FAILURE);
	}
	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * pipex->n_cmd);
	if (!pipex->pid)
	{
		perror("Error al asignar memoria para pids");
		exit(EXIT_FAILURE);
	}
	pxb_create_pipes(pipex);
}

static void	pxb_handle_child(t_pipex_bonus *pipex, char **commands, char **env)
{
	int	i;

	i = 0;
	while (i < pipex->n_cmd)
	{
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
		{
			perror("fork");
			pxb_free_parent(pipex);
			exit(EXIT_FAILURE);
		}
		if (pipex->pid[i] == 0)
		{
			if (i > 0)
				dup2(pipex->pipe[(i - 1) * 2], STDIN_FILENO);
			if (i < pipex->n_cmd - 1)
				dup2(pipex->pipe[i * 2 + 1], STDOUT_FILENO);
			pxb_select_child(pipex, commands, env, i);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

void	mainpipex(int count, char **commands, char **env)
{
	t_pipex_bonus	pipex;
	int				i;

	ft_memset(&pipex, 0, sizeof(t_pipex_bonus));
	pipex.n_cmd = count;
	pxb_init_pipex(&pipex, env);
	pxb_handle_child(&pipex, commands, env);
	i = -1;
	while (++i < pipex.n_cmd)
		waitpid(pipex.pid[i], NULL, 0);
	pxb_freeparent_closefd(&pipex);
}
