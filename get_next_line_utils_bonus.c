/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:54:17 by tchalifo          #+#    #+#             */
/*   Updated: 2021/11/15 10:42:06 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclenght;

	i = 0;
	srclenght = ft_strlen(src);
	if (dstsize == 0)
		return (srclenght);
	while (src[i] != '\0' && dstsize-- > 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
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

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	s1_length;

	s1_length = ft_strlen(s1) + 1;
	s2 = malloc(sizeof(*s2) * s1_length);
	if (!s2)
		return (0);
	ft_strlcpy(s2, s1, s1_length);
	return (s2);
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
