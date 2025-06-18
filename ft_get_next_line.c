/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aosman <aosman@42wolfsburg.de>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:08:24 by aosman            #+#    #+#             */
/*   Updated: 2025/06/18 21:09:11 by aosman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

static size_t	ft_strlen(const char *s)
{
	size_t i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}

static char	*ft_strdup(const char *s)
{
	size_t	len = ft_strlen(s);
	char	*dup = malloc(len + 1);
	size_t	i = 0;

	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1 = ft_strlen(s1);
	size_t	len2 = ft_strlen(s2);
	char	*res = malloc(len1 + len2 + 1);
	size_t	i = 0, j = 0;

	if (!res)
		return (NULL);
	while (i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	while (j < len2)
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

static char	*extract_line(char **stash)
{
	char	*line;
	char	*tmp;
	size_t	len = 0;

	if (!*stash || !**stash)
		return (NULL);
	while ((*stash)[len] && (*stash)[len] != '\n')
		len++;
	if ((*stash)[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		line[i] = (*stash)[i];
	line[len] = '\0';
	if ((*stash)[len])
		tmp = ft_strdup(*stash + len);
	else
		tmp = NULL;
	free(*stash);
	*stash = tmp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!ft_strchr(stash, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		if (bytes == 0)
			break;
		buffer[bytes] = '\0';
		if (!stash)
			stash = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(stash, buffer);
			free(stash);
			stash = tmp;
		}
	}
	return (extract_line(&stash));
}