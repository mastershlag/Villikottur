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

int		check_process(char *name, int pid)
{
	DIR* dir;
	struct dirent* ent;
	char* endptr;
	char buf[512];
	if ((name == NULL || strlen(name) == 0) && pid < 0)
		return (1);
	if (!(dir = opendir("/proc"))) {
		perror("can't open /proc");
		return (-1);
	}
	while ((ent = readdir(dir)) != NULL)
	{
		if (pid > 0 && atoi(ent->d_name) == pid)
			return (0);
		long lpid = strtol(ent->d_name, &endptr, 10);
		if (*endptr != '\0')
			continue;
		snprintf(buf, sizeof(buf), "/proc/%ld/stat", lpid);
		int fd = open(buf, O_RDONLY);
		if (fd >= 0)
		{
			int size;
			if ((size = read(fd, buf, 512)) > 0)
			{
				buf[size - 1] = '\0';
				if (strstr(buf, name) != NULL)
					return (0);
			}
			close(fd);
		}
	}
	return (1);
}