#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    struct mq_attr msq_rx_attr;
    unsigned int priority = 1;
    mqd_t mesage_queue_rx = mq_open("/order_queue", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, NULL);
    if(mesage_queue_rx == (mqd_t)-1)
    {
        printf("mq_open failed\n");
        return 1;
    }

    if(mq_getattr(mesage_queue_rx, &msq_rx_attr) == -1)
    {
        printf("mq_getattr failed\n");
        return 1;
    }

    void *buffer = malloc(msq_rx_attr.mq_msgsize * msq_rx_attr.mq_maxmsg);
    mq_receive(mesage_queue_rx, buffer, msq_rx_attr.mq_msgsize , &priority);
    printf("Received message: %s\n", (char *)buffer);

    mq_receive(mesage_queue_rx, buffer, msq_rx_attr.mq_msgsize, &priority);
    printf("Received message: %s\n", (char *)buffer);

    mq_receive(mesage_queue_rx, buffer, msq_rx_attr.mq_msgsize, &priority);
    printf("Received message: %s\n", (char *)buffer);

    mq_close(mesage_queue_rx);
    mq_unlink("/order_queue");

    return 0;
}