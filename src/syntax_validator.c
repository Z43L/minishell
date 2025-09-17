/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmoren <davmoren@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:51:24 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/08/18 16:50:10 by davmoren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_redirection(t_type type)
{
	return (type == REDIR_OUT || type == REDIR_IN || type == REDIR_APP
		|| type == REDIR_HD);
}

static int	validate_redirection(t_token *current)
{
	if (current->type == REDIR_HD)
	{
		if (!current->next || current->next->type != LIMITER)
		{
			ft_puterr("syntax error near unexpected token `newline'");
			return (0);
		}
	}
	else if (!current->next || current->next->type != FILE_PATH)
	{
		ft_puterr("syntax error near unexpected token `newline'");
		return (0);
	}
	return (1);
}

static int	validate_pipe(t_token *current)
{
	if (!current->next || current->next->type == OP_PIPE)
	{
		ft_puterr("syntax error near unexpected token `|'");
		return (0);
	}
	return (1);
}

int	validate_token_sequence(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current && current->type == OP_PIPE)
	{
		ft_puterr("syntax error near unexpected token `|'");
		return (0);
	}
	while (current)
	{
		if (is_redirection(current->type) && !validate_redirection(current))
			return (0);
		if (current->type == OP_PIPE && !validate_pipe(current))
			return (0);
		current = current->next;
	}
	return (1);
}
