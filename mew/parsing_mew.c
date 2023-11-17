#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 5

char *get_next_line(int fd)
{
    int i = 0;
    int rd = 0;
    char character;

    char *buffer = malloc(100000); // check before the current BUFFER_SIZE and then malloc
    while ((rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1)) > 0)
    {
        buffer[i++] = character;
        if (character == '\n')
            break;
    }
    buffer[i] = '\0';
    if (rd == -1 || i == 0 || (!buffer[i - 1] && !rd))
        return (free(buffer), NULL);
    return (buffer);
}

char  *ft_replace(char *str, char s, char r)
{
  int i = 0;
  char  *dup;

  if (!str)
  {printf("err\n"); return NULL;}
  dup = malloc(sizeof(char) * strlen(str) + 1);
  if (!dup)
  {printf("err mall\n"); return NULL;}
  while (str[i])
  {
    if (str[i] == s)
      dup[i] = r;
    else
      dup[i] = str[i];
    i++;
  }
  dup[i] = '\0';
  return (dup);
}

int is_empty(char *str)
{
  int i = 0;
  while (str[i])
  {
    if (str[i] != ' ' && str[i] != '\n')
      return (0);
    i++;
  }
  return (1);
}

char  *delete_end_spaces(char *str)
{
  char  *cpy;
  int i = strlen(str) - 1;
  while (str[i] == '\n' || str[i] == ' ')
    i--;
  cpy = calloc(sizeof(char), (i + 2));
  if (!cpy)
    return (printf("ERREUR MALL CPY\n"), NULL);
  strncpy(cpy, str, i + 2);
  free(str);
  return (cpy);
}

int	main(int argc, char **argv)
{
  char  *str;
  char  *line;
  int infile;
  int outfile;
  int count;

  if (argc != 3)
    return (printf("Bad arguments number\n"), 1);
  infile = open(argv[1], O_RDWR);
  outfile = open(argv[2], O_RDWR | O_CREAT);
  if (infile == -1 || outfile == -1)
    return (printf("ERREUR OPEN\n"), 1);
  while (1)
  {
    count = 0;
    write(outfile, "tr ", 3);
    while (count < 3)
    {
      str = get_next_line(infile);
      if (!str)
        return (close(infile), close(outfile), printf("EOF\n"), 0);
      if (is_empty(str))
       {free(str);continue;}
      str = delete_end_spaces(str);
      line = ft_replace(str, ' ', ',');
      if (!line)
        return (1);
      write(outfile, line, strlen(line) - 1);
      write(outfile, " ", 1);
      count++;
      free(str);
      free(line);
    }
    write(outfile, "247,184,207\n", strlen("247,184,207") + 1);
  }
  return (0);
}
