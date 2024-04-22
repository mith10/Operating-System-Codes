#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t pid;
  int status;

  // Fork a child process
  pid = fork();

  if (pid < 0)
  { // Error occurred
    perror("Fork failed");
    exit(1);
  }
  else if (pid == 0)
  {
    // Child process
    // Execute cp command
    execl("/bin/cp", "cp", "source.txt", "destination.txt", NULL);
    perror("exec failed");
    exit(1);
  }
  else
  { 
    // Parent process
    // Wait for the child process to complete
    
    wait(&status);
    printf("cp command executed successfully.\n");

    // Fork another child process
    pid = fork();

    if (pid < 0)
    { // Error occurred
      perror("Fork failed");
      exit(1);
    }
    else if (pid == 0)
    { // Child process
      // Execute grep command
      execl("/bin/grep", "grep", "keyword", "file.txt", NULL);
      perror("exec failed");
      exit(1);
    }
    else
    { // Parent process
      // Wait for the child process to complete
      wait(&status);
      printf("grep command executed successfully.\n");
    }
  }

  // Print process IDs
  printf("Parent process ID: %d\n", getpid());
  printf("Child process ID: %d\n", pid);

  // Exit the program
  exit(0);
}
