/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:28:45 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/22 20:28:55 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_var_value(char *name, t_shell *shell)
{
	t_env	*current;

	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(shell->exit_code));
	current = (shell->env);
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (current->value)
				return (ft_strdup(current->value));
			else
				return (ft_strdup(""));
		}
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*extract_var_name(char *str)
{
	int	i;

	i = 0;
	
	if (!str || !*str)
		return (NULL);
	if (str[i] == '?')
		return (ft_strdup("?"));
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (NULL);
	i++;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (ft_substr(str, 0, i));
}

char	*expand_variables(char *str, t_shell *shell)
{
	char	*final_str;
	char	*temp_join;
	char	*temp_sub;
	int		i;
	int		start;

	i = -1;
	start = 0;
	final_str = ft_strdup("");
	while (str && str[++i])
	{
		
		if (str[i] == '$')
		{
			temp_sub = ft_substr(str, start, i - start);
			temp_join = ft_strjoin(final_str, temp_sub);
			(free(final_str), free(temp_sub));
			final_str = temp_join;
			final_str = handle_dollar(str, &i, final_str, shell);
			start = i + 1;
		}
	}
	temp_sub = ft_substr(str, start, i - start);
	temp_join = ft_strjoin(final_str, temp_sub);
	(free(final_str), free(temp_sub));
	return (temp_join);
}

char	*handle_dollar(char *str, int *i, char *final_str, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	char	*temp_join;

	var_name = extract_var_name(&str[*i + 1]);
	if (var_name)
	{
		var_value = get_var_value(var_name, shell);
		temp_join = ft_strjoin(final_str, var_value);
		(free(final_str), free(var_value));
		final_str = temp_join;
		*i += ft_strlen(var_name);
		free(var_name);
	}
	else
	{
		temp_join = ft_strjoin(final_str, "$");
		free(final_str);
		final_str = temp_join;
	}
	return (final_str);
}

void	perform_expansion(t_token *token_list, t_shell *shell)
{
	t_token	*current;
	t_token	*prev;
	char	*original_content;
	bool	is_heredoc_limiter;

	current = token_list;
	prev = NULL;
	while (current)
	{
		is_heredoc_limiter = (prev && prev->type == REDIR_HD);
		if (current->type != S_QUOTES && !is_heredoc_limiter
			&& ft_strchr(current->content, '$'))
		{
			original_content = current->content;
			current->content = expand_variables(original_content, shell);
			free(original_content);
		}
		prev = current;
		current = current->next;
	}
}
