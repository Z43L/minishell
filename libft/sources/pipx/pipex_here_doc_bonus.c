/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:47:37 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/23 14:53:00 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static void	pxb_here_doc_read(t_pipex_bonus *pipex, char *limiter)
{
	char	*line;

	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			ft_putchar_fd('\n', 2);
			pxb_perror_exit(ERR_HEREDOC_EOF, limiter);
		}
		if (!ft_strncmp(line, limiter, ft_strlen(line) - 1))
		{
			free(line);
			return ;
		}
		write(pipex->in_fd, line, ft_strlen(line));
		free(line);
	}
}

void	pxb_here_doc(t_pipex_bonus *pipex, char **argv)
{
	char	*limiter;

	pipex->in_fd = open("/tmp/.here_doc", O_CREAT | 01 | O_TRUNC, 0000644);
	if (pipex->in_fd < 0)
		pxb_perror_exit(ERR_HEREDOC, NULL);
	pipex->here_doc = true;
	limiter = argv[2];
	pxb_here_doc_read(pipex, limiter);
	close(pipex->in_fd);
}
