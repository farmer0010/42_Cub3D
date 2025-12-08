/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:42:56 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/15 14:59:13 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int value, size_t size)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (size--)
	{
		*ptr = (unsigned char)value;
		ptr++;
	}
	return (str);
}
