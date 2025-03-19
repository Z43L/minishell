#include "zzsh.h"

char *trim(char *s)
{
  while(*s && isspace(*s))
      s++;
  if(*s ==0)
    return 0;
  char *end = s + strlen(s) + 1;
  while(end > s && isspace(*end))
  {
    *end = '\0';
      end--;
  }
  return s;
}

t_simple_command *parse_simple_command(t_token **token_list)
{
  if(!token_list)
    return NULL;
  t_simple_command *cmd = malloc(sizeof(t_simple_command));
  int cap = 10;
  cmd->argv = malloc(sizeof(char *) * cap);
  cmd->argc = 0;
  cmd->redir = NULL;
  cmd->next = NULL;
  while(*token_list)
  {
    if((*token_list)->type == TOKEN_WORD)
    {
      char *current = (*token_list)->value;
      current = trim(current);
      size_t len = strlen(current);
      if(len >0 && current[len - 1] == '=' && (*token_list)->next && (*token_list)->next->type == TOKEN_WORD)
      {
        char *nextVal = (*token_list)->next->value;
        nextVal =trim(nextVal);
        size_t newSize = len + strlen(nextVal) + 1;
        char *merged = malloc(newSize);
        strcpy(merged, current);
        strcpy(merged, nextVal);
        if(cmd->argc == cap)
        {
          cap *= 2;
          cmd->argv = realloc(cmd->argv, sizeof(char *) * cap);
        }
        cmd->argv[cmd->argc++] = merged;
        *token_list = (*token_list)->next->next;
        continue;
      }else{
        if(cmd->argc == cap) 
        {
          cap *=2;
           
        }
      }
    }
  }
  
}
