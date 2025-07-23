/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_check_files_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:48:00 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/23 14:53:00 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	pxb_check_infile(t_pipex_bonus *pipex, char **argv)
{
	if (pipex -> here_doc)
		pxb_error_msg(ERR_HEREDOC, NULL);
	else
	{
		if (access(argv[1], R_OK) == -1 && !access(argv[1], F_OK))
			px_error_msg(argv[1], NO_PERMS);
		else
			px_error_msg(argv[1], NO_FILE);
	}
}

void	pxb_check_outfile(t_pipex_bonus *pipex, char **argv)
{
	if (pipex->here_doc)
	{
		if (access(argv[5], W_OK) == -1 && !access(argv[5], F_OK))
			px_error_msg(argv[5], NO_PERMS);
		else
			px_error_msg(argv[5], NO_MEMORY);
		return ;
	}
	else
	{
		if (access(argv[pipex->n_cmd + 2], W_OK) == -1
			&& !access(argv[pipex->n_cmd + 2], F_OK))
			px_error_msg(argv[pipex->n_cmd + 2], NO_PERMS);
		else
			px_error_msg(argv[pipex->n_cmd + 2], NO_MEMORY);
		return ;
	}
}
