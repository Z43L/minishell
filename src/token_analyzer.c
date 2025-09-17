/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analyzer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:47:36 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/22 19:11:31 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	analyze_token(t_shell *shell, int index)
{
	t_token	*current_token;
	t_token	*token_list_head;
	int		type;
	char	*curr_str;

	curr_str = shell->st[index];
	current_token = malloc(sizeof(t_token));
	if (!current_token)
		exit(1);
	token_list_head = shell->input->token_lst;
	type = lexer_vocal(current_token, shell->cmd, curr_str, token_list_head);
	free(current_token);
	if (type == -2 || ft_isevil(curr_str) == -1)
		return (STATUS_ERROR);
	if (type == 3)
		return (STATUS_PIPE);
	if (type == 1)
	{
		shell->path[0] = malloc(sizeof(char *));
		shell->path[0] = comand_path(curr_str);
		shell->argumentos[shell->count++] = curr_str;
	}
	else if (type == 0)
		shell->argumentos[shell->count++] = curr_str;
	return (STATUS_OK);
}
