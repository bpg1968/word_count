#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include "wc.h"

extern int thread_count;
extern sem_t *sems;
extern pthread_mutex_t mutex;
extern int total_lines;
extern int total_words;
extern int total_chars;

void *process_line(void *rank)
{
  long my_rank = (long) rank;
  int next = (my_rank + 1) % thread_count;
  char *fg_rv;
  char my_line[MAX];
  int chars_in_line;
  int words_in_line;

  sem_wait(&sems[my_rank]);
  fg_rv = fgets(my_line, MAX, stdin);
  sem_post(&sems[next]);

  while (fg_rv != NULL)
  {
    chars_in_line = count_chars(my_line);
    words_in_line = count_words(my_line);

    pthread_mutex_lock(&mutex);
    ++total_lines;
    total_words += words_in_line;
    total_chars += chars_in_line;
    pthread_mutex_unlock(&mutex);

    sem_wait(&sems[my_rank]);
    fg_rv = fgets(my_line, MAX, stdin);
    sem_post(&sems[next]);
  }

  return NULL;
}
