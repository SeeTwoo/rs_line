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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "ts_readline_struct.h"

#ifndef DELIM
# define DELIM "<>&| "
#endif

typedef struct s_comp	t_comp;

struct s_comp {
	char	*word_start;
	char	*word_end;
	char	*last_slash;
	char	*base;
	size_t	base_len;
	char	*filler;
};

int	is_delim(char c) {
	return ( c == '>' || c == '<' || c == '|' || c == '&' || c == ' ');
}

char	*find_match(t_comp *comp) {
	char			*dir_name;
	DIR				*dir;
	struct dirent	*entry;

	if (comp->last_slash)
		dir_name = strndup(comp->word_start, comp->last_slash + 1 - comp->word_start);
	else
		dir_name = strdup(".");
	if (!dir_name)
		return (NULL);
	dir = opendir(dir_name);
	free(dir_name);
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry) {
		if (strncmp(comp->base, entry->d_name, comp->base_len) == 0)
			return (entry->d_name + comp->base_len);
		entry = readdir(dir);
	}
	return (NULL);
}

void	init_comp(t_comp *comp, t_rl *rl) {
	int	temp = rl->i + strcspn(rl->line + rl->i, DELIM);

	comp->word_end = rl->line + temp;
	comp->last_slash = NULL;
	while (temp > 0 && !is_delim(rl->line[temp])) {
		if (!comp->last_slash && rl->line[temp] == '/')
			comp->last_slash = rl->line + temp;
		temp--;
	}
	comp->word_start = rl->line + temp;
	comp->base = comp->last_slash ? comp->last_slash + 1 : comp->word_start;
	comp->base_len = comp->word_end - comp->base;
	comp->filler = find_match(comp);
}

void	replace(t_rl *rl, t_comp *comp) {
	size_t	filler_len = strlen(comp->filler);

	memmove(rl->line + rl->i + filler_len, rl->line + rl->i, strlen(rl->line + rl->i) + 1);
	memcpy(rl->line + rl->i, comp->filler, filler_len);
	rl->i += filler_len;
	rl->len += filler_len;
	write(2, comp->filler, filler_len);
}

void	ts_completion(t_rl *rl) {
	t_comp	comp;

	init_comp(&comp, rl);
	replace(rl, &comp);
}
