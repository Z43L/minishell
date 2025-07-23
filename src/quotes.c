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
