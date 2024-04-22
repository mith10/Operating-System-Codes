#include <iostream>
#include <unistd.h>
#include <cstring> 

using namespace std;

int main() {

    int fd1[2], fd2[2];
    
    char str1[] = "Hello Child Process from Parent Process";
    char str2[] = "Hello Parent Process from Child Process";

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("Pipe Failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid > 0) {
       // Parent Process
        char buffer[100];
        close(fd1[0]); // Close reading end of first pipe
        write(fd1[1], str1, strlen(str1) + 1); // Include null terminator when writing
        close(fd1[1]); // Close writing end of first pipe

        close(fd2[1]); // Close writing end of second pipe
        
        ssize_t nbytes = read(fd2[0], buffer, sizeof(buffer)); // Read from second pipe
        if (nbytes >= 0) {
            buffer[nbytes] = '\0'; // Null terminate the received string
            cout << buffer << endl; // Write read message to stdout
        }
        
        close(fd2[0]); // Close reading end of second pipe
        
    } else { // Child Process
        
        close(fd1[1]); // Close writing end of first pipe
        char buffer[100];
       
        ssize_t nbytes = read(fd1[0], buffer, sizeof(buffer)); // Read from first pipe
        if (nbytes >= 0) {
            buffer[nbytes] = '\0'; // Null terminate the received string
            cout << buffer << endl; // Write read message to stdout
        }
        close(fd1[0]); // Close reading end of first pipe

        close(fd2[0]); // Close reading end of second pipe
        write(fd2[1], str2, strlen(str2) + 1); // Include null terminator when writing
        close(fd2[1]); // Close writing end of second pipe
    }

    return 0;
}
