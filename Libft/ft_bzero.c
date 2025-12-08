/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:55:41 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/14 15:13:23 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *str, size_t size)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (size--)
	{
		*ptr = 0;
		ptr++;
	}
}
