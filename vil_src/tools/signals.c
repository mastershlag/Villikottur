#include "vil.h"

static void	sig_segv_handler(int signum, siginfo_t *info, void *ptr)
{
	printf("SIG %d recieved\n", signum);
	if (signum != SIGINT)
		exit(0);
}

void		set_signal_handle(int sig)
{
	static struct 	sigaction _sigact[100];
	static int	i = 0;
	memset(&(_sigact[i]), 0, sizeof(_sigact[i]));
	_sigact[i].sa_sigaction = sig_segv_handler;
	_sigact[i].sa_flags = SA_SIGINFO;
	sigaction(sig, &_sigact[i], NULL);
	++i;
}
