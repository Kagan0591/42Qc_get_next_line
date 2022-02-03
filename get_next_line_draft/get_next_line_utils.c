/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 09:09:58 by tchalifo          #+#    #+#             */
/*   Updated: 2021/11/04 15:17:53 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	s1_lenght;
	size_t	s2_lenght;

	if (!s1)
		return ((char *) s2);
	if (!s2)
		return ((char *) s1);
	if (s1 || s2)
	{
		s1_lenght = ft_strlen(s1);
		s2_lenght = ft_strlen(s2);
		s3 = malloc((s1_lenght + s2_lenght) + 1);
		if (!s3)
			return (NULL);
		ft_strlcpy(s3, s1, (s1_lenght + 1));
		free((void *) s1);
		ft_strlcat(s3, s2, ((s1_lenght + s2_lenght) + 1));
		return (s3);
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	i_s1;

	i_s1 = ft_strlen(s1) + 1;
	s2 = malloc(sizeof(*s2) * i_s1);
	if (!s2)
		return (0);
	ft_strlcpy(s2, s1, i_s1);
	return (s2);
}

size_t	ft_strlen(const char *s)
{
	size_t	i_s;

	i_s = 0;
	while (s[i_s] != '\0')
		i_s++;
	return (i_s);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclenght;
	srclenght = ft_strlen(src);
	if (dstsize == 0)
		return (srclenght);
	while (*src && dstsize-- > 1)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return (srclenght);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i_dest;
	size_t	i_src;
	size_t	destlenght;
	size_t	srclenght;

	i_dest = 0;
	i_src = 0;
	destlenght = ft_strlen(dst);
	srclenght = ft_strlen((char *)src);
	if (dstsize < destlenght)
		return (dstsize + srclenght);
	while (dst[i_dest])
		i_dest++;
	while (src[i_src] && (i_dest + 1) < dstsize)
	{
		dst[i_dest] = src[i_src];
		i_dest++;
		i_src++;
	}
	dst[i_dest] = '\0';
	return (destlenght + srclenght);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char )c)
			return ((char *)s + 1);
		s++;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = (ft_strlen(s) - start);
	dst = (char *) malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (0);
	ft_strlcpy(dst, ((char *)s + start), (len + 1));
	return (dst);
}
