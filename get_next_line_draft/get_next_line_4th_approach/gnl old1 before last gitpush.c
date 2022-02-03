/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl old1 before last gitpush.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:23:55 by tchalifo          #+#    #+#             */
/*   Updated: 2021/11/09 18:11:44 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
char	*get_line(fd)
{
	char static	*remaining;
	char		*line;
	char		*buffer;
	int			read_output;
	static int	count = 0;

	read_output = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	buffer[BUFFER_SIZE + 1] = '\0';
	count++;
	printf("count = %d\n", count);
	//printf("remaining at start = %s\n", remaining);
	while (!ft_strchr(buffer, '\n') && read_output != 0)
	{
		read_output = read(fd, buffer, BUFFER_SIZE);
		printf("buffer_out = %d\n", read_output);
		if (read_output == -1)
		{
			free(buffer);
			return (0);
		}
		remaining = ft_strjoin(remaining, buffer);
		printf("remaining after joint = %s\n", remaining);
	}
	free(buffer);
	line = crop_front(remaining);
	remaining = crop_end(remaining);
	printf("GET_LINE AFTER CROP_FRONT && CROP_END,, line = %s\n", line);
	printf("GET_LINE AFTER CROP_FRONT && CROP_END,, remaining = %s\n", remaining);

	return (line);
}

char	*get_next_line(fd)
{
	char	*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	line = get_line(fd);
	return (line);
}

/* Verifier si j ai quelque chose dans la static remaining provenant d un ancien appel de gnl.
 * Si il y a joindre line avec remaining j uste qu au premier \n puis faire egaler le restant a la static remaining.
 * 1. Copier la droite du \n le restant du buffer dans une static remaining et ce sans malloc.
 * 2. copier la gauche du \n la ligne vers la variable line incluant le \n.
 */

char	*crop_front(char *remaining)
{
	int		lenght;
	int		i;
	char	*line;
	printf(" CROP_FRONT remaining = %s\n", remaining);
	lenght = 0;
	i = 0;
	while (remaining[lenght] && remaining[lenght] != '\n')
		lenght++;
	line = malloc(sizeof(char) * (lenght + 1));
	while (i <= lenght)
	{
		line[i] = remaining[i];
		i++;
	}
	printf(" CROP_FRONT line = %s\n", line);
	line[i] = '\0';
	return (line);
}

char	*crop_end(char *src)
{
	char	*dst;
	size_t	length;
	size_t	i;

	i = 0;
	while (src[i] && src[i] != '\n')
		i++;
	printf("CROP_END value of i = %zu\n", i);
	length = ft_strlen(&src[i + 1]);
	dst = malloc(sizeof(char) * (length + 1));
	ft_strlcpy(dst, &src[i + 1], length + 1);
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	s1_length;
	size_t	s2_length;

	if (!s1)
	{
		s2_length = ft_strlen(s2);
		s3 = malloc(sizeof(char) * (s2_length + 1));
		//printf("STRJOIN_IF!S1,, value of s2 = %s\n", s2);
		//printf("STRJOIN_IF!S1,, %zu\n", s2_length);
		ft_strlcpy(s3, s2, (s2_length + 1));
		//printf("STRJOIN_IF!S1,, value of s3 = %s\n", s3);
		return (s3);
	}
	if (!s2)
	{
		s1_length = ft_strlen(s2);
		s3 = malloc(sizeof(char) * (s1_length + 1));
		ft_strlcpy(s3, s1, s1_length);
		return (s3);
	}
	if (s1 || s2)
	{
		s1_length = ft_strlen(s1);
		s2_length = ft_strlen(s2);
		s3 = malloc((s1_length + s2_length) + 1);
		if (!s3)
			return (NULL);
		ft_strlcpy(s3, s1, (s1_length + 1));
		ft_strlcat(s3, s2, ((s1_length + s2_length) + 1));
		return (s3);
	}
	return (NULL);
}

int	main(void)
{
	int	fd;
	int	i;

	i = 0;
	fd = open("test.txt", O_RDONLY);
	while (i != 8)
	{
		printf("Final returned value = %s\n", get_next_line(fd));
		i++;
	}
	return (0);
}
