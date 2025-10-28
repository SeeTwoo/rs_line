/* ************************************************************************** */
/*                                                                            */
/*                                                         :::     ::::::::   */
/*   raw_mode_handling.c                                 :+:     :+:    :+:   */
/*                                                     +:+ +:+        +:+     */
/*   By: walter </var/spool/mail/walter>             +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*   Created:                                           #+#    #+#            */
/*   Uptated:                                          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct termios		t_settings;

void	disable_raw_mode(t_settings *original) {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, original);
}

void	enable_raw_mode(t_settings *original) {
	t_settings	raw;

	tcgetattr(STDIN_FILENO, original);
	raw = *original;
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	raw.c_iflag &= ~(ICRNL | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
