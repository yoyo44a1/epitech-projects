/*
** child.c for mysh in /home/gicque_p/local/unix/PSU_2013_minishell1
** 
** Made by Pierrick Gicquelais
** Login   <gicque_p@epitech.net>
** 
** Started on  Fri Dec 13 12:08:52 2013 Pierrick Gicquelais
** Last update Sat Dec 21 17:08:22 2013 Pierrick Gicquelais
*/

#include	"../shell.h"

void		child_process(char *s, char **tab, char **env)
{
  int		i;

  my_builtin(s, env);
  my_alias(s, tab, env);
  my_execution(tab, env);
  if (s[0] != 'c' || s[1] != 'd')
    {
      i = -1;
      while (env[++i])
      	free(env[i]);
      i = -1;
      while (tab[++i])
      	free(tab[i]);
      my_spec_error(s);
    }
  free(tab);
  free(env);
  exit(EXIT_SUCCESS);
}

void		parent_process(char **env)
{
  pid_t		pid;
  char		*s;
  char		**tab;

  while ((s = get_next_line(0)) != NULL)
    {
      if (my_strcmp("exit", s) == 0)
	exit(EXIT_SUCCESS);
      signal(SIGINT, SIG_IGN);
      tab = my_str_to_wordtab(s);
      my_cd(s, tab, env);
      if (s[0] != 'c' || s[1] != 'd')
	pid = fork();
      if (pid == 0 && (s[0] != 'c' || s[1] != 'd'))
        child_process(s, tab, env);
      else if (pid == -1)
        my_error("Impossible to create a child process");
      else
        {
	  waitpid(pid, 0, WSTOPPED);
          my_putstr("$> ");
        }
      free(s);
      free(tab);
    }
}
