/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:11:10 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/23 15:02:58 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_command_path(char **split_path, char *word)
{
	char	*temp_path;
	char	*full_command;
	int		i;

	i = 0;
	while (split_path[i])
	{
		temp_path = ft_strjoin(split_path[i], "/");
		if (!temp_path)
			return (0);
		full_command = ft_strjoin(temp_path, word);
		free(temp_path);
		if (full_command && access(full_command, X_OK) == 0)
		{
			free(full_command);
			return (1);
		}
		free(full_command);
		i++;
	}
	return (0);
}

int	is_command(char *word)
{
	char	*path_env;
	char	**split_path;
	int		result;

	path_env = getenv("PATH");
	if (!path_env || !word)
		return (0);
	split_path = ft_split(path_env, ':');
	if (!split_path)
		return (0);
	result = check_command_path(split_path, word);
	free_split(split_path);
	return (result);
}

static char	*search_path_split(char **split_path, char *word)
{
	char	*temp_path;
	char	*full_command;
	int		i;

	i = 0;
	while (split_path[i])
	{
		temp_path = ft_strjoin(split_path[i], "/");
		if (!temp_path)
			return (NULL);
		full_command = ft_strjoin(temp_path, word);
		free(temp_path);
		if (full_command && access(full_command, X_OK) == 0)
		{
			free_split(split_path);
			return (full_command);
		}
		free(full_command);
		i++;
	}
	return (NULL);
}

char	*comand_path(char *word)
{
	char	*path_env;
	char	**split_path;

	if (!word)
		return (NULL);
	if (word[0] == '/' || word[0] == '.')
	{
		if (access(word, X_OK) == 0)
			return (ft_strdup(word));
		else
			return (NULL);
	}
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	split_path = ft_split(path_env, ':');
	if (!split_path)
		return (NULL);
	return (search_path_split(split_path, word));
}
