#include "codexion.h"

void    dongle_initializer(int n_coders, t_dongle *dongles)
{
    int i;
    t_dongle    *curr;

    i = 0;
    while (i < n_coders)
    {
        curr->available = 0;
        curr->last_release = 0;
        curr->d_mutex = pthread_mutex_init(curr->d_mutex, NULL);
        curr->d_cond = pthread_cond_init(curr->d_cond, NULL);
        dongles[i] = *curr;
        i++;
    }
}

void    coder_initializer(int n_coders, t_coder *coders, t_compiler *compiler)
{
    int i;
    t_coder *curr;

    i = 0;
    while (i < n_coders)
    {
        curr->id = i + 1;
        curr->last_compile = 0;
        curr->compiler = compiler;
        i++;
    }
    // assigne_dongle()
}

void    compiler_initializer(t_compiler *compiler, char **av)
{
    compiler->n_coders = atoi(av[0]);
    compiler->t_compile = atoi(av[1]);
    compiler->t_burnout = atoi(av[2]);
    compiler->t_debug = atoi(av[3]);
    compiler->t_refactor = atoi(av[4]);
    compiler->n_compiles = atoi(av[5]);
    compiler->d_cooldown = atoi(av[6]);
    compiler->scheduler = av[7];
    compiler->stop_flag = 0;
    compiler->dongles = (t_dongle *)malloc(sizeof(t_dongle) * (size_t)(compiler->n_coders));
    compiler->dongles = memset(compiler->dongles, '0', sizeof(compiler->dongles));
    compiler->coders = (t_coder *)malloc(sizeof(t_coder) * (size_t)(compiler->n_coders));
    compiler->coders = memset(compiler->coders, '0', sizeof(compiler->coders));
    

}
