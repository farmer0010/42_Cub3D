/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:08:37 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/18 13:09:25 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90) || (c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
int main(void)
{
    // 테스트 문자 정의
    char ch1 = ':';  // 특수문자
    char ch2 = 'a';  // 소문자
    char ch3 = '3';  // 숫자
    char ch4 = ' ';  // 공백

    // ft_isalnum 함수 테스트
    printf("ch1 ('%c') is alphanumeric: %d\n", ch1, ft_isalnum(ch1));
    printf("ch2 ('%c') is alphanumeric: %d\n", ch2, ft_isalnum(ch2));
    printf("ch3 ('%c') is alphanumeric: %d\n", ch3, ft_isalnum(ch3));
    printf("ch4 ('%c') is alphanumeric: %d\n", ch4, ft_isalnum(ch4));

    return 0;
}
*/
