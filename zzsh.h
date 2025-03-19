#ifndef ZZSH_H
#define ZZSH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <glob.h>
#include <sys/types.h>
#include <pwd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <sys/wait.h>

typedef enum e_tokentype
{
  TOKEN_WORD,
  TOKEN_PIPE,
  TOKEN_AND_IF,
  TOKEN_OF_IF,
  TOKEN_SEMINCOLON,
  TOKEN_LESS,
  TOKEN_GREAT,
  TOKEN_DGREAT,
  TOKEN_DLESS,
  TOKEN_DLESSDASH,
  TOKEN_IO_NUMBER
} t_tokentype;

typedef struct s_token
{
  t_tokentype type;
  char *value;
  struct s_token *next;
} t_token;

typedef struct s_simple_command
{
  char **argv;
  int argc;
  t_token *redir;
  struct s_simple_command *next;
} t_simple_command;

typedef struct s_pipeline
{
  t_simple_command *first_command;
  struct  s_pipeline *next;
} t_pipeline;

typedef struct s_and_or
{
  t_pipeline *first_pipeline;
  t_tokentype op;
  struct s_and_or *next;
} t__and_or;

typedef struct s_command_line
{
  t__and_or *first_and_or;
  struct s_command_line *next;
} t_command_line;

typedef struct s_var 
{
  char *name;
  char *value;
  int local;
  struct s_var *next;
} t_var;

typedef struct s_alias
{
  char *name;
  char *command;
  struct s_alias *next;
}

t_token *create_token(t_tokentype type, const char *value);
void free_token(t_token *token);
void free_tokens(t_token *head);

#endif // !ZZSH_H

