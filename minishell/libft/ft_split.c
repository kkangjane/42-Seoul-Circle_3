/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:25:40 by seonggek          #+#    #+#             */
/*   Updated: 2023/12/07 11:42:53 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_of_total(char const *s, char c)
{
	size_t	size;
	int		flag;

	size = 0;
	flag = 1;
	while (*s != 0)
	{
		if (*s == c)
			flag = 1;
		else if (flag == 1)
		{
			size++;
			flag = 0;
		}
		s++;
	}
	return (size);
}

static char	**portion_word(char **splited, char const *s, char c)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (*s != 0)
	{
		if (*s != c)
			size++;
		if ((*s == c || *(s + 1) == '\0') && size != 0)
		{
			splited[i] = (char *)malloc(sizeof(char) * (size + 1));
			if (!splited[i])
			{
				while (i > 0)
					free(splited[--i]);
				free(splited);
				return (0);
			}
			splited[i++][size] = 0;
			size = 0;
		}
		s++;
	}
	return (splited);
}

static char	**word_save(char **splited, char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s != 0)
	{
		if (*s != c)
			splited[i][j++] = *s;
		else if (j != 0)
		{
			i++;
			j = 0;
		}
		s++;
	}
	return (splited);
}

char	**ft_split(char const *s, char c)
{
	char	**splited;
	size_t	size;

	if (!s)
		return (0);
	size = size_of_total(s, c);
	splited = (char **)malloc(sizeof(char *) * (size + 1));
	if (!splited)
		return (0);
	splited[size] = 0;
	splited = portion_word(splited, s, c);
	if (!splited)
		return (0);
	splited = word_save(splited, s, c);
	return (splited);
}
