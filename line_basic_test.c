#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes/ts_readline.h"
#include "includes/ts_hist.h"

#ifndef PROMPT
# define PROMPT "\x1b[31m > \x1b[0m"
#endif

void	print_history(t_ts_hist *history) {
	if (!history || !history->prev)
		return ;
	history = history->prev;
	while (history) {
		printf("%s\n", history->line);
		history = history->prev;
	}
}

int	main(void) {
	char		*line;
	t_ts_hist	*history;

	history = ts_init_hist();
	while (1) {
		line = ts_readline(PROMPT, history);
		if (!line)
			return (1);
		if (strcmp(line, "exit") == 0)
			break ;
		ts_add_hist(line, history);
		print_history(history);
		free(line);
	}
	ts_free_hist(history);
	free(line);
	return (0);
}
