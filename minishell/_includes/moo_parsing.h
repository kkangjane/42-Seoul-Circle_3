/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moo_parsing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:32:41 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOO_PARSING_H
# define MOO_PARSING_H

# include "moo_basic.h"
# include <stdlib.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>

/* arr_func.c */
void		arr_add(char ***arr, char *add);
void		*arr_free(char ***arr);

/* buf_strcut_func.c */
void		*buf_free(t_buf **buf);
void		char_to_buf(t_buf **buf, char save);

/* cmd_strcut_func.c */
void		*cmd_free(t_cmd **cmd);
void		cmd_add(t_cmd **cmd, t_token **token, t_buf **buf, int *attr);

/* env_parsing.c */
void		parse_dollar(t_buf **buf, char **str);
void		parse_dollar2(t_buf **buf, char **str, t_token **token);

/* parsing_error.c */
int			print_token_error(int attr);
int			token_error_check(int attr, char **str);
void		parsing_error_exit(const char *string);
int			token_error_update_exit(void);

/* file_lst_func.c */
void		*file_free(t_file_lst **file);
void		file_add(t_file_lst **head, char *filename, int io_flag);

/* token_struct_func.c */
void		token_add(t_buf **buf, int *attr, t_token **token);
void		*token_free(t_token **token);

/* parser.c */
t_cmd		*parsing(char *str);

/* attr_func.c */
int			getattr(char **str, int flag);
int			pipe_cmd_add(t_cmd **cmd, t_token **token, t_buf **buf, int *attr);
int			check_attr_and_add_token(char **str, t_token **token, t_buf **buf);

#endif