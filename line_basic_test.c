#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes/tshoo_line.h"

#ifndef PROMPT
# define PROMPT "\x1b[31m > \x1b[0m"
#endif

/*
void	print_history(t_ts_hist *history) {
	if (!history || !history->prev)
		return ;
	history = history->prev;
	while (history) {
		printf("%s\n", history->line);
		history = history->prev;
	}
}
*/

int	main(void) {
	char			*line;
	t_tshoo_hist	*history;

	history = tshoo_init_hist();
	while (1) {
		line = tshoo_line(PROMPT, history);
		if (!line)
			return (1);
		if (strcmp(line, "exit") == 0)
			break ;
		tshoo_add_hist(line, history);
		free(line);
	}
	tshoo_free_hist(history);
	free(line);
	return (0);
}
