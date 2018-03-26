#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include "wc.h"

int thread_count;
sem_t *sems;
pthread_mutex_t mutex;
int total_lines;
int total_words;
int total_chars;

int main(int argc, char *argv[])
{
  pthread_t *thread_handles;
  long thread;

  pthread_mutex_init(&mutex, NULL);
  total_lines = 0;
  total_words = 0;
  total_chars = 0;

  if (argc == 1)
    thread_count = (int) sysconf(_SC_NPROCESSORS_ONLN);
  else if (argc == 2)
    thread_count = atoi(argv[1]);
  else
    usage(argv[0]);

  thread_handles =
      (pthread_t *) malloc(thread_count * sizeof(pthread_t));
  sems = (sem_t *) malloc(thread_count * sizeof(sem_t));
  sem_init(&sems[0], 0, 1);
  for (thread = 1; thread < thread_count; thread++)
    sem_init(&sems[thread], 0, 0);

  for (thread = 0; thread < thread_count; thread++)
    pthread_create(&thread_handles[thread],
                   (pthread_attr_t *) NULL, process_line,
                   (void *) thread);
  for (thread = 0; thread < thread_count; thread++)
    pthread_join(thread_handles[thread], NULL);

  printf("%d lines, %d words, %d characters\n", total_lines,
         total_words, total_chars);

  for (thread = 0; thread < thread_count; thread++)
    sem_destroy(&sems[thread]);
  free(sems);
  pthread_mutex_destroy(&mutex);
  free(thread_handles);

  return 0;
}
