/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:12:29 by aamaya-g          #+#    #+#             */
/*   Updated: 2025/09/17 16:28:42 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define READ_END 0
# define WRITE_END 1
# define STATUS_OK 0
# define STATUS_ERROR -1
# define STATUS_PIPE -2
# define STATUS_EXIT -3

extern int			g_signals;

typedef enum e_bultin
{
	NO_BI,
	BI_ECHO,
	BI_PWD,
	BI_CD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT
}					t_builtin;

typedef enum e_type
{
	WORD,
	COMMAND,
	CMD_ARG,
	OP_PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_HD,
	REDIR_APP,
	FILE_PATH,
	LIMITER,
	D_QUOTES,
	S_QUOTES
}					t_type;

typedef struct s_is_command
{
	char			*path_env;
	char			**split_path;
	char			*temp_path;
	char			*full_command;
	int				i;
}					t_is_command;

typedef struct s_token
{
	char			*content;
	t_type			type;
	int				type_numered;
	int				index;
	bool			had_quotes;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	int				in_fd;
	int				out_fd;
	int				close_fd;
	int				cmd_argc;
	char			*quotes_conten;
	char			*cmd_path;
	char			**cmd_argv;
	char			**env;
	t_builtin		is_bi;
}					t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_input
{
	t_token			*token_lst;
	char			*readline;
	int				hd_count;
	int				hd_used;
	pid_t			*pid;
	int				*pipes;
	int				pipe_count;
}					t_input;

typedef struct s_shell
{
	t_is_command	*command;
	t_token			*node;
	t_input			*input;
	t_env			*env;
	t_cmd			*cmd;
	int				status;
	int				exit_code;
	char			**envv;
	char			**argumentos;
	char			**st;
	char			**path;
	int				count;
	int				save_stdin;
	int				save_stdout;
	int				exit_status;
}					t_shell;

// BI_CD ===============================================================
char				*new_env2(t_env **env_list, char *name);
void				handle_cd_error(char *path);
int					change_update_dir(t_shell *mini_sh, char *path);
int					bi_cd(t_shell *mini_sh, t_cmd *cmd);
int					update_dir_env(t_shell *mini_sh, char *old_cwd);
char				*get_cd_env_path(t_shell *mini_sh, const char *var,
						const char *err);
// BI_ECHO ===============================================================
bool				is_n(char *arg);
int					bi_echo(t_shell *mini_sh, t_cmd *cmd);
// BI_EXIT ===============================================================
int					bi_exit(t_shell *mini_sh, t_cmd *cmd);
// BI_EXPORT ===============================================================
void				print_export(t_env **start);
int					bi_export(t_shell *mini_sh, t_cmd *cmd);
// BI_PWD ===============================================================
int					bi_pwd(t_shell *mini_sh, t_cmd *cmd);
// BI_UNSET ===============================================================
void				remove_node(t_env **start, char *name);
int					bi_unset(t_shell *mini_sh, t_cmd *cmd);
// BUILTING ===============================================================
int					is_builtin(t_token *node);
int					exec_builtin(t_shell *mini_sh, t_cmd *cmd,
						t_builtin bi_cmd);
void				exec_one_bi(t_shell *mini_sh, t_token *node,
						t_builtin bi_cmd);
// CMD_EXIT ===============================================================
void				clear_cmd(t_cmd *cmd);
// ENV ===============================================================
void				addback_envnode(t_env **start, t_env *node);
char				*my_getenv(t_env *start, char *name);
int					is_valid_var_name(const char *argv);
int					print_env(t_env *start);
// EXECUTION_UTILS ========================================================
int					count_args(t_token *node);
int					ft_token_lstsize(t_token *lst);
int					env_lstsize(t_env *env);
char				*collect_command_segment(t_token **current);
void				exec_pipe(t_shell *shell, t_token *tokens, int pipe_count);
int					has_command(t_token *tokens);
// EXECUTION ===============================================================
char				**argv_node_print(t_token *node);
char				**env_to_array(t_env *env);
char				**extract_commands_from_tokens(t_token *tokens,
						int pipe_count);
void				execute_cmds(char **envp, char **argumentos, char *path);
void				execution_dispatcher(t_shell *shell, t_token *tokens,
						int pipe_count);
void				exec_pipe(t_shell *shell, t_token *tokens, int pipe_count);
void				has_redirection(t_token *node, t_shell *shell);

// EXECUTION2 ===============================================================
void				free_cmd_resources(t_cmd *cmd, t_shell *mini_sh,
						int error_code);
void				handle_cmd_not_found(t_cmd *cmd, t_shell *mini_sh);
void				exec_child_process(t_cmd *cmd);
void				setup_cmd_struct(t_shell *mini_sh, t_token *node,
						t_cmd *cmd);
void				execute_single_external_command(t_shell *mini_sh,
						t_token *node);
void				execute_piped_segment(t_shell *shell,
						t_token *segment_start, int in_fd, int out_fd,
						int *pipes, int pipe_count);
void				exec_pipe_loop(t_shell *shell, int *pipes, pid_t *pids,
						int pipe_count, t_token *tokens);
// EXPANSION ===============================================================
char				*get_var_value(char *name, t_shell *shell);
char				*extract_var_name(char *str);
char				*expand_variables(char *str, t_shell *shell);
char				*handle_dollar(char *str, int *i, char *final_str,
						t_shell *shell);
void				perform_expansion(t_token *token_list, t_shell *shell);
// INIT ===============================================================
void				init_shell(t_shell *shell, t_token *token, char **env);
// IS_COMAND ===============================================================
int					is_command(char *word);
char				*comand_path(char *word);
// LEXER_UTILS ===============================================================
t_type				get_previous_token_type(t_token *token_list);
int					handle_output_redirections(t_token *token, char *av);
int					handle_input_redirections(t_token *token, char *av);
int					lexer_redirections(t_token *token, char *av);
int					handle_pipe_and_limiter(t_token *token, char *av,
						t_token *token_list);
// LEXER ===============================================================
int					lexer_vocal(t_token *token, t_cmd *cmd, char *av,
						t_token *token_list);
void				add_token_back(t_token **head, t_token *nw);
char				**initialize_lexer(const char *input, t_shell *shell,
						t_token **token_list_head);
int					process_tokens(char **words, t_token **token_list_head,
						t_shell *shell);
int					lexer(const char *input, t_shell *shell);
// MAIN / MAIN_LOOP ==========================================================
void				init_shell_data(t_shell **shell, t_cmd **cmd,
						t_input **input);
void				shell_loop(t_shell *shell);
// PIPEX_UTILS ===============================================================
int					create_pipes(int *pipes, int countpipex);
void				close_pipes(int *pipes, int countpipex);
void				setup_pipes(int n, int countpipex, int *pipes);
void				execute_command(char *command, char **env);
// PIPEX ===============================================================
int					launch_pipe_processes(t_input *px, char **fullcomand,
						char **env);
int					pipex(char **fullcomand, char **env, int countpipex);
// PROCESS_INPUT ===============================================================
void				execute_logic(t_shell *shell, const char *line, char **env,
						int pipes);
void				add_token_to_list(t_token **list, t_token *new_token);
int					create_heredoc_file(const char *limiter);

int					handle_heredoc(t_token *redir_node);
// PROCESS_INPUT2 =============================================================
int					preprocess_heredocs(t_token *token_list);
int					validate_and_preprocess_tokens(t_shell *shell);
void				execute_tokens(t_shell *shell);
int					process_input_line(t_shell *shell, char *line);
int					update_heredoc_token(t_token *redir_node);
// QUOTES_UTILS ===============================================================
char				*initialize_result(char *str, int *len, int *i, int *j);
void				process_quotes(char *str, char *result, int *i, int *j);
char				*remove_quotes(char *str);
bool				has_unclosed_quotes(const char *str);
int					contains_unclosed_quotes(t_token *t);
// QUOTES ===============================================================
int					qoutes_total(char **av, int index, t_token *token);
int					quotes(char *str, t_cmd *cmd, t_token *token, char **av);
// REDIRECTIONS ===============================================================
int					handle_redirections(t_shell *mini_sh, t_token *node,
						t_cmd *cmd);
void				open_outfile(t_token *node, t_cmd *cmd);
void				open_infile(t_token *node, t_cmd *cmd);
void				open_here_doc_file(t_shell *mini_sh, t_cmd *cmd);
// SIGNALS ===============================================================
void				setup_interactive_signals(void);
void				setup_execution_signals(void);
// SYNTAX_VALIDATOR ==========================================================
int					validate_token_sequence(t_token *tokens);
// TOKEN_ANALYZER ===========================================================
int					analyze_token(t_shell *shell, int index);
// TOKENS ===============================================================
t_token				*create_token(const char *value, t_type type);
void				free_token(t_token *token);
// TYPE ===============================================================
int					is_file(char *route);
int					is_directory(char *route);
// UTILS ==============================================================
size_t				split_len(char **input);
void				free_split(char **array);
char				**split_cpy(char **input);
void				my_perr(const char *msg, bool should_exit, int exit_code);
// UTILS2 ===============================================================
void				my_free(void **mem);
void				my_close(int *fd);
void				free_token_list(t_token *list);
void				free_env_list(t_env **start);
void				free_shell(t_shell *shell);
// VAR_FT ===============================================================
void				add_var(t_shell *ini_sh, char *name, char *value);
t_env				*copy_env(char **env);
void				register_var(t_shell *mini_sh, const char *argv);

#endif
