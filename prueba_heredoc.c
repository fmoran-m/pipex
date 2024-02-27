#include "pipex.h"

void	open_here_doc(char *limiter, int *pipex)
{
	int	fd;
	char *buffer;

	buffer = NULL;
	fd = open(".here_doc.txt", O_CREAT | O_RDONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		close(pipex[0]);
		close(pipex[1]);
		perror(OPEN_ERR);
		exit(1);
	}
	while(1)
	{
		ft_printf("> ");
		buffer = get_next_line(0);
		if (!ft_strncmp(buffer, limiter, ft_strlen(limiter)))
			break;
	}
	dup2(fd, 0);
}

int main(void)
{
	char limiter[5] = "betis";

	open_here_doc(limiter, NULL);
	return 0;
}
