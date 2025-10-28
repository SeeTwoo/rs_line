/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_readline_struct.h                                :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#ifndef TS_READLINE_STRUCT_H
# define TS_READLINE_STRUCT_H

typedef struct s_rl	t_rl;

struct s_rl {
	char	line[1024];
	int		i;
	int		len;
};

#endif
