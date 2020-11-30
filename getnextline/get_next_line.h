/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:55:00 by ekim              #+#    #+#             */
/*   Updated: 2020/11/06 13:38:47 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

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
