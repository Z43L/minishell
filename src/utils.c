/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:06:36 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/09/17 14:24:26 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	split_len(char **input)
{
	size_t	i;

	i = 0;
	while (input[i])
		i ++;
	return (i);
}

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**split_cpy(char **input)
{
	char	**new;
	size_t	i;

	if (!input)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (split_len(input) + 1));
	i = -1;
	while (input[++i])
		new[i] = ft_strdup(input[i]);
	return (new);
}

void	my_perr(const char *msg, bool should_exit, int exit_code)
{
	perror(msg);
	if (should_exit)
		exit(exit_code);
}
