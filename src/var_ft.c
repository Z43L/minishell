/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmoren <davmoren@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:05:48 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/08/18 16:54:19 by davmoren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	update_var(t_shell *mini_sh, char *name, char *value)
{
	t_env	*current;

	current = mini_sh->env;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (true);
		}
		current = current->next;
	}
	return (false);
}

void	register_var(t_shell *mini_sh, const char *argv)
{
	char	*name;
	char	*value;
	int		eq_pos;

	if (!argv)
		return ;
	eq_pos = ft_strchr_pos(argv, '=');
	if (eq_pos == -1)
	{
		name = ft_strdup(argv);
		value = NULL;
	}
	else
	{
		name = ft_substr(argv, 0, eq_pos);
		value = ft_substr(argv, eq_pos + 1, -1);
	}
	if (!update_var(mini_sh, name, value))
		add_var(mini_sh, name, value);
}

static t_env	*create_envnode(char *name, char *value)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
	{
		perror("Failed to allocate memory for env node");
		exit(1);
	}
	node->name = name;
	node->value = value;
	return (node);
}

void	add_var(t_shell *mini_sh, char *name, char *value)
{
	addback_envnode(&(mini_sh->env), create_envnode(name, value));
}

t_env	*copy_env(char **env)
{
	int		i;
	t_env	*head;
	char	*eq_ptr;
	char	*name;
	char	*value;

	i = 0;
	head = NULL;
	while (env[i])
	{
		eq_ptr = ft_strchr(env[i], '=');
		if (eq_ptr)
		{
			name = ft_substr(env[i], 0, eq_ptr - env[i]);
			value = ft_strdup(eq_ptr + 1);
			addback_envnode(&head, create_envnode(name, value));
		}
		i++;
	}
	return (head);
}
