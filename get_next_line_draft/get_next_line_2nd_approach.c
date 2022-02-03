/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_2nd_approach.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:30:53 by tchalifo          #+#    #+#             */
/*   Updated: 2021/10/29 17:56:57 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* get_line est utilise pour retrouver BUFFER_SIZE nombres de charactere
 * dans un fichier puis les ecrires dans la variable char *buffer.
 * Ensuite, il joint le buffer a la chaine line. Puis, il s assurera de copier
 * dans la chaine remaining le reste du buffer */

char	*get_next_line(int fd)
{
	char	*line;
	static char	*remaining; // Ce qui restera du buffer apres le retour de ligne

	if (remaining)												// Verifie si il y a un reste de l ancient buffer
		line = ft_strjoin(remaining, get_line(fd, &remaining));
	else							// Si il y a, la chaine remaining sera copier vers une nouvelle chaine line
		line = get_line(fd, &remaining);
	return (line);
}


char	*get_line(int fd, char **remaining)
{
	char		*buffer;		// Le tempon ou est stocke les characteres provenant du fichier
	char		*line;			// La chaine de charactere destine a contenire toute la ligne
	int			read_output;	// Le nombre de characteres ecrit dans le buffer, retourne par la fonction read

	buffer = malloc(sizeof(char) * (BUFFER_SIZE));					// Alloue l espace au buffer selon le BUFFER_SIZE
	read_output = 1;												// Initialise la variable read_output a 1
	while (read_output != 0 && !ft_strchr(line, '\n'))				// Tant que la variable read-output n egale pas 0 (read retourne 0 quand il atteint END_OF_FILE)
	{
		read_output = read(fd, buffer, BUFFER_SIZE);
		if (read_output == -1)										// Verifie si la variable read-output est egale a -1 (read retourne -1 quand il ya a erreur)
		{
			free(buffer);
			return (0);												// Si vrai, la fonction retourne 0
		}
		buffer = ft_cropfront(buffer, '\n');
		if (!line)													// Verifie si la chaine line existe (Elle ne devrait pas si il sagit de la premiere iteration et/ou si remaining ne contenais rien)
			line = ft_strldup(buffer, ft_strlen(buffer));								// Si elle n existe pas, les valeurs de buffer y seront copiees
		else
		line = ft_strjoin(line, buffer);							// La chaine buffer est jointe a la chaine line pour y ajouter sont contenue a la suite de cette derniere
		//buffer = ft_strchr_and_destroy(buffer, &remaining, '\n');	// Dans cette fonction, \n sera recherche dans la string, si il est trouve, tou ce qui se trouve a droite de celui-ci sera copier dans la variable remaining et ecraser par des zeros dans la chaine buffer. Ensuite elle retournera la chaine buffer.
	}
	*remaining = ft_cropend(buffer, 'n');
	free(buffer);
	return (line);
}

/* Si le buffer contient un /n */

// malloc une nouvelle string qui acceuillera les char de la droite du \n
char	*ft_cropend(char *s1, char c)
{
	char	*s2;
	while (*s1 != c)
		s1++;
	s2 = ft_strldup(s1 + 1, ft_strlen(s1 + 1));
	return (s2);
}

// malloc une nouvelle string qui acceuillera les char de la gauche du \n l incluant
char	*ft_cropfront(char *s1, char c)
{
	char	*s2;
	size_t	count;

	count = 0;
	while (s1[count] != '\0' && s1[count] != c)
		count++;
	s2 = ft_strldup(s1, count + 1);
	return (s2);
}

char	*ft_strldup(const char *s1, size_t len)
{
	char	*s2;
	size_t	i_s1;

	i_s1 = ft_strlen(s1) + 1;
	if (i_s1 > len)
		i_s1 = len;
	s2 = malloc(sizeof(*s2) * i_s1);
	if (!s2)
		return (0);
	ft_strlcpy(s2, s1, i_s1);
	return (s2);
}

#include <fcntl.h>
int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	get_next_line(fd);
	return (0);
}




/*
char	*ft_strchr_and_destroy(const char *str, char **keep, int c)
{
	size_t	i_str;

	i_str = 0;
	while (str[i_str])
	{
		if (str[i_str] == (char)c)
		{
			*keep = ft_substr(str, i_str + 1, ft_strlen(&str[i_str] + 1)); // Copie les elements de la chaine apres le /n dans la chaine keep
			printf("%s\n", *keep);
			ft_memset((void *)&str[i_str + 1], '\0', ft_strlen(&str[i_str + 1])); // met a zero les elements de la chaine apres le /n
			printf("%s\n", str);
			return ((char *)str); // retourne la chaine tronquer
		}
		i_str++;
	}
	return ((char *)str);
}
*/
/* get_next_line est utilise pour retrouver BUFFER_SIZE nombres de charactere
 * dans un fichier puis les ecrires dans la variable char *buffer. */
/*
char	*get_next_line(int fd)
{
	char	*line;

	line = get_line(fd);
	return (line);
}

#include <fcntl.h>

int	main(void)
{
	int	fd;

	fd = open("test.txt", O_RDONLY);
	get_next_line(fd);
	return (0);
}
*/
