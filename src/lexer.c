/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:26:53 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/07/22 20:12:26 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lexer_vocal(t_token *token, t_cmd *cmd, char *av, t_token *token_list)
{
	(void)cmd;
	token->content = ft_strdup(av);
	if (!token->content)
	{
		perror("ft_strdup failed");
		return (-1);
	}
	if (is_command(token->content) == 1
		&& get_previous_token_type(token_list) != REDIR_OUT)
	{
		token->type = COMMAND;
		return (0);
	}
	if (lexer_redirections(token, av) == 0)
		return (0);
	if (handle_pipe_and_limiter(token, av, token_list) == 0)
		return (0);
	token->type = WORD;
	return (0);
}

void	add_token_back(t_token **head, t_token *nw)
{
	t_token	*current;

	if (!head || !nw)
		return ;
	if (!*head)
	{
		*head = nw;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = nw;
}

char	**initialize_lexer(const char *input, t_shell *shell,
		t_token **token_list_head)
{
	char	**words;

	*token_list_head = NULL;
	if (!input || !shell)
		return (NULL);
	words = ft_split(input, ' ');
	if (!words)
		return (NULL);
	return (words);
}

int	process_tokens(char **words, t_token **token_list_head, t_shell *shell)
{
	t_token	*nw;
	int		i;

	i = -1;
	while (words[++i])
	{
		nw = ft_calloc(1, sizeof(t_token));
		if (!nw)
		{
			free_split(words);
			if (*token_list_head)
				free_token_list(*token_list_head);
			return (-1);
		}
		if (lexer_vocal(nw, shell->cmd, words[i], *token_list_head) == -1)
		{
			free(nw);
			free_split(words);
			if (*token_list_head)
				free_token_list(*token_list_head);
			return (-1);
		}
		add_token_back(token_list_head, nw);
	}
	return (0);
}

int	lexer(const char *input, t_shell *shell)
{
	char	**words;
	t_token	*token_list_head;

	words = initialize_lexer(input, shell, &token_list_head);
	if (!words)
		return (-1);
	if (process_tokens(words, &token_list_head, shell) == -1)
		return (-1);
	shell->input->token_lst = token_list_head;
	free_split(words);
	return (0);
}
