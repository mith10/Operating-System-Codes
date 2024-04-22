#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h> // Include for time function

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_reader = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_writer = PTHREAD_COND_INITIALIZER;
int readers_count = 0;
int writers_count = 0;
int resource = 0;

// Synchronized Reader function
void *sync_reader(void *arg)
{
  int reader_id = *((int *)arg);
  pthread_mutex_lock(&mutex);
  while (writers_count > 0)
  {
    printf("Reader %d is waiting because a writer is writing\n", reader_id);
    pthread_cond_wait(&cond_reader, &mutex);
  }
  readers_count++;
  pthread_mutex_unlock(&mutex);

  // Read the resource
  printf("Reader %d is reading shared resource\n", reader_id);
  sleep(1);

  pthread_mutex_lock(&mutex);
  readers_count--;
  if (readers_count == 0)
  {
    pthread_cond_signal(&cond_writer);
  }
  pthread_mutex_unlock(&mutex);

  printf("Reader %d completed reading, CS is free\n", reader_id);
  return NULL;
}

// Synchronized Writer function
void *sync_writer(void *arg)
{
  int writer_id = *((int *)arg);
  pthread_mutex_lock(&mutex);
  writers_count++;
  while (readers_count > 0)
  {
    printf("Writer %d is blocked from writing\n", writer_id);
    pthread_cond_wait(&cond_writer, &mutex);
  }
  pthread_mutex_unlock(&mutex);

  // Write to the resource
  resource = writer_id;
  printf("Writer %d is writing shared resource\n", writer_id);
  sleep(1);

  pthread_mutex_lock(&mutex);
  writers_count--;
  pthread_cond_signal(&cond_writer); // Signal waiting writers
  pthread_cond_broadcast(&cond_reader); // Signal all readers
  pthread_mutex_unlock(&mutex);

  printf("Writer %d completed writing, CS is free\n", writer_id);
  return NULL;
}


// Asynchronized Reader function
void *async_reader(void *arg)
{
  int reader_id = *((int *)arg);
  // Read the resource
  printf("Reader %d is reading shared resource\n", reader_id);
  sleep(1);
  printf("Reader %d completed reading, CS is free\n", reader_id);
  return NULL;
}

// Asynchronized Writer function
void *async_writer(void *arg)
{
  int writer_id = *((int *)arg);
  // Write to the resource
  printf("Writer %d is dangerously writing shared resource\n", writer_id);
  sleep(1);
  printf("Writer %d completed dangerously writing, CS is free\n", writer_id);
  return NULL;
}

// Run the program in synchronized mode
void runSynchronized(int numReaders, int numWriters)
{
  pthread_t readers[numReaders];
  pthread_t writers[numWriters];
  int i, reader_ids[numReaders], writer_ids[numWriters];

  for (i = 0; i < numReaders; i++)
  {
    reader_ids[i] = i + 1;
  }

  for (i = 0; i < numWriters; i++)
  {
    writer_ids[i] = i + 1;
  }

  printf("Running in synchronized mode.\n");

  // Reader-Reader (RR) case
  printf("\nReader-Reader (RR) case:\n");
  for (i = 0; i < numReaders; i++)
  {
    pthread_create(&readers[i], NULL, sync_reader, &reader_ids[i]);
  }

  for (i = 0; i < numReaders; i++)
  {
    pthread_join(readers[i], NULL);
  }

  // Reader-Writer (RW) case
  printf("\nReader-Writer (RW) case:\n");
  pthread_create(&readers[0], NULL, sync_reader, &reader_ids[0]);
  pthread_create(&writers[0], NULL, sync_writer, &writer_ids[0]);
  pthread_join(readers[0], NULL);
  pthread_join(writers[0], NULL);

  // Writer-Writer (WW) case
  printf("\nWriter-Writer (WW) case:\n");
  for (i = 0; i < numWriters; i++)
  {
    pthread_create(&writers[i], NULL, sync_writer, &writer_ids[i]);
  }

  for (i = 0; i < numWriters; i++)
  {
    pthread_join(writers[i], NULL);
  }
}

// Run the program in asynchronous mode
void runAsynchronized(int numReaders, int numWriters)
{
  pthread_t readers[numReaders];
  pthread_t writers[numWriters];
  int i, reader_ids[numReaders], writer_ids[numWriters];

  for (i = 0; i < numReaders; i++)
  {
    reader_ids[i] = i + 1;
  }

  for (i = 0; i < numWriters; i++)
  {
    writer_ids[i] = i + 1;
  }

  printf("Running in asynchronous mode.\n");

  // Reader-Reader (RR) case without synchronization
  printf("\nReader-Reader (RR) case without synchronization:\n");
  for (i = 0; i < numReaders; i++)
  {
    pthread_create(&readers[i], NULL, async_reader, &reader_ids[i]);
  }

  for (i = 0; i < numReaders; i++)
  {
    pthread_join(readers[i], NULL);
  }

  // Reader-Writer (RW) case without synchronization
  printf("\nReader-Writer (RW) case without synchronization:\n");
  pthread_create(&readers[0], NULL, async_reader, &reader_ids[0]);
  pthread_create(&writers[0], NULL, async_writer, &writer_ids[0]);
  pthread_join(readers[0], NULL);
  pthread_join(writers[0], NULL);

  // Writer-Writer (WW) case without synchronization
  printf("\nWriter-Writer (WW) case without synchronization:\n");
  for (i = 0; i < numWriters; i++)
  {
    pthread_create(&writers[i], NULL, async_writer, &writer_ids[i]);
  }

  for (i = 0; i < numWriters; i++)
  {
    pthread_join(writers[i], NULL);
  }
}

int main()
{
  int numReaders, numWriters, mode;
  printf("Enter the number of readers: ");
  scanf("%d", &numReaders);
  printf("Enter the number of writers: ");
  scanf("%d", &numWriters);

  while (true)
  {
    printf("Enter the mode (1 for synchronized, 2 for asynchronized): ");
    scanf("%d", &mode);

    if (mode == 1)
    {
      runSynchronized(numReaders, numWriters);
    }
    else if (mode == 2)
    {
      runAsynchronized(numReaders, numWriters);
    }
    else
    {
      printf("Invalid mode. Please enter 1 or 2.\n");
      return 0;
    }
  }

  return 0;
}
