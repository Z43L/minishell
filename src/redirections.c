/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:27:23 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/09/17 15:28:54 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_redirections(t_shell *mini_sh, t_token *node, t_cmd *cmd)
{
	while (node && node -> type != OP_PIPE)
	{
		open_outfile(node, cmd);
		open_infile(node, cmd);
		if (cmd -> in_fd < 0 || cmd -> out_fd < 0)
			return (perror(node -> next -> content), 1);
		if (node -> type == REDIR_HD)
			open_here_doc_file(mini_sh, cmd);
		if (cmd -> in_fd < 0)
			return (1);
		node = node -> next;
	}
	return (0);
}

void	open_outfile(t_token *node, t_cmd *cmd)
{
	if (node -> type == REDIR_APP || node -> type == REDIR_OUT)
	{
		my_close(&(cmd->out_fd));
		if (node->type == REDIR_OUT)
			cmd->out_fd = open(node->next->content,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			cmd->out_fd = open(node->next->content,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
}

void	open_infile(t_token *node, t_cmd *cmd)
{
	if (node -> type == REDIR_IN)
	{
		my_close(&(cmd -> in_fd));
		if (node -> type == REDIR_IN)
			cmd -> in_fd = open(node -> next -> content, O_RDONLY);
	}
}

void	open_here_doc_file(t_shell *mini_sh, t_cmd *cmd)
{
	char	*file;
	char	*num;

	my_close(&(cmd -> in_fd));
	num = ft_itoa(mini_sh -> input -> hd_count++);
	file = ft_strjoin("hd_mini_sh", num);
	cmd -> in_fd = open(file, O_RDONLY);
	if (cmd -> in_fd >= 0)
		unlink(file);
	my_free((void **)&num);
	my_free((void **)&file);
	if (cmd -> in_fd < 0)
		perror("error opening heredoc file");
}
