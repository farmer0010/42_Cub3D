/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:43:21 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/16 13:38:16 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*str1;
	int		n;

	if (! src)
		return (NULL);
	n = 0;
	str1 = (char *)malloc((ft_strlen(src) +1) * sizeof(char));
	if (! str1)
		return (NULL);
	while (src[n])
	{
		str1[n] = src[n];
		n++;
	}
	str1[n] = '\0';
	return (str1);
}
