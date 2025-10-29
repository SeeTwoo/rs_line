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

#include "tshoo_line_struct.h"

t_tshoo_hist	*tshoo_init_hist(void) {
	t_tshoo_hist	*new;

	new = malloc(sizeof(t_tshoo_hist));
	if (!new)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->line = strdup("");
	if (!new->line)
		return (free(new), NULL);
	return (new);
}
