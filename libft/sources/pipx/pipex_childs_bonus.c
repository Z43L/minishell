/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_childs_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:48:06 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/23 14:53:00 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	pxb_first_child(t_pipex_bonus *pipex, char **argv, char **envp)
{
	if (pipex->in_fd < 0)
	{
		pxb_check_infile(pipex, argv);
		return ;
	}
	if (dup2(pipex->pipe[1], STDOUT_FILENO) == -1)
		px_error_exit(NULL, DUP_ERR);
	pxb_close_pipes(pipex);
	if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
		px_error_exit(NULL, DUP_ERR);
	if (pipex->here_doc)
		pipex->cmd_argv = ft_split(argv[3], ' ');
	else
		pipex->cmd_argv = ft_split(argv[2], ' ');
	if (!pipex->cmd_argv)
		px_malloc_error();
	pipex->cmd_path = find_cmd_path(pipex->cmd_argv[0], pipex->paths_array);
	if (!pipex->cmd_path)
	{
		pxb_cmd_not_found(pipex);
		return ;
	}
	if (execve(pipex->cmd_path, pipex->cmd_argv, envp) == -1)
		pxb_cmd_fail_exit(pipex);
}

void	pxb_last_child(t_pipex_bonus *pipex, char **argv, char **envp)
{
	if (pipex->out_fd < 0)
	{
		pxb_check_outfile(pipex, argv);
		return ;
	}
	if (dup2(pipex->pipe[(pipex->n_cmd - 2) * 2], STDIN_FILENO) == -1)
		px_error_exit(NULL, DUP_ERR);
	pxb_close_pipes(pipex);
	if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
		px_error_exit(NULL, DUP_ERR);
	if (pipex->here_doc)
		pipex->cmd_argv = ft_split(argv[4], ' ');
	else
		pipex->cmd_argv = ft_split(argv[pipex->n_cmd + 1], ' ');
	if (!pipex->cmd_argv)
		px_malloc_error();
	pipex->cmd_path = find_cmd_path(pipex->cmd_argv[0], pipex->paths_array);
	if (!pipex->cmd_path)
	{
		pxb_cmd_not_found(pipex);
		return ;
	}
	if (execve(pipex->cmd_path, pipex->cmd_argv, envp) == -1)
		pxb_cmd_fail_exit(pipex);
}

void	pxb_middle_child(t_pipex_bonus *pipex, char **argv, char **envp, int i)
{
	if (dup2(pipex->pipe[(i - 1) * 2], STDIN_FILENO) == -1)
		px_error_exit(NULL, DUP_ERR);
	if (dup2(pipex->pipe[(i + 1) * 2 - 1], STDOUT_FILENO) == -1)
		px_error_exit(NULL, DUP_ERR);
	pxb_close_pipes(pipex);
	pipex->cmd_argv = ft_split(argv[i + 2], ' ');
	if (!pipex->cmd_argv)
		px_malloc_error();
	pipex->cmd_path = find_cmd_path(pipex->cmd_argv[0], pipex->paths_array);
	if (!pipex->cmd_path)
	{
		pxb_cmd_not_found(pipex);
		return ;
	}
	if (execve(pipex->cmd_path, pipex->cmd_argv, envp) == -1)
		pxb_cmd_fail_exit(pipex);
}

void	pxb_select_child(t_pipex_bonus *pipex, char **argv, char **envp, int i)
{
	if (i == 0)
		pxb_first_child(pipex, argv, envp);
	else if (i + 1 == pipex->n_cmd)
		pxb_last_child(pipex, argv, envp);
	else
		pxb_middle_child(pipex, argv, envp, i);
}
