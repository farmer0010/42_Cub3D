/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:55:15 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/14 11:56:30 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
int main()
{
	char ch='a';
	if(ft_isdigit(ch))
		printf("숫자입니다");
	else
		printf("숫자가 아닙니다");
}
*/
