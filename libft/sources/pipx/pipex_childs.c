/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:39:33 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/23 14:53:00 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*finds the path and the argv of the first command, 
then either executes the command if it exist or frees the memory
used previously if it dosen't. */
void	first_child(t_pipex *pipex, char **argv, char **envp)
{
	if (pipex->in_fd < 0)
	{
		if (access(argv[1], R_OK) == -1 && !access(argv[1], F_OK))
			px_error_msg(argv[1], NO_PERMS);
		else
			px_error_msg(argv[1], NO_FILE);
		return ;
	}
	if (dup2(pipex->fd_pipe[1], STDOUT_FILENO) == -1)
		px_error_exit(NULL, DUP_ERR);
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
		px_error_exit(NULL, DUP_ERR);
	pipex->cmd_argv = ft_split(argv[2], ' ');
	if (!pipex->cmd_argv)
		px_malloc_error();
	pipex->cmd_path = find_cmd_path(pipex->cmd_argv[0], pipex->paths_array);
	if (!pipex->cmd_path)
	{
		px_error_free(pipex, pipex->cmd_argv[0], CMD_NOT_FOUND);
		return ;
	}
	if (execve(pipex->cmd_path, pipex->cmd_argv, envp) == -1)
		px_error_free(pipex, pipex->cmd_argv[0], CMD_FAIL);
}

/*finds the path and the argv of the second command, 
then either executes the command if it exist or frees the memory
used previously if it dosen't.*/
void	second_child(t_pipex *pipex, char **argv, char **envp)
{
	if (pipex -> out_fd < 0)
	{
		if (access(argv[4], W_OK) == -1 && !access (argv[4], F_OK))
			px_error_msg(argv[4], NO_PERMS);
		else
			px_error_msg(argv[4], NO_MEMORY);
		return ;
	}
	if (dup2(pipex -> fd_pipe[0], STDIN_FILENO) == -1)
		px_error_exit(NULL, DUP_ERR);
	close(pipex -> fd_pipe[0]);
	close(pipex -> fd_pipe[1]);
	if (dup2(pipex -> out_fd, STDOUT_FILENO) == -1)
		px_error_exit(NULL, DUP_ERR);
	pipex -> cmd_argv = ft_split(argv[3], ' ');
	if (!pipex -> cmd_argv)
		px_malloc_error();
	pipex->cmd_path = find_cmd_path(pipex->cmd_argv[0], pipex->paths_array);
	if (!pipex -> cmd_path)
	{
		px_error_free(pipex, pipex -> cmd_argv[0], CMD_NOT_FOUND);
		return ;
	}
	if (execve(pipex -> cmd_path, pipex -> cmd_argv, envp) == -1)
		px_error_free(pipex, pipex -> cmd_argv[0], CMD_FAIL);
}
