/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:17:37 by seonggek          #+#    #+#             */
/*   Updated: 2023/12/07 11:42:37 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pnt;

	pnt = (void *)malloc(size * count);
	if (!pnt)
		return (0);
	return (ft_memset(pnt, 0, size * count));
}
