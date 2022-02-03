/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_1st_approach.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 09:05:22 by tchalifo          #+#    #+#             */
/*   Updated: 2021/10/25 17:04:21 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Calling your function get_next_line in a loop will then allow you to read the text
 * available on the file descriptor one line at a time until the end of it.
 * Appeler la fonction get_next_line dans un loop, ce qui me permettra
 * de lire le fichier texte depuis le file descriptor une ligne a la fois jusqu'a la fin
 *
 * READ
 * Fonction read tentera de lire count nombre d octet depuis le fd dans un buffer commencant a *buf
 *  A chaque fois que read est utilie , il garde sa position en lecture, donc si je lis 10 chars une premiere fois,
 * a la seconde fois il continura de lire depuis la 10 ieme position
 *
 * get_line read la ligne au complet et
 * */

// #include "get_next_line.h"

char	*get_line(int fd)
{
	char		*buffer1;
	char		*line;
	static char *keep_the_rest;
	size_t		line_lenght;
	int			bytes_read;
	int	nbr_of_while;

	nbr_of_while = 0;
	buffer1 = malloc(sizeof(char) * (BUFFER_SIZE));
	if (!buffer1)
		return (0);
	bytes_read = 1;
	line_lenght = 0;
	if (keep_the_rest)
		line = ft_substr(keep_the_rest, 0, BUFFER_SIZE);
	if (!line) // Si line ne contient aucune valeur, utiliser keep_the_rest
		line = strdup(buffer1);
	while (bytes_read != 0)
	{
		nbr_of_while++;
		bytes_read = read(fd, buffer1, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer1);
			return (0);
		}
		buffer1 = ft_strchr_and_destroy(buffer1, &keep_the_rest, '\n');
		line = ft_strjoin(line, buffer1);
		line_lenght = ft_strlen(line);
		ft_memset(buffer1, '\0', ft_strlen(buffer1));
		if (line[line_lenght - 1] == '\n')
			break;
	}
	free(buffer1);
	buffer1 = NULL;
	return (line);
}

char	*ft_strchr_and_destroy(const char *s, char **keep, int c)
{
	size_t	i_s;

	i_s = 0;
	while (s[i_s])
	{
		if (s[i_s] == (char)c)
		{
			*keep = ft_substr(s, i_s + 1, ft_strlen(&s[i_s] + 1)); // Copie les elements de la chaine apres le /n dans la chaine keep
			ft_memset((void *)&s[i_s + 1], '\0', ft_strlen(&s[i_s + 1])); // met a zero les elements de la chaine apres le /n
			return ((char *)s); // retourne la chaine tronquer
		}
		i_s++;
	}
	return ((char *)s);
}

char	*get_next_line(int fd)
{
	char	*tmp_buf;

	tmp_buf = get_line(fd);
	return (tmp_buf);
}


#include <fcntl.h>

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);

	line = get_next_line(fd);
return (0);
}



