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

#include "ts_readline.h"
#include "ts_hist.h"

void	ts_free_hist(t_ts_hist *history) {
	t_ts_hist	*temp;

	while (history) {
		temp = history;
		history = history->prev;
		free(temp->line);
		free(temp);
	}
}
