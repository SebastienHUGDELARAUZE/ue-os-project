#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv) {
        int des_p[2];
        if(pipe(des_p) == -1) {
          perror("Pipe failed");
          exit(1);
        }

        if(fork() == 0)            //first fork
        {
            dup2(des_p[1], STDOUT_FILENO);         //replacing stdout with pipe write 
            close(des_p[0]);       //closing pipe read

            const char* prog1[] = { "ls", "-l", 0};
            execvp(prog1[0], prog1);
            perror("execvp of ls failed");
            exit(1);
        }

        if(fork() == 0)            //creating 2nd child
        {
            dup2(des_p[0], STDIN_FILENO);         //replacing stdin with pipe read
            close(des_p[1]);       //closing pipe write

            const char* prog2[] = { "wc", "-l", 0};
            execvp(prog2[0], prog2);
            perror("execvp of wc failed");
            exit(1);
        }

        close(des_p[0]);
        close(des_p[1]);
        wait(0);
        wait(0);
        return 0;
}