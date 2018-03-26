int count_chars(char *line)
{
  int count_chars = 0;

  while (line[count_chars] != '\0')
    count_chars++;

  return count_chars;
}
