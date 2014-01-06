/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:24:19 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 10:24:19 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char			*ft_strlcat_do(char *s_dst, char *s_src, size_t s_size);

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	final_dst_len;
	size_t	s_size;
	char	*s_src;
	char	*s_dst;

	if (!dst || !src)
		return (0);
	s_size = size;
	s_dst = dst;
	s_src = (char *)src;
	while (s_size != 0 && *s_dst != '\0')
	{
		s_size--;
		s_dst++;
	}
	final_dst_len = s_dst - dst;
	s_size = size - final_dst_len;
	if (s_size == 0)
		return (final_dst_len + ft_strlen(src));
	return (final_dst_len + (ft_strlcat_do(s_dst, s_src, s_size) - src));
}

char			*ft_strlcat_do(char *s_dst, char *s_src, size_t s_size)
{
	while (*s_src != '\0' && s_size != 1)
	{
		*s_dst = *s_src;
		s_size--;
		s_src++;
		s_dst++;
	}
	*s_dst = '\0';
	while (*s_src != '\0')
		s_src++;
	return (s_src);
}
