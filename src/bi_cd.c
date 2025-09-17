/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmoren <davmoren@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:24:32 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/08/18 17:20:32 by davmoren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	change_update_dir(t_shell *mini_sh, char *path)
{
	char	old_cwd[PATH_MAX];

	if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
	{
		perror("cd: getcwd");
		return (EXIT_FAILURE);
	}
	if (chdir(path) < 0)
	{
		handle_cd_error(path);
		return (EXIT_FAILURE);
	}
	return (update_dir_env(mini_sh, old_cwd));
}

char	*get_cd_env_path(t_shell *mini_sh, const char *var, const char *err)
{
	char	*path;

	path = new_env2(&mini_sh->env, (char *)var);
	if (!path)
	{
		ft_puterr((char *)err);
		return (NULL);
	}
	return (ft_strdup(path));
}

char	*cd_set_path(t_shell *mini_sh, t_cmd *cmd)
{
	if (cmd->cmd_argc == 1 || !cmd->cmd_argv[1])
		return (get_cd_env_path(mini_sh, "HOME", "cd: HOME not set\n"));
	if (ft_strcmp(cmd->cmd_argv[1], "-") == 0)
		return (get_cd_env_path(mini_sh, "OLDPWD", "cd: OLDPWD not set\n"));
	return (ft_strdup(cmd->cmd_argv[1]));
}

void	handle_cd_error(char *path)
{
	char	*err;

	err = NULL;
	if (access(path, F_OK) != 0 || access(path, X_OK) != 0)
		err = ft_strjoin("cd: ", path);
	else if (access(path, R_OK) != 0)
		err = ft_strdup("cd");
	else if (is_file(path))
		err = ft_strjoin("cd: ", path);
	else if (is_directory(path))
		err = ft_strdup("cd");
	if (err)
	{
		perror(err);
		my_free((void **)&err);
	}
}

int	bi_cd(t_shell *mini_sh, t_cmd *cmd)
{
	int		exit_code;
	char	*path;

	path = cd_set_path(mini_sh, cmd);
	if (!path)
		return (EXIT_FAILURE);
	exit_code = change_update_dir(mini_sh, path);
	my_free((void **)&path);
	return (exit_code);
}
