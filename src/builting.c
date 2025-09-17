/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:27:11 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/09/09 20:24:17 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(t_token *node)
{
	if (ft_strncmp(node->content, "echo", -1) == 0)
		return (BI_ECHO);
	if (ft_strncmp(node->content, "env", -1) == 0)
		return (BI_ENV);
	if (ft_strncmp(node->content, "cd", -1) == 0)
		return (BI_CD);
	if (ft_strncmp(node->content, "pwd", -1) == 0)
		return (BI_PWD);
	if (ft_strncmp(node->content, "unset", -1) == 0)
		return (BI_UNSET);
	if (ft_strncmp(node->content, "export", -1) == 0)
		return (BI_EXPORT);
	if (ft_strncmp(node->content, "exit", -1) == 0)
		return (BI_EXIT);
	return (NO_BI);
}

int	exec_builtin(t_shell *mini_sh, t_cmd *cmd, t_builtin bi_cmd)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (bi_cmd == BI_ECHO)
		exit_code = bi_echo(mini_sh, cmd);
	else if (bi_cmd == BI_PWD)
		exit_code = bi_pwd(mini_sh, cmd);
	else if (bi_cmd == BI_CD)
		exit_code = bi_cd(mini_sh, cmd);
	else if (bi_cmd == BI_EXIT)
		exit_code = bi_exit(mini_sh, cmd);
	else if (bi_cmd == BI_EXPORT)
		exit_code = bi_export(mini_sh, cmd);
	else if (bi_cmd == BI_UNSET)
		exit_code = bi_unset(mini_sh, cmd);
	else if (bi_cmd == BI_ENV)
		exit_code = print_env(mini_sh->env);
	else if (bi_cmd == BI_EXIT)
		exit_code = bi_exit(mini_sh, cmd);
	return (exit_code);
}

static void	super_close(t_shell *mini_sh, t_cmd cmd)
{
	mini_sh->exit_code = 1;
	close(mini_sh->save_stdin);
	close(mini_sh->save_stdout);
	clear_cmd(&cmd);
	return ;
}

void	exec_one_bi(t_shell *mini_sh, t_token *node, t_builtin bi_cmd)
{
	t_cmd	cmd;
	int		redirection;

	mini_sh->save_stdin = dup(STDIN_FILENO);
	mini_sh->save_stdout = dup(STDOUT_FILENO);
	ft_memset(&cmd, 0, sizeof(t_cmd));
	cmd.in_fd = STDIN_FILENO;
	cmd.out_fd = STDOUT_FILENO;
	cmd.cmd_argv = argv_node_print(node);
	redirection = handle_redirections(mini_sh, node, &cmd);
	if (redirection != 0)
		super_close(mini_sh, cmd);
	dup2(cmd.in_fd, STDIN_FILENO);
	dup2(cmd.out_fd, STDOUT_FILENO);
	if (cmd.in_fd != STDIN_FILENO)
		close(cmd.in_fd);
	if (cmd.out_fd != STDOUT_FILENO)
		close(cmd.out_fd);
	mini_sh->exit_code = exec_builtin(mini_sh, &cmd, bi_cmd);
	dup2(mini_sh->save_stdin, STDIN_FILENO);
	dup2(mini_sh->save_stdout, STDOUT_FILENO);
	close(mini_sh->save_stdin);
	close(mini_sh->save_stdout);
	clear_cmd(&cmd);
}
