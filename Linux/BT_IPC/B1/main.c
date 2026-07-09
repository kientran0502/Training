#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#define TRANSFER_ORDER_PAPER_SIZE       4096

uint8_t transfer_order_paper[TRANSFER_ORDER_PAPER_SIZE];
char buffer[32];
int pipe_fd[2];

int transfer_order_init(void);

int main()
{
    transfer_order_init();

    
        printf("[Order] Read line order.txt: %s", buffer);
        pipe(pipe_fd);
        switch (fork())
        {
            case -1:
                printf("Fork failed\n");
                break;
            case 0: // Child process
                char food[32] = {0};
                int position = 0;
                close(pipe_fd[1]); // Close write end
                while(1)
                {
                    read(pipe_fd[0], food, sizeof(food));
                    printf("[Receipt] Received from child: %s", food);
                    transfer_order_write(food, position, strlen(food) + 1);
                    position += strlen(food) + 1;
                    if(position >= TRANSFER_ORDER_PAPER_SIZE)
                    {
                        
                    }
                }
                break;
            default: // Parent process
                FILE *file = fopen("order.txt", "r");
                if (file == NULL)
                {
                    printf("Failed to open file\n");
                    return 1;
                }
                close(pipe_fd[0]); // Close read end

                while (fgets(buffer, sizeof(buffer), file) != NULL)
                {
                    write(pipe_fd[1], buffer, strlen(buffer) + 1);
                }
                wait(NULL); // Wait for child to finish
                break;
        }

    fclose(file);
    return 0;
}

int transfer_order_init(void)
{
    int transfer_order_paper_fd = shm_open("/shm-transfer-order", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (transfer_order_paper == -1)
    {
        printf("shm_open failed\n");
        return 1;
    }

    ftruncate(transfer_order_paper_fd, TRANSFER_ORDER_PAPER_SIZE);

    void *addr = mmap(NULL, TRANSFER_ORDER_PAPER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, transfer_order_paper_fd, (off_t)position);
    if (addr == MAP_FAILED)
    {
        printf("mmap failed\n");
        return 1;
    }
    return 0; // Return 0 for success
}

int head = 0, tail = 0;

int transfer_order_write(char *food, int position, int length)
{
    he
    memcpy(transfer_order_paper + position, food, strlen(food) + 1); 
    return 0; // Return 0 for success
}

int transfer_order_read(char *food, int position, int length)
{
    memcpy(food, transfer_order_paper + position, strlen(transfer_order_paper + position) + 1);
    return 0; // Return 0 for success
}