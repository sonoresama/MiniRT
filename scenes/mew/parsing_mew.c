#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 5

char	**ft_split(const char *s, char *charset);
void  ft_free_tab(char **tab);

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
  cpy = calloc(sizeof(char), (i + 1));
  if (!cpy)
    return (printf("ERREUR MALL CPY\n"), NULL);
  strncpy(cpy, str, i);
  cpy[i + 1] = '\0';
  free(str);
  return (cpy);
}

char  first_char(char *str)
{
  int i = 0;
  while (str[i] == ' ')
    i++;
  return (str[i]);
}

int  get_vectors(int infile)
{
  int fd;
  int i;
  char  *str;

  fd = open("middle.txt", O_RDWR | O_CREAT, 0666);
  if (fd == -1)
    return (printf("ERREUR OPEN MIDDLE\n"), 1);
  str = get_next_line(infile);
  while (str)
  {
    if (first_char(str) == 'v')
    {
      for(i = 0; str[i] != '-' && !isdigit(str[i]); i++){}
      write(fd, str + i, strlen(str) - i);
    }
    free(str);
    str = get_next_line(infile);
  }
  close(fd);
  return (0);
}

int parse_scientific(void)
{
  int middle;
  int scient;
  int i;
  int j;
  char  *str;
  char  **split;

  middle = open("middle.txt", O_RDWR);
  scient = open("scient.txt", O_RDWR | O_CREAT, 0666);
  if (scient == -1 || middle == -1)
    return (printf("pb open scient\n"), 1);
  str = get_next_line(middle);
  while (str)
  {
    i = 0;
    split = ft_split(str, " ");
    while (split && split[i])
    {
      j = 0;
      while (split[i][j])
      {
        if (split[i][j] == 'e')
          break;
        j++;
      }
      if (split[i][j])
      {
        write(scient, "0.00000000", 11);
         if (!split[i + 1])
           write(scient, " ", 1);
      }
      else
      {
        write(scient, split[i], strlen(split[i]));
        if (split[i + 1])
          write(scient, " ", 1);
      }
      i++;
    }
    free(str);
    ft_free_tab(split);
    str = get_next_line(middle);
  }
  close(middle);
  close(scient);
  return (0);
}

int	main(int argc, char **argv)
{
  char  *str;
  char  *line;
  int infile;
  int outfile;
  int middle;
  int count;

  if (argc != 3)
    return (printf("Bad arguments number\n"), 1);
  infile = open(argv[1], O_RDWR);
  outfile = open(argv[2], O_RDWR | O_CREAT, 0666);
  if (infile == -1 || outfile == -1)
    return (printf("ERREUR OPEN\n"), 1);
  if (get_vectors(infile))
    return (1);
  if (parse_scientific())
    return (1);
  close(infile);
  middle = open("scient.txt", O_RDWR);
  if (middle == -1)
    return (printf("ERREUR OPEN MIDDLE 2\n"), 1);
  while (1)
  {
    count = 0;
    write(outfile, "tr ", 3);
    while (count < 3)
    {
      str = get_next_line(middle);
      if (!str)
        return (close(middle), close(outfile), unlink("middle.txt"), unlink("scient.txt"), printf("EOF\n"), 0);
      if (is_empty(str))
       {free(str);continue;}
//      str = delete_end_spaces(str);
      line = ft_replace(str, ' ', ',');
      if (!line)
        return (1);
      write(outfile, line, strlen(line) - 1);
      write(outfile, " ", 1);
      count++;
      free(str);  free(line);
    }
    write(outfile, "247,184,207\n", strlen("247,184,207") + 1);
  }
  return (0);
}
