/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:08:25 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/22 21:22:00 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_token_lstsize(t_token *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

int	count_args(t_token *node)
{
	int	count;

	count = 0;
	while (node && node->type != OP_PIPE)
	{
		if (node->type == COMMAND || node->type == WORD
			|| node->type == CMD_ARG)
			count++;
		else if (node->type == REDIR_IN || node->type == REDIR_OUT
			|| node->type == REDIR_APP || node->type == REDIR_HD)
		{
			if (node->next)
				node = node->next;
		}
		node = node->next;
	}
	return (count);
}

int	env_lstsize(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

char	*collect_command_segment(t_token **current)
{
	char	*cmd_str;
	char	*temp;

	cmd_str = NULL;
	while (*current && (*current)->type != OP_PIPE)
	{
		if ((*current)->type == COMMAND || (*current)->type == WORD
			|| (*current)->type == CMD_ARG)
		{
			if (!cmd_str)
				cmd_str = ft_strdup((*current)->content);
			else
			{
				temp = ft_strjoin(cmd_str, " ");
				free(cmd_str);
				cmd_str = ft_strjoin(temp, (*current)->content);
				free(temp);
			}
		}
		*current = (*current)->next;
	}
	return (cmd_str);
}
