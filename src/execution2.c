/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 03:28:39 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/09/17 14:22:39 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_cmd_resources(t_cmd *cmd, t_shell *mini_sh, int error_code)
{
	if (cmd->in_fd != STDIN_FILENO)
		close(cmd->in_fd);
	if (cmd->out_fd != STDOUT_FILENO)
		close(cmd->out_fd);
	clear_cmd(cmd);
	free_split(cmd->env);
	if (error_code)
		mini_sh->exit_code = error_code;
}

void	handle_cmd_not_found(t_cmd *cmd, t_shell *mini_sh)
{
	if (!cmd || !cmd->cmd_argv || !cmd->cmd_argv[0])
        return;
	ft_puterr("minishell: ");
	ft_puterr(cmd->cmd_argv[0]);
	ft_puterr(": command not found\n");
	mini_sh->exit_code = 127;
	clear_cmd(cmd);
}

void	exec_child_process(t_cmd *cmd)
{
	dup2(cmd->in_fd, STDIN_FILENO);
	dup2(cmd->out_fd, STDOUT_FILENO);
	if (cmd->in_fd != STDIN_FILENO)
		close(cmd->in_fd);
	if (cmd->out_fd != STDOUT_FILENO)
		close(cmd->out_fd);
	execve(cmd->cmd_path, cmd->cmd_argv, cmd->env);
	my_perr("execve", true, 127);
}

void	setup_cmd_struct(t_shell *mini_sh, t_token *node, t_cmd *cmd)
{
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->in_fd = STDIN_FILENO;
	cmd->out_fd = STDOUT_FILENO;
	cmd->cmd_argv = argv_node_print(node);
	if (!cmd->cmd_argv[0])
	{
		if (handle_redirections(mini_sh, node, cmd) != 0)
			mini_sh->exit_code = 1;
		clear_cmd(cmd);
	}
	if (cmd->cmd_argv && cmd->cmd_argv[0])
    	cmd->cmd_path = comand_path(cmd->cmd_argv[0]);
	else
    	cmd->cmd_path = NULL;
}

void	execute_single_external_command(t_shell *mini_sh, t_token *node)
{
	t_cmd	cmd;
	pid_t	pid;
	int		status;

	setup_cmd_struct(mini_sh, node, &cmd);
	if (!cmd.cmd_path)
		return (handle_cmd_not_found(&cmd, mini_sh));
	if (handle_redirections(mini_sh, node, &cmd) != 0)
		return (free_cmd_resources(&cmd, mini_sh, 1));
	cmd.env = env_to_array(mini_sh->env);
	pid = fork();
	if (pid == -1)
		my_perr("fork", true, 1);
	if (pid == 0)
		exec_child_process(&cmd);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			mini_sh->exit_code = WEXITSTATUS(status);
	}
	free_cmd_resources(&cmd, mini_sh, 0);
}
