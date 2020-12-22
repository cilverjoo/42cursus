/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:55:00 by ekim              #+#    #+#             */
/*   Updated: 2020/12/16 22:17:51 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define MAX_FD 1025
# define BUFFER_SIZE 30

char	*ft_gnl_strdup(char *str);
char	*ft_gnl_strjoin(char *s1, char *s2);
int		newline_check(char *str);
int		get_next_line(int fd, char **line);

#endif
