/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:41:07 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/22 20:17:25 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_export(t_env **start)
{
	t_env	*current;

	current = *start;
	while (current)
	{
		if (current->value != NULL)
			printf("%s=\"%s\"\n", current->name, current->value);
		else
			printf("%s\n", current->name);
		current = current->next;
	}
}

static int	handle_invalid_var(char *arg)
{
	char	*err;
	char	*full_err;

	err = ft_strjoin("export: `", arg);
	if (!err)
		return (EXIT_FAILURE);
	full_err = ft_strjoin(err, "': not a valid identifier");
	free(err);
	if (full_err)
	{
		ft_puterr(full_err);
		free(full_err);
	}
	return (EXIT_FAILURE);
}

int	bi_export(t_shell *mini_sh, t_cmd *cmd)
{
	int	exit_code;
	int	i;

	exit_code = EXIT_SUCCESS;
	if (!cmd->cmd_argv[1])
		return (print_export(&(mini_sh->env)), exit_code);
	i = 1;
	while (cmd->cmd_argv[i])
	{
		if (!ft_strchr(cmd->cmd_argv[i++], '='))
			return (exit_code);
	}
	i = 1;
	while (cmd->cmd_argv[i])
	{
		if (is_valid_var_name(cmd->cmd_argv[i]))
			register_var(mini_sh, cmd->cmd_argv[i]);
		else
			exit_code = handle_invalid_var(cmd->cmd_argv[i]);
		i++;
	}
	return (exit_code);
}
