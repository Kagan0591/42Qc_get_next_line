#include "get_next_line.h"

char	*get_next_line(int	fd)
{
	char	*buffer;
	char	*super_buffer;
	static char	**str;
	int	read_output;
	int i;

	read_output = 1;
	i = 0;
	if (read_output != 0)
	{
		buffer = malloc((char) * BUFFER_SIZE);
		while (read_output != 0)
		{
			read_output = read(fd, buffer, BUFFER_SIZE);
			if (super_buffer)
				super_buffer = ft_strjoin(super_buffer, buffer);
			else
				super_buffer = ft_strdup(buffer);
		}
		free(buffer);
	}
	str = ft_split(super_buffer, '\n');
	free(super_buffer);
	while (str[i] != NULL)
	{
		str[i] = str[i + 1];
	}
	return (str[0]);
}

#include <fcntl.h>

int	main(void)
{
	int	fd;
	char	*get;

	fd = open("test.txt", O_RDONLY);
	get = get_next_line(fd);
	printf("%s\n", get);
	return (0);
}
