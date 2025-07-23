/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_msg_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:47:55 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/23 14:53:00 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	pxb_error_msg(int err, char *param)
{
	ft_putstr_fd("pipex: ", 2);
	if (err == INV_ARGS)
	{
		ft_putstr_fd("invalid arguments, use: ", 2);
		ft_putstr_fd("./pipex infile cmd1 cmd2 ... cmdn outfile or ", 2);
		ft_putstr_fd("./pipex here\\_doc LIMITER cmd1 cmd2 outfile\n", 2);
	}
	else if (err == ERR_HEREDOC)
		ft_putstr_fd("error opening here_doc\n", 2);
	else if (err == ERR_RDHEREDOC)
		ft_putstr_fd("error reading from here_doc\n", 2);
	else if (err == ERR_HEREDOC_EOF)
		ft_putstr_fd("here_doc terminated with end-of-file, expected ", 2);
	if (err == ERR_HEREDOC_EOF)
	{
		ft_putstr_fd(param, 2);
		ft_putchar_fd('\n', 2);
	}
}

void	pxb_perror_exit(int err, char *param)
{
	pxb_error_msg(err, param);
	exit (err);
}

void	pxb_cmd_not_found(t_pipex_bonus *pipex)
{
	px_error_msg(pipex->cmd_argv[0], CMD_NOT_FOUND);
	ft_free(pipex->cmd_argv);
}

void	pxb_cmd_fail_exit(t_pipex_bonus *pipex)
{
	px_error_msg(pipex->cmd_argv[0], CMD_FAIL);
	free(pipex->cmd_path);
	ft_free(pipex->cmd_argv);
	exit (CMD_FAIL);
}
