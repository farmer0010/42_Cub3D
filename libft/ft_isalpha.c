/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:44:21 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/14 11:56:10 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
int main(void) {
    char ch = '3';
    if (ft_isalpha(ch)) {
        printf("%c는 알파벳입니다.\n", ch);
    } else {
        printf("%c는 알파벳이 아닙니다.\n", ch);
    }
    return 0;
}
*/
