/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:23:55 by tchalifo          #+#    #+#             */
/*   Updated: 2021/11/11 10:47:55 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int	fd;
	char	*result;

	fd = open("test.txt", O_RDONLY);
	result = get_next_line(fd);
	printf("Final returned value = '%s'\n", result);
	printf("'%s'\n", NULL);
	// while (result != NULL)
	// {
	//	printf("Final returned value = %s\n", result);
	// 	result = get_next_line(fd);
	// }
	return (0);
}

char	*get_line(int fd)
{
	char static	*remaining;
	char		*line;
	char		*buffer;
	int			read_output;

	read_output = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	while (!ft_strchr(remaining, '\n') && read_output != 0)
	{
		read_output = read(fd, buffer, BUFFER_SIZE);
		buffer[read_output] = '\0';
		if (read_output == -1)
		{
			free(buffer);
			return (NULL);
		}
		printf("GET_LINE: buffer before memjoin = '%s'\n", buffer);
		printf("GET_LINE: remaining before memjoin = '%s'\n", remaining);
		printf("GET_LINE: read_output = %d\n", read_output);
		remaining = ft_memjoin(remaining, buffer);
		printf("GET_LINE: remaining after memjoin = '%s'\n", remaining);
		printf("GET_LINE: buffer after memjoin = '%s'\n", buffer);

	}
	free(buffer);
	buffer = NULL;
	line = crop_front(remaining);
	remaining = crop_end(remaining);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_line(fd);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/* Verifier si j ai quelque chose dans la static remaining provenant d un ancien appel de gnl.
 * Si il y a joindre line avec remaining j uste qu au premier \n puis faire egaler le restant a la static remaining.
 * 1. Copier la droite du \n le restant du buffer dans une static remaining et ce sans malloc.
 * 2. copier la gauche du \n la ligne vers la variable line incluant le \n.
 */

char	*crop_front(char *src)
{
	int		lenght;
	int		i;
	char	*dst;
	//printf(" CROP_FRONT remaining = %s\n", remaining);
	lenght = 0;
	i = 0;
	while (src[lenght] && src[lenght] != '\n')
		lenght++;
	dst = malloc(sizeof(char) * (lenght + 1));
	while (i <= lenght)
	{
		dst[i] = src[i];
		i++;
	}
	//printf(" CROP_FRONT line = %s\n", line);
	dst[i] = '\0';
	return (dst);
}

char	*crop_end(char *src)
{
	//char	*dst;
	size_t	i;

	i = 0;
	if (*src != '\0')
	{
		while (src[i] && src[i] != '\n')
			i++;
		if (src[i] == '\n')
			return (ft_strdup(&src[i] + 1));
		// if (src[i] == '\n')
		// {
		// 	length = ft_strlen(&src[i + 1]);
		// 	dst = malloc(sizeof(char) * (length + 1));
		// 	if (!dst)
		// 		return (NULL);
		// 	ft_strlcpy(dst, &src[i + 1], length + 1);
		else
			return (ft_strdup(src));
	}
		// else
		// {
		// 	length = ft_strlen(src);
		// 	dst = malloc(sizeof(char) * (length + 1));
		// 	if (!dst)
		// 		return (NULL);
		// 	ft_strlcpy (dst, src, (length + 1));
		// }
		// free(src);
		// src = NULL;
	free((void*)src);
	return (NULL);
}

char	*ft_memjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	s1_length;
	size_t	s2_length;
	printf("MEMJOIN: s1 = %s\n", s1);
	printf("MEMJOIN: s2 = %s\n", s2);
	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	else if (s1 && s2)
	{
		s3 = malloc((s1_length + s2_length) + 1);
		if (!s3)
			return (NULL);
		ft_strlcpy(s3, s1, (s1_length + 1));
		ft_strlcat(s3, s2, ((s1_length + s2_length) + 1));
		free((void*)s1);
		printf("MEMJOIN: test\n");
		printf("MEMJOIN: s3 after cat = '%s'\n", s3);
		return (s3);
	}
	return (NULL);
}



/*
void	memdel(void *mem)
{
	if (mem != NULL)
	{
		free(mem);
		mem = NULL;
	}
}
*/
