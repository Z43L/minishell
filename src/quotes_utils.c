/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:08:48 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/09/16 19:50:38 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*initialize_result(char *str, int *len, int *i, int *j)
{
	char	*result;

	*len = ft_strlen(str);
	result = malloc(*len + 1);
	if (!result)
		return (NULL);
	*i = 0;
	*j = 0;
	return (result);
}

void	process_quotes(char *str, char *result, int *i, int *j)
{
	char	quote_char;
	bool	in_quotes;

	quote_char = 0;
	in_quotes = false;
	while (str[*i])
	{
		if (!in_quotes && (str[*i] == '"' || str[*i] == '\''))
		{
			quote_char = str[*i];
			in_quotes = true;
			(*i)++;
		}
		else if (in_quotes && str[*i] == quote_char)
		{
			in_quotes = false;
			quote_char = 0;
			(*i)++;
		}
		else
			result[(*j)++] = str[(*i)++];
	}
}

char	*remove_quotes(char *str)
{
	int		len;
	int		i;
	int		j;
	char	*result;

	if (!str)
		return (NULL);
	if (has_unclosed_quotes(str))
		return (NULL);
	result = initialize_result(str, &len, &i, &j);
	if (!result)
		return (NULL);
	process_quotes(str, result, &i, &j);
	result[j] = '\0';
	return (result);
}
