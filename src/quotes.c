/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:35:13 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/18 16:02:08 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	qoutes_total(char **av, int index, t_token *token)
{
	while (av[index + 1] != NULL)
	{
		if (ft_strchr(av[index + 1], '"') != NULL)
		{
			token->had_quotes = false;
			break ;
		}
		index++;
	}
	if (token->had_quotes == true)
		return (1);
	return (0);
}

int	quotes(char *str, t_cmd *cmd, t_token *token, char **av)
{
	int	index;

	(void)cmd;
	(void)str;
	index = token->index;
	token->type = D_QUOTES;
	token->had_quotes = true;
	return (qoutes_total(av, index, token));
}

bool	has_unclosed_quotes(const char *str)
{
	bool	in_quotes;
	char	q;

	in_quotes = false;
	q = 0;
	if (!str)
		return (false);
	while (*str)
	{
		if (!in_quotes && (*str == '"' || *str == '\''))
		{
			q = *str;
			in_quotes = true;
		}
		else if (in_quotes && *str == q)
		{
			in_quotes = false;
			q = 0;
		}
		str++;
	}
	return (in_quotes);
}

int	contains_unclosed_quotes(t_token *t)
{
	while (t && t->type != OP_PIPE)
	{
		if (t->type == COMMAND || t->type == WORD || t->type == CMD_ARG)
		{
			if (has_unclosed_quotes(t->content))
				return (1);
		}
		t = t->next;
	}
	return (0);
}
