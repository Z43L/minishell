/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:17:12 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/09/17 15:54:30 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_logic(t_shell *shell, const char *line, char **env, int pipes)
{
	if (pipes > 0)
		pipex((char **) &line, env, pipes);
	else
	{
		shell->cmd->cmd_argv = shell->argumentos;
		shell->cmd->cmd_path = shell->path[0];
		execute_cmds(env, shell->argumentos, shell->path[0]);
	}
}

void	add_token_to_list(t_token **list, t_token *new_token)
{
	t_token	*current;

	if (!*list)
	{
		*list = new_token;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

int	create_heredoc_file(const char *limiter)
{
	char	*line;
	int		tmp_fd;

	tmp_fd = open("/tmp/minishell_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd < 0)
	{
		perror("heredoc file");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
	close(tmp_fd);
	return (tmp_fd);
}

int	update_heredoc_token(t_token *redir_node)
{
	redir_node->type = REDIR_IN;
	free(redir_node->next->content);
	redir_node->next->content = ft_strdup("/tmp/minishell_heredoc");
	if (!redir_node->next->content)
		return (STATUS_ERROR);
	redir_node->next->type = FILE_PATH;
	return (STATUS_OK);
}

int	handle_heredoc(t_token *redir_node)
{
	int	tmp_fd;

	if (!redir_node->next || redir_node->next->type != LIMITER)
		return (STATUS_ERROR);
	tmp_fd = create_heredoc_file(redir_node->next->content);
	if (tmp_fd < 0)
		return (STATUS_ERROR);
	return (update_heredoc_token(redir_node));
}
