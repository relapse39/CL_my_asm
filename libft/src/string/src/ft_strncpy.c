/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelehov <dmelehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 18:44:22 by dmelehov          #+#    #+#             */
/*   Updated: 2018/01/05 13:44:22 by dmelehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *res;

	res = dst;
	while (*src != '\0' && len > 0)
	{
		*(dst++) = *(src++);
		len--;
	}
	while (len-- > 0)
		*(dst++) = '\0';
	return (res);
}
