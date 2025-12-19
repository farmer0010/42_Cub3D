/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:12:05 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/14 11:57:41 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	unsigned char		*d_num;
	const unsigned char	*s_num;

	d_num = (unsigned char *)dest;
	s_num = (const unsigned char *)src;
	if (d_num < s_num || d_num > s_num + num)
	{
		while (num--)
			*d_num++ = *s_num++;
	}
	else
	{
		d_num += num;
		s_num += num;
		while (num--)
			*(--d_num) = *(--s_num);
	}
	return (dest);
}
