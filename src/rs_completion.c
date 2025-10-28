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

#include "ts_readline_struct.h"

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

char	*dir_substring(char *dir, char *last_slash) {
	if (last_slash)
		return (strndup(dir, last_slash - dir + 1));
	else
		return (strdup("."));
}

char	*file_substring(char *path, char *last_slash) {
	if (last_slash)
		return (strndup(last_slash + 1, strcspn(last_slash + 1, " <>&|")));
	else
		return (strndup(path, strcspn(path, " <>&|")));
}

char	*find_match(char *to_complete, char *last_slash/*, char *replaced*/) {
	char	*dir_name = dir_substring(to_complete, last_slash);
	char	*foot = file_substring(to_complete, last_slash);
	DIR		*dir;
	struct dirent	*entry;

	if (!dir_name || !foot)
		return (free(dir_name), free(foot), NULL);
	dir = opendir(dir_name);
	free(dir_name);
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry) {
		if (strncmp(foot, entry->d_name, strlen(foot)) == 0)
			return (free(foot), entry->d_name);
		entry = readdir(dir);
	}
	free(foot);
	return (NULL);
}

void	replace(t_rl *rl, char *replaced, char *replacement) {
	size_t	len = strcspn(replaced, " <>&|");
	size_t	offset = strlen(replacement) - len;

	memmove(replaced + offset, replaced, strlen(replaced) + 1);
	memcpy(replaced, replacement, strlen(replacement));
	rl->len += offset;
	rl->i += offset;
}

void	ts_completion(t_rl *rl) {
	char	*to_complete = find_current_word(rl->line, rl->i);
	char	*last_slash = find_last_slash(to_complete);
	char	*replaced = last_slash ? last_slash + 1 : to_complete;
	char	*replacement = find_match(to_complete, last_slash/*, replaced*/);

	if (!replacement)
		return ;
	replace(rl, replaced, replacement);
	printf("%s\n", rl->line);
}
