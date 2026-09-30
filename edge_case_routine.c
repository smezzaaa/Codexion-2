#include "codexion.h"

void *one_coder_routine(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;
    while (!coder->compiler->burnout_flag)
    {
        pthread_cond_wait(&coder->compiler->dongles[0]->d_cond,
                            &coder->compiler->dongles[0]->d_mutex);
    }
    return (NULL);
}