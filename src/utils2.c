/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:34:43 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/19 00:51:47 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	my_free(void **mem)
{
	if (mem && *mem)
	{
		free(*mem);
		*mem = NULL;
	}
}

void	my_close(int *fd)
{
	if (fd && *fd > 2)
	{
		close(*fd);
		*fd = -1;
	}
}

void	free_token_list(t_token *list)
{
	t_token	*current;
	t_token	*next;

	current = list;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env && shell->env)
	{
		free_env_list(shell->env);
		free(shell -> env);
		shell->env = NULL;
	}
	if (shell->input)
	{
		if (shell->input->token_lst)
		{
			free_token_list(shell->input->token_lst);
		}
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->cmd)
	{
		clear_cmd(shell->cmd);
		free(shell->cmd);
		shell->cmd = NULL;
	}
	free(shell);
}
