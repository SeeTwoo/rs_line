/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   free_history.c                                      :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "tshoo_line_struct.h"

void	tshoo_free_hist(t_tshoo_hist *history) {
	t_tshoo_hist	*temp;

	while (history) {
		temp = history;
		history = history->prev;
		free(temp->line);
		free(temp);
	}
}
