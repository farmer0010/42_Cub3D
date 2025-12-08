/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42gyeongsa      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:24:16 by juyoukim          #+#    #+#             */
/*   Updated: 2025/05/16 11:05:20 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*free_line(char **ptr);
size_t	gnl_strlen(const char *str);
char	*gnl_strchr(const char *str, int c);
char	*gnl_strjoin(char *s1, char *s2);
char	*get_line(char *str);
char	*save_remain(char *str);
char	*read_stack(int fd, char *stack);

#endif
