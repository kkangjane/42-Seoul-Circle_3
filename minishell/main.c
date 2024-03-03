/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:27:40 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/19 12:43:42 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_cmd		*cmd_lst;

	init_moo(argv, argc, envp);
	str = readline("\033[0;34mmoo > \033[0m\033[s");
	while (str)
	{
		if (*str)
		{
			add_history(str);
			cmd_lst = parsing(str);
			if (cmd_lst)
				process(cmd_lst);
			cmd_free(&cmd_lst);
		}
		free(str);
		set_signal_main();
		str = readline("\033[0;34mmoo > \033[0m\033[s");
	}
	arr_free(&g_env);
	printf("\033[uexit\n");
	return (0);
}
