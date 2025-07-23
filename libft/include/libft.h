/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamaya-g <aamaya-g@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:13:49 by aamaya-g          #+#    #+#             */
/*   Updated: 2024/04/16 15:45:49 by aamaya-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
#  define OPEN_MAX 256
# endif

# include "../../include/minishell.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>

# define ERR_INPUT "unvalid argc, use: ./pipex infile cmd1 cmd2 outfile"

//chek_functions
int		ft_isascii(int c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isevil(char *av);
//
//memory_functions
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
//
//strings_functions
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *str);
int		ft_atoi_base(const char *str, const char *base);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t dstize);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_itoa(int n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	**ft_split(const char *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dst, char *src);
int		ft_strchr_pos(const char *s, char c);
//
//write_functions
void	ft_putchar_fd(int c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_puterr(char *s);

//
//List_functions
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
//
//Printf_functions
int		ft_printf(const char *str, ...);
int		print_char(char c, int len);
int		print_str(char *str, int len);
int		print_number(int nb, int len);
int		print_positive_number(unsigned int nb, int len);
int		print_hex(size_t nb, int len, char format);
int		ft_print_pointer(void *ptr, int len);
int		find_print(const char *str, int i, int len, va_list list);
//
//Get_next_line_functions
char	*get_next_line(int fd);
int		line_len(char *buffer);
char	*set_line(char **left_over);
char	*ft_strjoin_special(char const *s1, char const *s2, int bytes_read);
char	*ft_strchr_gnl(const char *s, int c);
char	*ft_strdup_gnl(const char *s1);
void	fill_buffer(int fd, char *buffer, char **left_over);

//============ PIPEX ======================

enum e_num_px_error
{
	OK_EN,
	CMD_NOT_FOUND,
	NO_FILE,
	NO_PERMS,
	INV_ARGS,
	NO_MEMORY,
	PIPE_ERR,
	DUP_ERR,
	FORK_ERR,
	NO_PATH,
	CMD_FAIL ,
	MALLOC_ERR
};

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd_pipe[2];
	int		in_fd;
	int		out_fd;
	char	**paths_array;
	char	**cmd_argv;
	char	*cmd_path;
}	t_pipex;

enum e_pxb_error
{
	ERR_HEREDOC = -12,
	ERR_RDHEREDOC = -13,
	ERR_HEREDOC_EOF = -14
};

typedef struct s_pipex_bonus
{
	int		in_fd;
	int		out_fd;
	int		*pipe;
	int		n_cmd;
	pid_t	*pid;
	bool	here_doc;
	char	**paths_array;
	char	**cmd_argv;
	char	*cmd_path;

}	t_pipex_bonus;

//pipex free

void	ft_free(char **array);
void	free_child(t_pipex *pipex);
void	free_father_fd(t_pipex	*pipex);

//pipex_error

void	px_error_msg(char *param, int err);
void	px_error_free(t_pipex *pipex, char *param, int err);
void	px_error_exit(char *param, int err);
void	px_malloc_error(void);

//pipex_paths

char	**px_split_path(char **envp);
char	*find_cmd_path(char *cmd, char **paths_array);

//pipex_childs

void	first_child(t_pipex *pipex, char **argv, char **envp);
void	second_child(t_pipex *pipex, char **argv, char **envp);

//pipex_error_msg_bonus

void	pxb_error_msg(int err, char *param);
void	pxb_perror_exit(int err, char *param);
void	pxb_cmd_not_found(t_pipex_bonus *pipex);
void	pxb_cmd_fail_exit(t_pipex_bonus *pipex);

//pipex_check_files_bonus

void	pxb_check_infile(t_pipex_bonus *pipex, char **argv);
void	pxb_check_outfile(t_pipex_bonus *pipex, char **argv);

//pipex_free_close_bonus

void	pxb_close_pipes(t_pipex_bonus *pipex);
void	pxb_free_parent(t_pipex_bonus *pipex);
void	pxb_freeparent_closefd(t_pipex_bonus *pipex);

//pipex_here_doc_bonus

void	pxb_here_doc(t_pipex_bonus *pipex, char **argv);

//pipex_childs_bonus

void	pxb_first_child(t_pipex_bonus *pipex, char **argv, char **envp);
void	pxb_last_child(t_pipex_bonus *pipex, char **argv, char **envp);
void	pxb_middle_child(t_pipex_bonus *pipex, char **argv, char **envp, int i);
void	pxb_select_child(t_pipex_bonus *pipex, char **argv, char **envp, int i);

// the final pipex

void	mainpipex(int count, char **commands, char **env);

#endif