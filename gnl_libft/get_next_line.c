/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:14:30 by ozamora-          #+#    #+#             */
/*   Updated: 2025/04/15 02:18:41 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_strlcpy - Copies a string up to a specified size.
 * 
 * @dst:  The destination buffer where the string will be copied.
 * @src:  The source string to copy from.
 * @size: The size of the destination buffer.
 * 
 * Return: The total length of the string it tried to copy (the length of 'src').
 * 
 * Description:
 * - It copies up to 'size - 1' characters from the source string 'src'
 * to the destination buffer 'dst',
 * - Function ensures the destination string is null-terminated. 
 * - If 'size' is 0, no characters are copied, and only the length of 
 *  'src' is returned.
 * - Function always returns the total length of 'src', regardless of whether
 * the entire string was copied. This can be useful for truncating strings or 
 * determining the necessary buffer size.
 * 
 * Note: The destination buffer must be large enough to receive the string, 
 *       otherwise the string will be truncated.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	if (!dst || !src)
		return (0);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

static char	*read_and_append(int fd, char *store, char *buffer)
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
 * @return A pointer to the newly allocated string containing the extracted line
 * or NULL if no newline character is found or if memory allocation fails.
 * @note 
 * - The function modifies the original buffer by terminating it at the newline
 *   character.
 * 
 * - The caller is responsible for freeing the returned string.
 */
static char	*extract_line_store_remaining(char *line_buffer)
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
	static char	*store[MAX_FD];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (free(store[fd]), store[fd] = NULL, NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(store[fd]), store[fd] = NULL, NULL);
	line = read_and_append(fd, store[fd], buffer);
	(free(buffer), buffer = NULL);
	if (!line)
		return (free(store[fd]), store[fd] = NULL, NULL);
	store[fd] = extract_line_store_remaining(line);
	return (line);
}

/* ************************************************************************** */
/* ************************* UNCOMMENT FOR TESTING  ************************* */
/* ************************************************************************** */

int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line1;
	char	*line2;
	char	*line3;

	fd1 = open("file0", O_RDONLY);
	fd2 = open("file1", O_RDONLY);
	fd3 = open("alphabet", O_RDONLY);
	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
		return (printf("error"), 1);
	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);
		(printf("%s", line1), printf("%s", line2), printf("%s", line3));
		if (line3 == NULL)
			break ;
		(free(line1), free(line2), free(line3));
	}
	(close(fd1), close(fd2), close(fd3));
	return (0);
}