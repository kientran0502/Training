#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>

int main()
{
    mqd_t mesage_queue = mq_open("/order_queue", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, NULL);
    if(mesage_queue == (mqd_t)-1)
    {
        printf("mq_open failed\n");
        return 1;
    }

    mq_send(mesage_queue, "101", 4, 1);
    printf("Sent message: 101\n");
    mq_send(mesage_queue, "102", 4, 1);
    printf("Sent message: 102\n");
    mq_send(mesage_queue, "103", 4, 1);
    printf("Sent message: 103\n");

    return 0;
}