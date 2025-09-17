/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:59:23 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/09/17 15:54:16 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	preprocess_heredocs(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	while (current)
	{
		if (current->type == REDIR_HD)
			if (handle_heredoc(current) != STATUS_OK)
				return (STATUS_ERROR);
		current = current->next;
	}
	return (STATUS_OK);
}

int	validate_and_preprocess_tokens(t_shell *shell)
{
	if (!shell->input->token_lst)
		return (STATUS_OK);
	perform_expansion(shell->input->token_lst, shell);
	if (preprocess_heredocs(shell->input->token_lst) != STATUS_OK)
	{
		free_token_list(shell->input->token_lst);
		shell->input->token_lst = NULL;
		return (STATUS_ERROR);
	}
	if (validate_token_sequence(shell->input->token_lst) != 1)
	{
		ft_puterr("Syntax error");
		shell->exit_code = 2;
		free_token_list(shell->input->token_lst);
		shell->input->token_lst = NULL;
		return (STATUS_ERROR);
	}
	return (STATUS_OK);
}

void	execute_tokens(t_shell *shell)
{
	int		pipe_count;
	t_token	*current;

	pipe_count = 0;
	current = shell->input->token_lst;
	while (current)
	{
		if (current->type == OP_PIPE)
			pipe_count++;
		current = current->next;
	}
	execution_dispatcher(shell, shell->input->token_lst, pipe_count);
}

int	process_input_line(t_shell *shell, char *line)
{
	if (!line || !*line)
		return (STATUS_OK);
	if (lexer(line, shell) == -1)
		return (STATUS_ERROR);
	if (validate_and_preprocess_tokens(shell) != STATUS_OK)
		return (STATUS_ERROR);
	execute_tokens(shell);
	free_token_list(shell->input->token_lst);
	shell->input->token_lst = NULL;
	return (STATUS_OK);
}
