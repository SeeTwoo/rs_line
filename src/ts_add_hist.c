/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_add_hist.c                                       :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ts_readline.h"
#include "ts_hist.h"

t_ts_hist	*new_hist_node(char *line, t_ts_hist *prev, t_ts_hist *next) {
	t_ts_hist	*new;

	new = malloc(sizeof(t_ts_hist));
	if (!new)
		return (NULL);
	new->prev = prev;
	new->next = next;
	new->line = strdup(line);
	if (!new->line)
		return (free(new), NULL);
	return (new);
}

int	ts_add_hist(char *line, t_ts_hist *history) {
	history->prev = new_hist_node(line, history->prev, history);
	if (!history->prev)
		dprintf(2, "Couldn't add the line [ %s ] to the history, malloc failed\n", line);
	if (history->prev->prev)
		history->prev->prev->next = history->prev;
	return (0);
}
