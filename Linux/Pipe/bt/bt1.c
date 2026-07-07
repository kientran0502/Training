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
            perror("fork");
        break;
        case 0: // child
            char buff1[10];
            close(filepipe_parent_to_child[1]);
            close(filepipe_child_to_parent[0]);
            while(read(filepipe_parent_to_child[0], buff1, 1) == 0){}
            printf("Child: read from parent: %c\n", buff1[0]);
            write(filepipe_child_to_parent[1], (char[]){'B'}, 1);
            printf("Child: writing B to parent\n");
            _exit(0);
        break;
        default: //parent
            char buff2[10];
            close(filepipe_parent_to_child[0]);
            close(filepipe_child_to_parent[1]);
            printf("Parent: writing A to child\n");
            write(filepipe_parent_to_child[1], (char[]){'A'}, 1);
            while(read(filepipe_child_to_parent[0], buff2, 1) == 0){}
            printf("Parent: read from child: %c\n", buff2[0]);
        break;
    }
    wait(NULL);
    return 0;

}