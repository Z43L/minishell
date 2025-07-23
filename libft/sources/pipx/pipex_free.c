/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:49:48 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/23 14:53:00 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

//frees an arrays and point it to NULL
void	ft_free(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

//frees memory allocated for a child process
void	free_child(t_pipex *pipex)
{
	ft_free(pipex -> cmd_argv);
	if (pipex -> cmd_path)
		free(pipex);
}

//close all files descriptors
//wait for the child process finish and frees arrays
void	free_father_fd(t_pipex	*pipex)
{
	close(pipex -> fd_pipe[0]);
	close(pipex -> fd_pipe[1]);
	waitpid(pipex -> pid1, NULL, 0);
	waitpid(pipex -> pid2, NULL, 0);
	close(pipex -> in_fd);
	close(pipex -> out_fd);
	ft_free(pipex -> paths_array);
}
