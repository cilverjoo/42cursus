/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 02:13:35 by heryu             #+#    #+#             */
/*   Updated: 2021/02/16 21:15:13 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define RET_ERROR -1
# define RET_EOF 0
# define RET_SUCCESS 1

int					get_next_line(int fd, char **line);
void				ft_strncpy(char *dst, char *src, size_t size);
char				*ft_strncat_and_free(char *str, char *src, size_t size);
char				*ft_my_strchr(char *str, char chr);
#endif
