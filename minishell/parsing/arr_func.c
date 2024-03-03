/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:53:22 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_parsing.h"

static void	arr_dup(char **dst, char **src);

static void	arr_dup(char **dst, char **src)
{
	int	idx;

	idx = 0;
	while (src && src[idx])
	{
		dst[idx] = src[idx];
		idx++;
	}
	dst[idx] = 0;
}

void	arr_add(char ***arr, char *add)
{
	int		idx;
	char	**new;

	idx = 0;
	if (add == 0)
		return ;
	while (*arr && (*arr)[idx])
		idx++;
	new = (char **)malloc(sizeof(char *) * (idx + 2));
	if (!new)
	{
		free(add);
		arr_free(arr);
		parsing_error_exit("minishell");
	}
	arr_dup(new, *arr);
	new[idx++] = add;
	new[idx] = 0;
	free(*arr);
	*arr = new;
	return ;
}

void	*arr_free(char ***arr)
{
	int		idx;

	if (!*arr)
		return (0);
	idx = 0;
	while ((*arr)[idx])
		free((*arr)[idx++]);
	free(*arr);
	*arr = 0;
	return (0);
}
