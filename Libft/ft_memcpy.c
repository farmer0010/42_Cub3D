/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:34:04 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/16 14:51:32 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	unsigned char		*d_byte;
	const unsigned char	*s_byte;

	d_byte = (unsigned char *)dest;
	s_byte = (const unsigned char *)src;
	while (count--)
	{
		*d_byte = *s_byte;
		d_byte++;
		s_byte++;
	}
	return (dest);
}
