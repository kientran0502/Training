#include<stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

int share_data = 0;

int main()
{
    int shm_fd = shm_open("/shm-example", O_RDWR, S_IRUSR | S_IWUSR);
    if(shm_fd == -1) 
    {
        perror("shm_open");
        return 1;
    }

    void *addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(addr == MAP_FAILED)
    {
        printf("mmap failed\n");
        return 1;
    }

    memcpy(&share_data, addr, sizeof(int));
    printf("Value read from shared memory: %d\n", share_data);
    share_data = 200;
    memcpy(addr, &share_data, sizeof(int));
    close(shm_fd);
    return 0;
}



