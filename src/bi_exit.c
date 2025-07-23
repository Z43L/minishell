/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:15:18 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/18 20:15:24 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	bi_exit(t_shell *mini_sh, t_cmd *cmd)
{
	int	exit_code;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (!cmd->cmd_argv[1])
	{
		exit_code = mini_sh->exit_code;
	}
	else if (cmd->cmd_argv[2])
	{
		ft_puterr("exit: too many arguments");
		return (1);
	}
	else if (!is_numeric(cmd->cmd_argv[1]))
	{
		ft_puterr("exit: numeric argument required");
		exit_code = 2;
	}
	else
	{
		exit_code = ft_atoi(cmd->cmd_argv[1]) % 256;
		if (exit_code < 0)
			exit_code = 256 + exit_code;
	}
	exit(exit_code);
}
