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

#ifndef TSHOO_LINE_H 
# define TSHOO_LINE_H 

typedef struct s_tshoo_hist	t_tshoo_hist;

char		*tshoo_line(char *prompt, t_tshoo_hist *history);

int			tshoo_add_hist(char *line, t_tshoo_hist *history);
void		tshoo_free_hist(t_tshoo_hist *history);
t_tshoo_hist	*tshoo_init_hist(void);

#endif
