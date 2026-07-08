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

    mq_send(mesage_queue, "Order 1", 7, 1);

    return 0;
}