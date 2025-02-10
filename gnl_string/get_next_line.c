/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:35:18 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/10 23:20:36 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_store(int fd, char *store, char *buffer)
{
	char	*temp;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!store)
			store = ft_strdup("");
		if (store == NULL)
			return (free(store), store = NULL, NULL);
		temp = store;
		store = ft_strjoin(temp, buffer);
		if (store == NULL)
			return (free(store), store = NULL, free(temp), temp = NULL, NULL);
		(free(temp), temp = NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (store);
}

/**
 * @brief Extracts a line from the line buffer up to the first newline character.
 * @param line_buffer The buffer containing the line to extract.
 * @return A pointer to the newly allocated string containing the extracted line, 
 * or NULL if no newline character is found or if memory allocation fails.
 * @note 
 * - The function modifies the original buffer by terminating it at the newline
 *   character.
 * 
 * - The caller is responsible for freeing the returned string.
 */
static char	*get_line(char *line_buffer)
{
	char	*line;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[1] == '\0')
		return (NULL);
	line = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (line == NULL)
		return (free(line), line = NULL, NULL);
	if (*line == 0)
		(free(line), line = NULL);
	line_buffer[i + 1] = 0;
	return (line);
}

/**
 * @brief Reads a line from a file descriptor.
 * @param fd The file descriptor to read from.
 * @return 
 * - A null-terminated string containing the line read.
 * 
 * - NULL on error or EOF.
 * @note The function uses a static variable to handle multi-line reads across
 * multiple calls. It reads from the file descriptor in chunks of BUFFER_SIZE 
 * and processes the data until a newline character or EOF is encountered.
 * @note Depends on Libft functions: `ft_strdup`, `ft_strchr`, `ft_substr`,
 * `ft_strjoin`, and `ft_strlen`.
 * @warning The returned string must be freed by the caller.
 */
char	*get_next_line(int fd)
{
	static char	*store = NULL;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(store), store = NULL, NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(store), store = NULL, NULL);
	line = read_and_store(fd, store, buffer);
	(free(buffer), buffer = NULL);
	if (!line)
		return (free(store), store = NULL, NULL);
	store = get_line(line);
	return (line);
}

/* ************************************************************************** */
/* ************************* UNCOMMENT FOR TESTING  ************************* */
/* ************************************************************************** */

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("file0", O_RDONLY);
// 	if (fd == -1)
// 		return (printf("error"), 1);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		if (line == NULL)
// 			break ;
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
