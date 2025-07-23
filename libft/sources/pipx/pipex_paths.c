/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:55:07 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/23 14:53:00 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

//This functions receives the array envp until finds the one that starts with:
//"PATH=" then returns the pointer to the paths. Returns a string of paths
static char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

//return an arrays of PATHS
char	**px_split_path(char **envp)
{
	char	*full_path;
	char	**new_path;

	full_path = find_path(envp);
	if (!full_path)
		px_error_exit(NULL, NO_PATH);
	new_path = ft_split(full_path, ':');
	if (!new_path)
		px_malloc_error();
	return (new_path);
}

//Test all the paths in the paths_array and plus the character `/`to chek if 
//the cmd executable file is in any of them
char	*find_cmd_path(char *cmd, char **paths_array)
{
	char	*tmp;
	char	*cmd_path;

	while (*paths_array)
	{
		tmp = ft_strjoin(*paths_array, "/");
		if (!tmp)
			px_malloc_error();
		cmd_path = ft_strjoin(tmp, cmd);
		if (!cmd_path)
			px_malloc_error();
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		paths_array++;
	}
	return (NULL);
}
