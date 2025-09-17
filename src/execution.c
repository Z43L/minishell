/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:13:47 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/09/17 16:27:40 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**argv_node_print(t_token *node)
{
	int		argc;
	char	**argv;
	int		i;

	argc = count_args(node);
	argv = ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
		exit(1);
	i = 0;
	while (node && node->type != OP_PIPE)
	{
		if (node->type == COMMAND || node->type == WORD
			|| node->type == CMD_ARG)
		{
			argv[i++] = remove_quotes(node->content);
		}
		else if (node->type == REDIR_IN || node->type == REDIR_OUT
			|| node->type == REDIR_APP || node->type == REDIR_HD)
		{
			if (node->next)
				node = node->next;
		}
		node = node->next;
	}
	return (argv);
}

char	**env_to_array(t_env *env)
{
	int		size;
	char	**envp;
	int		i;
	int		len;

	size = env_lstsize(env);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		len = strlen(env->name) + strlen(env->value) + 2;
		envp[i] = malloc(len);
		if (!envp[i])
		{
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		strcpy(envp[i], env->name);
		strcat(envp[i], "=");
		strcat(envp[i], env->value);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	**extract_commands_from_tokens(t_token *tokens, int pipe_count)
{
	char	**commands;
	t_token	*current;
	int		cmd_index;

	cmd_index = 0;
	commands = malloc(sizeof(char *) * (pipe_count + 2));
	if (!commands)
		return (NULL);
	current = tokens;
	while (current && cmd_index <= pipe_count)
	{
		commands[cmd_index++] = collect_command_segment(&current);
		if (current && current->type == OP_PIPE)
			current = current->next;
	}
	commands[cmd_index] = NULL;
	return (commands);
}

void	execute_cmds(char **envp, char **argumentos, char *path)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(path, argumentos, envp);
		perror("execve failed");
		exit(127);
	}
	else if (pid < 0)
		perror("fork failed");
	else
		wait(NULL);
}

void	execution_dispatcher(t_shell *shell, t_token *tokens, int pipe_count)
{
	t_builtin	bi_cmd;

	if (!tokens)
		return ;
	if (contains_unclosed_quotes(tokens))
	{
		ft_putendl_fd("command invalid", 2);
		shell->exit_status = 1;
		return ;
	}
	bi_cmd = is_builtin(tokens);
	if (pipe_count > 0)
		exec_pipe(shell, tokens, pipe_count);
	else if (bi_cmd != NO_BI)
		exec_one_bi(shell, tokens, bi_cmd);
	else
		execute_single_external_command(shell, tokens);
}
