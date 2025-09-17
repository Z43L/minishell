/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:24:10 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/09/09 21:20:37 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("Minishell >>>> ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			process_input_line(shell, line);
		}
		free(line);
	}
	free_shell(shell);
	exit(0);
}
