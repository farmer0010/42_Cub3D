/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:33:33 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/16 13:34:46 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	n;

	if (! *small)
		return ((char *)big);
	while (*big && len)
	{
		if (*big == *small)
		{
			n = 0;
			while (small[n] && big[n] == small[n] && (n + 1) <= len)
				n++;
			if (!small[n])
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (0);
}
