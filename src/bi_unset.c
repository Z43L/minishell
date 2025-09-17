/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:05:39 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/22 20:16:48 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_node(t_env **start, char *name)
{
	t_env	*current;
	t_env	*previous;

	current = *start;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, name, -1) == 0)
		{
			if (previous == NULL)
				*start = current->next;
			else
				previous->next = current->next;
			my_free((void **)&(current->name));
			my_free((void **)&(current->value));
			my_free((void **)&current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

int	bi_unset(t_shell *mini_sh, t_cmd *cmd)
{
	int	i;
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (!cmd->cmd_argv[1])
		return (exit_code);
	i = 1;
	while (cmd->cmd_argv[i])
	{
		remove_node(&(mini_sh->env), cmd->cmd_argv[i]);
		i++;
	}
	return (exit_code);
}
