#include <mqueue.h>
#include <fcntl.h>     // O_NONBLOCK
#include <unistd.h>
#include <stdlib.h>
#include "tlpi_hdr.h"

static void usageError(const char *progName)
{
    fprintf(stderr, "Usage: %s [-n] name\n", progName);
    fprintf(stderr, "    -n    Use O_NONBLOCK flag\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int flags = O_RDONLY;
    int opt;
    mqd_t mqd;
    unsigned int prio;
    void *buffer;
    struct mq_attr attr;
    ssize_t numRead;

    /* Parse command-line options */
    while ((opt = getopt(argc, argv, "n")) != -1)
    {
        switch (opt)
        {
            case 'n':
                flags |= O_NONBLOCK;
                break;

            default:
                usageError(argv[0]);
        }
    }

    /* Queue name is required */
    if (optind >= argc)
        usageError(argv[0]);

    /* Open message queue */
    mqd = mq_open(argv[optind], flags);
    if (mqd == (mqd_t)-1)
        errExit("mq_open");

    /* Get queue attributes */
    if (mq_getattr(mqd, &attr) == -1)
        errExit("mq_getattr");

    /* Allocate buffer large enough for the maximum message size */
    buffer = malloc(attr.mq_msgsize);
    if (buffer == NULL)
        errExit("malloc");

    /* Receive one message */
    numRead = mq_receive(mqd,
                         buffer,
                         attr.mq_msgsize,
                         &prio);
    if (numRead == -1)
        errExit("mq_receive");

    printf("Read %ld bytes; priority = %u\n",
           (long)numRead,
           prio);

    /* Print the received message */
    if (write(STDOUT_FILENO, buffer, numRead) == -1)
        errExit("write");

    if (write(STDOUT_FILENO, "\n", 1) == -1)
        errExit("write");

    free(buffer);

    exit(EXIT_SUCCESS);
}