/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:17:17 by seonggek          #+#    #+#             */
/*   Updated: 2023/12/07 11:42:48 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*mapped_lst;
	t_list	*new;
	void	*convert;

	mapped_lst = 0;
	while (lst)
	{
		tmp = lst -> next;
		convert = f(lst -> content);
		new = ft_lstnew(convert);
		if (!new)
		{
			del(convert);
			ft_lstclear(&mapped_lst, del);
			return (0);
		}
		ft_lstadd_back(&mapped_lst, new);
		lst = tmp;
	}
	return (mapped_lst);
}
