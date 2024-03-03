/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moo_environ.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:40:20 by seonggek          #+#    #+#             */
/*   Updated: 2024/01/18 16:49:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOO_ENVIRON_H
# define MOO_ENVIRON_H

# include "moo_basic.h"
# include "../libft/libft.h"
# include <stdlib.h>

/* find_env.c */
char	*exploit_value(char *key);
int		find_env_idx(char *key);
char	*exploit_key(int idx);
char	*join_key_value(char *key, char *value);
char	**make_fake_environ(void);

/* control_env.c */
void	copy_env(char **original);
int		change_env(char *key, char *value);
int		add_env(char *key, char *value);
void	remove_env(int idx);
int		update_exit_code(int code);

#endif