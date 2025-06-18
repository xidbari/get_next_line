/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@42wolfsburg.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:09:28 by aosman            #+#    #+#             */
/*   Updated: 2025/06/18 21:36:43 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Declare your function prototype
char *get_next_line(int fd);

int main(void)
{
	int fd;
	char *line;

	// Test 1: Read from a file
	fd = open("testfile.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	printf("Reading lines from testfile.txt:\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("LINE: %s", line);
		free(line);
	}
	close(fd);

	// Test 2: Read from stdin (uncomment to test)
	/*
	printf("\nEnter lines (Ctrl+D to end):\n");
	while ((line = get_next_line(0)) != NULL)
	{
		printf("STDIN: %s", line);
		free(line);
	}
	*/

	return 0;
}