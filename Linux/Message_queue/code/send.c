#include <mqueue.h>
#include <fcntl.h>     
#include <stdio.h>

static void usageError(const char *progName)
{
    fprintf(stderr, "Usage: %s [-n] name msg [prio]\n", progName);
    fprintf(stderr, "    -n    Use O_NONBLOCK flag\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int flags = O_WRONLY;
    int opt;
    mqd_t mqd;
    unsigned int prio;

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

    /* Need at least: queue_name and message */
    if (optind + 1 >= argc)
        usageError(argv[0]);

    /* Open message queue */
    mqd = mq_open(argv[optind], flags);
    if (mqd == (mqd_t)-1)
        errExit("mq_open");

    /* Priority is optional (default = 0) */
    if (argc > optind + 2)
        prio = atoi(argv[optind + 2]);
    else
        prio = 0;

    /* Send message */
    if (mq_send(mqd,
                argv[optind + 1],
                strlen(argv[optind + 1]),
                prio) == -1)
    {
        errExit("mq_send");
    }

    exit(EXIT_SUCCESS);
}


