/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_readline.h                                       :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#ifndef TS_READLINE_H
# define TS_READLINE_H

typedef struct s_ts_hist	t_ts_hist;

char		*ts_readline(char *prompt, t_ts_hist *history);

int			ts_add_hist(char *line, t_ts_hist *history);
void		ts_free_hist(t_ts_hist *history);
t_ts_hist	*ts_init_hist(void);

#endif
