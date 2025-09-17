/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd__two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmoren <davmoren@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:46:15 by davmoren          #+#    #+#             */
/*   Updated: 2025/08/18 16:52:43 by davmoren         ###   ########.fr       */
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

int	update_dir_env(t_shell *mini_sh, char *old_cwd)
{
	char	new_cwd[PATH_MAX];
	char	*oldpwd_var;
	char	*pwd_var;

	oldpwd_var = ft_strjoin("OLDPWD=", old_cwd);
	if (!oldpwd_var)
		return (EXIT_FAILURE);
	register_var(mini_sh, oldpwd_var);
	my_free((void **)&oldpwd_var);
	if (getcwd(new_cwd, sizeof(new_cwd)) == NULL)
	{
		perror("cd: getcwd");
		return (EXIT_FAILURE);
	}
	pwd_var = ft_strjoin("PWD=", new_cwd);
	if (!pwd_var)
		return (EXIT_FAILURE);
	register_var(mini_sh, pwd_var);
	my_free((void **)&pwd_var);
	return (EXIT_SUCCESS);
}
