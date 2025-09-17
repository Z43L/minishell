/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:09:31 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/23 13:37:21 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_declarer(t_shell *shell, t_token *token)
{
	shell->exit_code = 0;
	shell->input->readline = NULL;
	shell->input->token_lst = token;
	shell->input->hd_count = 0;
	shell->input->pipe_count = 0;
	shell->input->hd_used = 0;
	shell->input->pid = NULL;
}

void	init_shell(t_shell *shell, t_token *token, char **env)
{
	char	*system_home;

	if (!shell->input)
	{
		shell->input = ft_calloc(1, sizeof(t_input));
		if (!shell->input)
			my_perr("Failed to allocate memory for shell->input", true, 1);
	}
	shell->env = copy_env(env);
	if (!shell->env)
		my_perr("Failed to allocate memory for shell->env", true, 1);
	if (!new_env2(&(shell->env), "HOME"))
	{
		system_home = getenv("HOME");
		if (system_home)
			add_var(shell, "HOME", system_home);
		else
			ft_puterr("cd: HOME not set\n");
	}
	init_declarer(shell, token);
}
