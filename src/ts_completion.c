/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_completion.c                                     :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "ts_readline_structs.h"

int	is_sep(char c) {
	return (
		c == '>' ||
		c == '<' ||
		c == '|' ||
		c == '&' || 
		c == ' '
	);
}

char	*find_current_word(char *line, int i) {
	while (i > 0 && !is_sep(line[i]))
		i--;
	return (line + i);
}

char	*find_last_slash(char *word) {
	char	*last_slash = NULL;

	while (*word && !is_sep(*word)) {
		if (*word == '/')
			last_slash = word;
		word++;
	}
	return (last_slash);
}

char	*find_match(char *to_complete, char *last_slash, char *replaced) {
	
}

void	ts_completion(t_rl *rl) {
	char	*to_complete = find_current_word(rl->line, rl->i);
	char	*last_slash = find_last_slash(to_complete);
	char	*replaced = last_slash ? last_slash + 1 : to_comlete;
	char	*replacement = find_match(to_complete, last_slash, replaced);

	replace(t_rl, replaced, replacement);
}
