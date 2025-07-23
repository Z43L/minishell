/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:45:38 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/19 01:29:13 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_shell_data(t_shell **shell, t_cmd **cmd, t_input **input)
{
	*shell = ft_calloc(1, sizeof(t_shell));
	*cmd = ft_calloc(1, sizeof(t_cmd));
	*input = ft_calloc(1, sizeof(t_input));
	if (!*shell || !*cmd || !*input)
	{
		ft_putstr_fd("Failed to allocate memory for shell data", 1);
		exit(1);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;
	t_token	*token;

	shell = ft_calloc(1, sizeof(t_shell));
	token = ft_calloc(1, sizeof(t_token));
	shell -> cmd = ft_calloc(1, sizeof(t_cmd));
	shell -> input = ft_calloc(1, sizeof(t_input));
	(void)ac;
	(void)av;
	init_shell_data(&shell, &shell -> cmd, &shell -> input);
	setup_interactive_signals();
	init_shell(shell, token, env);
	shell_loop(shell);
	free(shell);
	free(shell -> cmd);
	free(shell -> input);
	return (0);
}
