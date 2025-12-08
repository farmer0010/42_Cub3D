/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:56:29 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/21 12:02:01 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip(const char *str, int *i, int *error)
{
	int	sign;
	int	signcnt;

	sign = 1;
	signcnt = 0;
	while (str[*i] == 32 || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	while (str[*i] == 43 || str[*i] == 45)
	{
		if (str[*i] == 45)
			sign *= -1;
		signcnt++;
		if (signcnt > 1)
		{
			*error = 1;
			return (0);
		}
		(*i)++;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	int	n;
	int	i;
	int	sign;
	int	error;

	i = 0;
	error = 0;
	sign = skip(str, &i, &error);
	if (error)
		return (0);
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}
