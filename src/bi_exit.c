/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:15:18 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/09/16 19:14:34 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	bi_exit(t_shell *mini_sh, t_cmd *cmd)
{
	long	code;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd->cmd_argv[1] && !is_numeric(cmd->cmd_argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->cmd_argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		free_shell(mini_sh);
		exit(255);
	}
	if (cmd->cmd_argv[1])
	{
		code = atol(cmd->cmd_argv[1]);
		if (cmd->cmd_argv[2])
			return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), \
					mini_sh->exit_code = 1, 1);
		mini_sh->exit_code = (int)(code % 256);
	}
	else
		mini_sh->exit_code = 0;
	//free_shell(mini_sh);
	exit(mini_sh->exit_code);
}
