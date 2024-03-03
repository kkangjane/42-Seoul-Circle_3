/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:01:50 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/17 17:01:20 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (*(str1 + i) != '\0' && *(str2 + i) != '\0')
	{
		if (*(str1 + i) != *(str2 + i))
			return ((int)*(str1 + i) - (int)*(str2 + i));
		i++;
	}
	return ((int)*(str1 + i) - (int)*(str2 + i));
}
