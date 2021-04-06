/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:19:20 by heryu             #+#    #+#             */
/*   Updated: 2021/02/18 15:19:48 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *dest, char *src, int d_free, int s_free)
{
	char	*tmp;

	tmp = ft_strjoin(dest, src);
	if (d_free == 1)
		free(dest);
	if (s_free == 1)
		free(src);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}
