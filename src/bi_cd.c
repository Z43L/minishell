/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:24:32 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/22 20:04:47 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*new_env2(t_env **env_list, char *name)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static char	*cd_set_path(t_shell *mini_sh, t_cmd *cmd)
{
	char	*path;

	if (cmd->cmd_argc == 1)
	{
		path = my_getenv(mini_sh->env, "HOME");
		if (!path)
		{
			ft_puterr("cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (cmd->cmd_argv[1] && ft_strcmp(cmd->cmd_argv[1], "-") == 0)
	{
		path = my_getenv(mini_sh->env, "OLDPWD");
		if (!path)
		{
			ft_puterr("cd: OLDPWD not set\n");
			return (NULL);
		}
	}
	else
		path = ft_strdup(cmd->cmd_argv[1]);
	return (path);
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

int	change_update_dir(t_shell *mini_sh, char *path)
{
	int		exit_code;
	char	cwd[PATH_MAX];
	char	*oldpwd;
	char	*pwd;

	oldpwd = NULL;
	pwd = NULL;
	exit_code = EXIT_SUCCESS;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		oldpwd = ft_strjoin("OLDPWD=", cwd);
	else
		exit_code = EXIT_FAILURE;
	if (chdir(path) < 0)
	{
		handle_cd_error(path);
		my_free((void **)&oldpwd);
		return (EXIT_FAILURE);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		register_var(mini_sh, oldpwd);
		pwd = ft_strjoin("PWD=", cwd);
		register_var(mini_sh, pwd);
	}
	else
	{
		perror("cd: getcwd");
		exit_code = EXIT_FAILURE;
	}
	my_free((void **)&oldpwd);
	my_free((void **)&pwd);
	return (exit_code);
}

int	bi_cd(t_shell *mini_sh, t_cmd *cmd)
{
	int		exit_code;
	char	*raw_path;
	char	*path;

	raw_path = cd_set_path(mini_sh, cmd);
	if (!raw_path)
		return (EXIT_FAILURE);
	path = ft_strdup(raw_path);
	if (!path)
	{
		ft_puterr("cd: path is NULL\n");
		return (EXIT_FAILURE);
	}
	exit_code = change_update_dir(mini_sh, path);
	my_free((void **)&path);
	return (exit_code);
}
