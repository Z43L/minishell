/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free_close_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:47:47 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/23 14:53:00 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	pxb_close_pipes(t_pipex_bonus *pipex)
{
	int	i;

	i = 0;
	while (i < ((pipex->n_cmd - 1) * 2))
	{
		close(pipex->pipe[i]);
		i++;
	}
}

void	pxb_free_parent(t_pipex_bonus *pipex)
{
	free (pipex->pipe);
	ft_free(pipex->paths_array);
	free (pipex->pid);
}

void	pxb_freeparent_closefd(t_pipex_bonus *pipex)
{
	int	i;

	pxb_close_pipes(pipex);
	i = 0;
	while (i < pipex->n_cmd)
	{
		waitpid(pipex->pid[i], NULL, 0);
		i++;
	}
	close(pipex->in_fd);
	close(pipex->out_fd);
	pxb_free_parent(pipex);
	if (pipex->here_doc)
		unlink ("/tmp/.here_doc");
}
