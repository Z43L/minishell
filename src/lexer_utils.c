/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:11:03 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/22 20:12:44 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_type	get_previous_token_type(t_token *token_list)
{
	t_token	*current;

	current = token_list;
	if (!current)
		return (WORD);
	while (current->next)
		current = current->next;
	return (current->type);
}

int	handle_output_redirections(t_token *token, char *av)
{
	if (ft_strcmp(av, ">>") == 0)
	{
		token->type = REDIR_APP;
		return (0);
	}
	if (ft_strcmp(av, ">") == 0)
	{
		token->type = REDIR_OUT;
		return (0);
	}
	else if (av[0] == '>')
	{
		ft_puterr("minishell: syntax error near unexpected token `");
		ft_puterr(av);
		ft_puterr("'\n");
		return (-1);
	}
	return (1);
}

int	handle_input_redirections(t_token *token, char *av)
{
	if (ft_strcmp(av, "<<") == 0)
	{
		token->type = REDIR_HD;
		return (0);
	}
	if (ft_strcmp(av, "<") == 0)
	{
		token->type = REDIR_IN;
		return (0);
	}
	else if (av[0] == '<')
	{
		ft_puterr("minishell: syntax error near unexpected token `");
		ft_puterr(av);
		ft_puterr("'\n");
		return (-1);
	}
	return (1);
}

int	lexer_redirections(t_token *token, char *av)
{
	int	result;

	result = handle_output_redirections(token, av);
	if (result != 1)
		return (result);
	return (handle_input_redirections(token, av));
}

int	handle_pipe_and_limiter(t_token *token, char *av, t_token *token_list)
{
	t_type	prev_type;

	if (ft_strcmp(av, "|") == 0)
	{
		token->type = OP_PIPE;
		return (0);
	}
	prev_type = get_previous_token_type(token_list);
	if (prev_type == REDIR_HD)
	{
		token->type = LIMITER;
		return (0);
	}
	if (prev_type == REDIR_OUT || prev_type == REDIR_IN
		|| prev_type == REDIR_APP)
	{
		token->type = FILE_PATH;
		return (0);
	}
	return (1);
}
