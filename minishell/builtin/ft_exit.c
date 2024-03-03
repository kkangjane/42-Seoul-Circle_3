/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:30:25 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/21 18:50:51 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_includes/moo_process.h"

static int	check_exit_code(char **cmd);
static int	real_exit(t_cmd *cmd);
static int	numeric_check(char *s, int i, int sign, char **cmd);

int	ft_exit(t_cmd *proc)
{
	long long	code;

	if (proc->next == 0 && proc->idx == 0)
		return (real_exit(proc));
	if (proc->cmd[1] == 0)
		return (close_out_fd(proc, 0));
	code = check_exit_code(&proc->cmd[1]);
	if (code > 0)
		return (close_out_fd(proc, code));
	code = ft_atol(proc->cmd[1]);
	while (code < 0)
		code += 256;
	return (close_out_fd(proc, code % 256));
}

static int	check_exit_code(char **cmd)
{
	char	*s;
	int		i;
	int		sign;

	s = cmd[0];
	i = -1;
	sign = 1;
	while (ft_isspace((*s)))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		i++;
	}
	return (numeric_check(s, i, sign, cmd));
}

static int	numeric_check(char *s, int i, int sign, char **cmd)
{
	while (s[++i])
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (print_error("exit", s, "numeric argument required\n", 255));
	if ((i > 19 + (sign < 0)) || (sign == 1 && i == 19
			&& ft_strncmp(&s[0], "9223372036854775807", 19) > 0))
		return (print_error("exit", s, "numeric argument required\n", 255));
	else if (sign == -1
		&& ft_strncmp(&s[1], "9223372036854775808", 19) > 0)
		return (print_error("exit", s, "numeric argument required\n", 255));
	if (cmd[1] != 0)
		return (print_error("exit", 0, "too many arguments\n", 1));
	return (0);
}

static int	real_exit(t_cmd *cmd)
{
	long long	code;

	printf("exit\n");
	if (cmd->cmd[1] == 0)
		exit(0);
	code = check_exit_code(&cmd->cmd[1]);
	if (code == 255)
		exit(255);
	else if (code == 1)
		return (1);
	code = ft_atol(cmd->cmd[1]);
	code = code % 256;
	if (code < 0)
		code += 256;
	exit(code);
	return (0);
}
