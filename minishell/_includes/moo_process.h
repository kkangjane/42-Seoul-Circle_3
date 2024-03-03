/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moo_process.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggek <seonggek@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:37:04 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/18 17:15:18 by seonggek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOO_PROCESS_H
# define MOO_PROCESS_H

# include "moo_basic.h"
# include "moo_environ.h"
# include "moo_parsing.h"
# include "moo_signals.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include <unistd.h>

/* builtin/builtin.c */
int		builtin(t_cmd *proc);
int		is_builtin(t_cmd *proc);
/* builtin/ft_pwd.c */
int		ft_pwd(t_cmd *proc);
/* builtin/ft_exit.c */
int		ft_exit(t_cmd *proc);
/* builtin/ft_env.c */
int		ft_env(t_cmd *proc);
/* builtin/ft_echo.c*/
int		ft_echo(t_cmd *proc);
/* builtin/ft_unset.c*/
int		ft_unset(t_cmd *proc);
/* builtin/ft_cd.c */
int		ft_cd(t_cmd *proc);
/* builtin/ft_export.c */
int		ft_export(t_cmd *proc);
void	print_line(char *key, int out_fd);
/* builtin/builtin_utils.c*/
int		find_fd(t_cmd *cmd, int inout);
int		all_check(char	*keys[], char *cmd);
int		close_out_fd(t_cmd *proc, int ret);
int		close_in_fd(t_cmd *proc, int ret);
int		check_dir(char *dir);

/* process/process.c */
void	process(t_cmd *cmd);
/* process/do_it.c */
int		do_execve(t_cmd *cmd, char *cmd_file);
int		do_builtin(t_cmd *cmd);
/* process/finish_cmdline.c*/
void	finish_cmdline(t_cmd *cmd);
/* process/pipe.c */
int		make_pipe(t_cmd *cmd);
int		pipe_to_fd(t_cmd *cmd);
int		file_to_fd(t_cmd *cmd);
int		close_prev(t_cmd *start, t_cmd *cmd);
/* process/open_files.c */
int		files_open_test(t_file_lst *files, t_cmd *cmd);
/* process/error.c */
int		fileopen_err(int exit);
int		cmdfile_error(t_cmd *cmd);

/* heredoc/heredoc.c */
int		check_heredoc(t_cmd *cmd);
void	heredoc(char *str, char *file_name);
/* heredoc/heredoc_utils.c */
char	*make_file_name(t_cmd *cmd, int *file_idx);
void	heredoc_per_cmdline(t_cmd *cmd, t_file_lst **files);

#endif