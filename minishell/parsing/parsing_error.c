/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:14:45 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_parsing.h"
#include "../_includes/moo_environ.h"

int	print_token_error(int attr)
{
	write(2, "moo: ", 5);
	write(2, "syntax error near unexpected token", 34);
	if (attr == PIPE)
		write(2, "`|\'", 3);
	else if (attr == (HEREDOC | REDIRECT | INPUT))
		write(2, "`<<\'", 4);
	else if (attr == (REDIRECT | INPUT))
		write(2, "`<\'", 3);
	else if (attr == (REDIRECT | OUTPUT | APPEND))
		write(2, "`>>\'", 4);
	else if (attr == (REDIRECT | OUTPUT))
		write(2, "`>\'", 3);
	else
		write(2, "`newline\'", 9);
	write(2, "\n", 1);
	if (token_error_update_exit() < 0)
		parsing_error_exit("parsing");
	return (-1);
}

int	token_error_check(int attr, char **str)
{
	int	check;

	check = 0;
	if (attr == 0)
		return (0);
	while (ft_isspace(**str) == 1)
		(*str)++;
	if (**str == 0)
		return (print_token_error(0));
	check = getattr(str, 0);
	if (attr == PIPE && check == PIPE)
		return (print_token_error(PIPE));
	else if (attr != PIPE && check)
		return (print_token_error(check));
	return (0);
}

void	parsing_error_exit(const char *string)
{
	extern int	errno;

	perror(string);
	exit(errno);
}

int	token_error_update_exit(void)
{
	char	*c;
	int		idx;

	idx = find_env_idx("?");
	c = ft_itoa(258);
	if (!c)
		return (-1);
	if (idx < 0)
		add_env("?", c);
	else
		change_env("?", c);
	free(c);
	return (0);
}
