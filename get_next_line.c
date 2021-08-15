#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

void	join_line(char **line, char *string, int *r);

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;
	int		r;

	buffer = ft_malloc(BUFFER_SIZE + 1, 1);
	r = read(fd, buffer, 0);
	line = NULL;
	if (r >= 0 && buffer)
	{
		r = 1;
		while (r > 0)
		{
			r = read(fd, buffer, BUFFER_SIZE);
			buffer[r] = 0;
			join_line(&line, buffer, &r);
		}
	}
	if (line && !*line)
	{
		free(line);
		line = NULL;
	}
	free(buffer);
	return (line);
}

void	join_line(char **line, char *str, int *r)
{
	static char	*store;
	char		*tmp;

	if (store)
	{
		*line = ft_strdup(store);
		free(store);
		store = NULL;
	}
	else if (!*line)
		*line = ft_strdup("");
	if (*str && *r > 0)
	{
		tmp = *line;
		*line = ft_strjoin(tmp, str);
		free(tmp);
	}
	tmp = ft_strchr(*line, '\n');
	if (tmp)
	{
		store = ft_strdup(tmp + 1);
		*(++tmp) = '\0';
		*r = 0;
	}
}
