#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("err");
        return 1;
    }

    pid_t pid = fork();
    
    if (pid == -1) {
        perror("err");
        return 1;
    } else if (pid == 0) {
        execl("./sequential_min_max", "sequential_min_max", argv[1], argv[2], NULL);
        perror("execl failed");
        return 1;
    } else {
        // Родительский процесс  
        int status;
        waitpid(pid, &status, 0);  // Ждем завершения дочернего процесса
        
        
    }
    
    return 0;
}