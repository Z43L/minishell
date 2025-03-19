#include "zzsh.h"

t_token lexer(const char *input)
{
  t_token *head = NULL;
  t_token *tail = NULL;
  const char *p = input;
  char buffer[1024];
  int buf_index = 0;
  while(*p)
  {
    if(isspace(*p))
    {
      p++;
      continue;
    }
    if(*p == '"' || *p == '\')
    {
       char quote = *p++;
       buf_index = 0;
       while(*p && *p != quote)
       {
          if(*p == '\\' && * (*p+1))
            p++;
          buffer[buf_index++] = *p++;
       }
       if(p == quote)
          p++;
       buffer[buf_index] = '\0';
       t_token *tok = create_token(TOKEN_WORD, buffer);
       if(!head)
       {
          head = tok;
          tail = tok;
       }
       else 
       {
          tail->next = tok;
          tail = tok;
       }
       continue;
    }
    if(*p == '\\')
      {
        p++;
        if(*p)
        {
          buffer[0]= *p++;
          buffer[1] = '\0';
          t_token *tok = create_token(TOKEN_WORD, buffer);
          if(!head)
          {
            head = tok;
            tail = tok;
          }
          else {
            tail->next= tok;
            tail = tok;
          }
          continue;
        }
      }
    if(*p != '|' && *p != '>' && *p != '<' && *p != ';' && *p != '&')
    {
      buf_index =0;
      while(*p && !isspace(*p) && *p != '|' && *p != '>' && *p != '<' && *p != ';' && *p != '&')
      {
        if(*p == '\\' && p+1)
        {
          *p++;
          buffer[buf_index++]= *p++;
        }else {
          buffer[buf_index++] = *p++;
        }
      }
      buffer[buf_index] = '\0';
      t_token *tok = create_token(TOKEN_WORD, buffer);
      if(!head)
      {
        head = tok;
        tail = tok;
      }else {
        tail->next = tok;
        tail = tok;
      }
      continue

    }
    if(*p == '|')
    {
      if( *(p+1) == '|')
      {
        t_token *tok = create_token(TOKEN_OR_IF, '||');
        p +=2;
        if(!head)
        {
          head = tok;
          tail = tok;
        }else {
          tail->next = tok;
          tail = tok;
        }
        continue;
        
      }else {
        t_token *tok = create_token(TOKEN_OR_IF, '|');
        p++;
        if(!head)
        {
          head = tok;
          tail = tok;
        }
        else {
          tail->next = tok;
          tail = tok;
        }
      }
      continue;
    }
    if(*p == '&')
    {
      if(*(p+1) == '&')
      {
        t_token *tok = create_token(TOKEN_AND_IF, '&&')
        p += 2;
        if(!head)
        {
          head = tok;
          tail = tok;
        }else {
          tail->next = tok;
          tail = tok;
          }
        continue;
        }
    }
    if(*p == ';' )
    {
      t_token *tok = create_token(TOKEN_SEMICOLON, ';');
      *p++;
      if(!head)
      {
        head = tok;
        tail = tok;
      }else {
        tail->next = tok;
        tail = tok;
      }
      continue;
    }
    if(*p == '<')
    {
      if(*(p+1) == '<2')
      {
          if(*(p+2) =='-')
          {
            t_token *tok = create_token(TOKEN_DLESSDASH, "<<-");
            p =+ 3;
            if(!head)
            {
            head = tok;
              tail = tok;
            }else {
              tail->next = tok;
              tail = tok;
            }
          }else {
            t_token *tok = create_token(TOKEN_DLESS, "<<");
            p+= 2;
            if(!head)
            {
              head = tok;
              tail = tok;
            }else {
              tail->next = tok;
              tail = tok;
            }
          }
        }else {
        t_token *tok = create_token(TOKEN_LESS, '<');
        p++;
        if(!head)
        {
          head = tok;
          tail = tok;
        }else {
          tail->next = tok;
          tail = tok;
        }
        continue;
      }
      if(*p == '>')
      {
        if(*(p+1)= '>')
        {
          t_token *tok = create_token(TOKEN_DGREAT, ">>");
          p += 2;
          if(!head)
          {
            head = tok;
            tail = tok;
          }else {
            tail->next = tok;
            tail = tok;
          }
        }else {
          t_token *tok = create_token(TOKEN_GREAT, '>');
          p++;
          if(!head)
          {
            head = tok;
            tail = tok;
          }else {
            tail->next = tok;
            tail = tok;
          }
        }
      }
      continue;
    }
    p++;
  }
  return head;
}
