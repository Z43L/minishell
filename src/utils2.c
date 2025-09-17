/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:34:43 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/09/17 15:07:28 by aamaya-g         ###   ########.fr       */
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

void	free_env_list(t_env **start)
{
	t_env	*node;
	t_env	*next_node;

	if (!start)
		return ;
	node = *start;
	while (node)
	{
		next_node = node->next;
		my_free((void **)&(node->name));
		my_free((void **)&(node->value));
		my_free((void **)&node);
		node = next_node;
	}
	*start = NULL;
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->command)
	{
		if (shell -> command -> split_path)
			free_split(shell -> command -> split_path);
		my_free((void **)shell->command);
	}
	if (shell->node)
		free_token_list(shell->node);
	if (shell->cmd)
	{
		clear_cmd(shell->cmd);
		my_free((void **)shell->cmd);
		shell->cmd = NULL;
	}
	if (shell->input)
	{
		if (shell->input->token_lst)
			free_token_list(shell->input->token_lst);
		my_free((void **)shell->input);
		shell->input = NULL;
	}
	if (shell->env)
		free_env_list(&(shell->env));
	my_free((void **)&shell);
}
