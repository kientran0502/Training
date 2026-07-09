#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int filepipe_parent_to_child[2] = {0};
    int filepipe_child_to_parent[2] = {0};

    if (pipe(filepipe_parent_to_child) == -1) 
    {
        perror("pipe");
        return 1;
    }

    if (pipe(filepipe_child_to_parent) == -1) 
    {
        perror("pipe");
        return 1;
    }

    switch (fork())
    {
        case -1:
            printf("Fork failed\n");
        break;
        case 0: // child
            char buff1[10] = {0};
            close(filepipe_parent_to_child[1]);
            close(filepipe_child_to_parent[0]);
            while (1)
            {
                if(read(filepipe_parent_to_child[0], buff1, 5) > 0)
                {
                    printf("Child: read from parent: %s\n", buff1);
                    write(filepipe_child_to_parent[1], "Pong", 5);
                    printf("Child: writing Pong to parent\n");
                }
            }
        break;
        default: //parent
            char buff2[10] = {0};
            close(filepipe_parent_to_child[0]);
            close(filepipe_child_to_parent[1]);
            printf("Parent: writing Ping to child\n");
            write(filepipe_parent_to_child[1], "Ping", 5);
            while (1)
            {
                if(read(filepipe_child_to_parent[0], buff2, 5) > 0)
                {
                    printf("Parent: read from child: %s\n", buff2);
                    write(filepipe_parent_to_child[1], "Ping", 5);
                    printf("Parent: writing Ping to child\n");
                }
            }
        break;
    }
    wait(NULL);
    return 0;

}