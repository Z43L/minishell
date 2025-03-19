#include "zzsh.h"

t_token *create_token(t_tokentype type, const char *value)
{
  t_token *tok = malloc(sizeof(t_token));
  tok->type = type;
  if(value)
  {
    tok->value = strdup(value);
  }
  else {
    tok->value = NULL;
  }
  tok->next = NULL;
  return tok;
}

void free_token(t_token *token)
{
  if(token)
  {
    free(token->value);
    free(token);
  }
}

void free_tokens(t_token *head)
{
  t_token *curr = head, *next;
  while(curr)
  {
    next = curr->next;
    free_token(curr);
    curr = next;
  }
}
