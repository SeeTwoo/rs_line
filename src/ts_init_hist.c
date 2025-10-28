/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_init_hist.c                                      :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "ts_readline.h"
#include "ts_hist.h"

t_ts_hist	*ts_init_hist(void) {
	t_ts_hist	*new;

	new = malloc(sizeof(t_ts_hist));
	if (!new)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->line = strdup("");
	if (!new->line)
		return (free(new), NULL);
	return (new);
}
