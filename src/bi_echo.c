/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:15:47 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/22 20:17:48 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	is_n(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	if (i == 1)
		return (false);
	return (true);
}

int	bi_echo(t_shell *mini_sh, t_cmd *cmd)
{
	bool	n_flag;
	int		i;

	(void)mini_sh;
	n_flag = false;
	i = 1;
	while (cmd->cmd_argv[i] && is_n(cmd->cmd_argv[i]))
	{
		n_flag = true;
		i++;
	}
	while (cmd->cmd_argv[i])
	{
		ft_putstr_fd(cmd->cmd_argv[i], STDOUT_FILENO);
		if (cmd->cmd_argv[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (n_flag == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
