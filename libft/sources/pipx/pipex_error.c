/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:38:48 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/23 14:53:00 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

//shows an error message
void	px_error_msg(char *param, int err)
{
	ft_putstr_fd("pipex: ", 2);
	if (err == CMD_NOT_FOUND)
		ft_putstr_fd("comand not found: ", 2);
	if (err == CMD_FAIL)
		ft_putstr_fd("comand failed: ", 2);
	if (err == NO_FILE)
		ft_putstr_fd("no such file a directory: ", 2);
	if (err == NO_PERMS)
		ft_putstr_fd("permission denied: ", 2);
	if (err == INV_ARGS)
		ft_putstr_fd(ERR_INPUT, 2);
	if (err == NO_MEMORY)
		ft_putstr_fd("no memory avaible", 2);
	if (err == DUP_ERR)
		ft_putstr_fd("could not dup fd", 2);
	if (err == PIPE_ERR)
		ft_putstr_fd("coul not create apipe", 2);
	if (err == FORK_ERR)
		ft_putstr_fd("could not fork process", 2);
	if (err == NO_PATH)
		ft_putstr_fd("PATH variable is not set", 2);
	if (param && (err == CMD_NOT_FOUND || err == CMD_FAIL || \
			err == NO_FILE || err == CMD_FAIL))
		ft_putstr_fd(param, 2);
	ft_putstr_fd ("\n", 2);
}

//shows an error message and free the memory allocated for a child process
void	px_error_free(t_pipex *pipex, char *param, int err)
{
	px_error_msg(param, err);
	if (err == CMD_FAIL || err == CMD_NOT_FOUND)
		free_child(pipex);
}

//finish all the process if an error occurs
void	px_error_exit(char *param, int err)
{
	px_error_msg(param, err);
	exit(err);
}

//shows an error message if malloc() fails
void	px_malloc_error(void)
{
	ft_putstr_fd("pipex: could not allocated memory", 2);
	exit(MALLOC_ERR);
}
