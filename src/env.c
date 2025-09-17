/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmoren <davmoren@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:23:39 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/08/18 16:54:30 by davmoren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	addback_envnode(t_env **start, t_env *node)
{
	t_env	*current;

	if (!*start)
		*start = node;
	else
	{
		current = *start;
		while (current->next)
			current = current->next;
		current->next = node;
	}
}

int	print_env(t_env *start)
{
	while (start)
	{
		printf("%s=%s\n", start->name, start->value);
		start = start->next;
	}
	return (STATUS_OK);
}

char	*my_getenv(t_env *start, char *name)
{
	if (!name)
		return (NULL);
	while (start)
	{
		if (ft_strncmp(start->name, name, ft_strlen(name) + 1) == 0)
			return (start->value);
		start = start->next;
	}
	return (NULL);
}

int	is_valid_var_name(const char *argv)
{
	char	*name;
	int		eq_pos;
	int		i;

	if (!argv || ft_strlen(argv) <= 0 || argv[0] == '=')
		return (false);
	eq_pos = ft_strchr_pos(argv, '=');
	if (eq_pos == -1)
		name = ft_strdup(argv);
	else
		name = ft_substr(argv, 0, eq_pos);
	i = 0;
	while (name[i] != '\0')
	{
		if (!ft_isalpha(name[0]) && name[0] != '_')
			return (my_free((void **)&name), false);
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (my_free((void **)&name), false);
		i++;
	}
	my_free((void **)&name);
	return (true);
}
