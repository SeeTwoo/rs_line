/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   ts_readline.c                                       :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: seetwoo <marvin@42students.fr>              +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "tshoo_line_struct.h"

typedef struct termios		t_settings;

void	enable_raw_mode(t_settings *original);
void	disable_raw_mode(t_settings *original);
void	tshoo_completion(t_rl *rl);

static void	replace_line(t_rl *rl, t_tshoo_hist **history, char cmd) {
	int	temp;

	if (*history == NULL)
		return ;
	if (cmd == 'A' && (*history)->prev)
		*history = (*history)->prev;
	else if (cmd == 'B' && (*history)->next)
		*history = (*history)->next;
	else
		return ;
	if (!(*history)->line)
		return ;
	temp = rl->i;
	while (temp > 0) {
		write(2, "\x1b[D", 3);
		temp--;
	}
	dprintf(2, "\x1b[%ldP", strlen(rl->line));
	memcpy(rl->line, (*history)->line, strlen((*history)->line) + 1);
	rl->len = strlen((*history)->line);
	rl->i = rl->len;
	write(2, rl->line, strlen(rl->line));
}

static void	fill_command(char *cmd_buf, char *cmd) {
	int	i;

	i = 0;
	while (1) {
		if (read(0, &cmd_buf[i], 1) == 0)
			continue ;
		if (isalpha(cmd_buf[i]))
			break ;
		i++;
	}
	*cmd = cmd_buf[i];
	i++;
	cmd_buf[i] = '\0';
}

static void	cursor_forward(t_rl *rl) {
	if (rl->i >= rl->len)
		return ;
	rl->i++;
	write(2, "\x1b[C", 3);
}

static void	cursor_backward(t_rl *rl) {
	if (rl->i <= 0)
		return ;
	rl->i--;
	write(2, "\x1b[D", 3);
}

static void	arrow_handling(t_rl *rl, t_tshoo_hist **history) {
	char	cmd_buf[32];
	char	cmd;

	fill_command(cmd_buf, &cmd);
	if (cmd == 'A' || cmd == 'B')
		replace_line(rl, history, cmd);
	else if (cmd == 'C')
		cursor_forward(rl);
	else if (cmd == 'D')
		cursor_backward(rl);
}

static void	fill_line(t_rl *rl, char c) {
	char	*dest;
	char	*src;
	int		temp;

	dest = rl->line + rl->i + 1;
	src = rl->line + rl->i;
	memmove(dest, src, strlen(src) + 1);
	src[0] = c;
	write(2, src, strlen(src));
	temp = rl->len;
	while (temp > rl->i) {
		write(2, "\x1b[D", 3);
		temp--;
	}
	rl->i++;
	rl->len++;
}

static void	backspace_handling(t_rl *rl) {
	if (rl->i <= 0)
		return ;
	rl->i--;
	rl->line[rl->i] = '\0';
	rl->len--;
	write(2, "\x08\x1b[K", 4);
}

char	*tshoo_line(char const *prompt, t_tshoo_hist *history) {
	t_settings	original;
	char		c;
	t_rl		rl;

	enable_raw_mode(&original);
	write(2, prompt, strlen(prompt));
	rl.i = 0;
	rl.len = 0;
	rl.line[0] = '\0';
	while (1) {
		if (read(0, &c, 1) == 0)
			continue ;
		else if (c == '\r' || rl.len == 1023)
			break ;
		else if (c == '\x7f')
			backspace_handling(&rl);
		else if (c == '\x1b')
			arrow_handling(&rl, &history);
		else if (c == '\t')
			tshoo_completion(&rl);
		else
			fill_line(&rl, c);
	}
	rl.line[rl.len] = '\0';
	write(2, "\r\v", 2);
	disable_raw_mode(&original);
	return (strdup(rl.line));
}
