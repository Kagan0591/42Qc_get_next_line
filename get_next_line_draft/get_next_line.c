/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:03:55 by tchalifo          #+#    #+#             */
/*   Updated: 2021/11/05 11:14:23 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

/* get_line est utilise pour retrouver BUFFER_SIZE nombres de charactere
 * dans un fichier puis les ecrires dans la variable char *buffer.
 * Ensuite, il joint le buffer a la chaine line. Puis, il s assurera de copier
 * dans la chaine remaining le reste du buffer */

char	*get_next_line(int fd)
{
	char	*line;
	static char	*remaining;

	if (remaining)
		line = ft_strjoin(remaining, get_line(fd, &remaining));
	else
		line = get_line(fd, &remaining);
	if (ft_strchr(line, '\n') != 0)
		remaining = ft_strldup(ft_strchr(line, '\n'), ft_strlen(ft_strchr(line, '\n')));
	//printf("Remaining = %s\n", remaining);
	//printf("line value = %s\n", line);
	ft_cropfront(&line, '\n');
	//printf("remaining value = %s\n", remaining);
	return (line);
}

void	ft_cropfront(char **s1, char c)
{
	//printf("test");
	char	*s2;
	size_t	count;
	//printf("test");
	count = 0;
	while (*s1[count] != '\0' && *s1[count] != c)
		count++;
	//printf("count = %zu\n", count);
	s2 = ft_strldup(*s1, count + 1);
	free(*s1);
	*s1 = s2;
}

char	*get_line(int fd, char **remaining)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*line;
	int		read_output;

	read_output = 1;
	line = NULL;
	while (!ft_strchr(line, '\n'))
	{
		read_output = read(fd, buffer, BUFFER_SIZE);
		//printf("%d\n", read_output);
		if (read_output <= 0)
		{
			*remaining = ft_substr(*remaining, count_char(*remaining, '\n'), ft_strlen(*remaining) - count_char(*remaining, '\n'));
			return (0);
		}
		buffer[read_output] = '\0';
		if (!line)
			line = ft_strldup(buffer, ft_strlen(buffer));
		else
			line = ft_strjoin(line, buffer);
	}
	return (line);
}

size_t	count_char(const char *s, const char c)
{
	size_t	count_char;
	size_t	i_s;

	count_char = 0;
	i_s = 0;
	while (s[i_s] != '\0')
	{
		if ((char)s[i_s] == c)
			return (count_char + 1);
		while ((char)s[i_s] != c && s[i_s] != '\0')
		{
			count_char++;
			i_s++;
		}
	}
	return (count_char);
}

char	*ft_strldup(const char *s1, size_t len)
{
	char	*s2;
	size_t	i_s1;

	i_s1 = ft_strlen(s1);
	if (i_s1 > len)
		i_s1 = len;
	s2 = malloc(sizeof(char) * i_s1 + 1);
	if (!s2)
		return (0);
	ft_strlcpy(s2, s1, i_s1 + 1);
	return (s2);
}

#include <fcntl.h>
int	main(void)
{
	int	fd;
	char	*display;
	int i;
	int j;

	i = 0;
	j = 0;
	fd = open("test.txt", O_RDONLY);
	while (i != 4)
	{
		display = get_next_line(fd);
		while (display[j] != '\0')
		{
			write(1, &display[j], 1);
			j++;
		}
		j = 0;
		i++;
		free(display);
	}
	close(fd);
	return (0);
}
