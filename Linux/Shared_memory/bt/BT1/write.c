#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

int share_data = 100;

int main()
{
    int shm_fd = shm_open("/shm-example", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if(shm_fd == -1) 
    {
        printf("shm_open failed\n");
        return 1;
    }

    if(ftruncate(shm_fd, sizeof(int)) == -1) 
    {
        printf("ftruncate failed\n");
        return 1;
    }

    void *addr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if(addr == MAP_FAILED) 
    {
        printf("mmap failed\n");
        return 1;
    }
    
    memcpy(addr, &share_data, sizeof(int));
    
    sleep(5); 
    
    memcpy(&share_data, addr, sizeof(int));

    printf("Value read from shared memory after sleep: %d\n", share_data);

    shm_unlink("/shm-example");

    close(shm_fd);

    return 0;
}