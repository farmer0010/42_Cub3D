/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:18:01 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/16 11:37:39 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destl;
	size_t	srcl;
	size_t	i;
	size_t	j;

	destl = 0;
	srcl = 0;
	i = 0;
	while (src[srcl])
		srcl++;
	while (dest[destl])
		destl++;
	j = destl;
	if (size == 0 || size <= destl)
		return (srcl + size);
	while (i < size - destl - 1 && src[i])
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (destl + srcl);
}
