enum read_state { NON_WORD, WORD };

int count_words(char *line)
{
  int count_words = 0;
  enum read_state currently_reading = NON_WORD;

  while (*line)
  {
    if (*line == ' ' || *line == '\t' || *line == '\n')
    {
      currently_reading = NON_WORD;
    } else if (currently_reading == NON_WORD)
    {
      currently_reading = WORD;
      ++count_words;
    }
    ++line;
  }

  return count_words;
}
