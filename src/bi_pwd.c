/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:07:28 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/22 20:16:14 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	bi_pwd(t_shell *mini_sh, t_cmd *cmd)
{
	int		exit_code;
	char	buffer[1024];

	(void)mini_sh;
	(void)cmd;
	exit_code = EXIT_SUCCESS;
	if (getcwd(buffer, sizeof(buffer)) != NULL)
		ft_putendl_fd(buffer, STDOUT_FILENO);
	else
		(perror("pwd"), exit_code = EXIT_FAILURE);
	return (exit_code);
}
