/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:21:01 by ekim              #+#    #+#             */
/*   Updated: 2020/11/06 14:26:20 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define MAX_FD 1025

char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		newline_check(char *str);
int		get_next_line(int fd, char **line);

#endif
