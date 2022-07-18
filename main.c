/* ************************************************************************** */
/*  888888  .d8888b.   .d8888b.                    888                        */
/*    "88b d88P  Y88b d88P  Y88b                   888                        */
/*     888 888    888 Y88b.                        888                        */
/*     888 888         "Y888b.    8888b.  88888b.  888888 .d88b.  .d8888b     */
/*     888 888            "Y88b.     "88b 888 "88b 888   d88""88b 88K         */
/*     888 888    888       "888 .d888888 888  888 888   888  888 "Y8888b.    */
/*     88P Y88b  d88P Y88b  d88P 888  888 888  888 Y88b. Y88..88P      X88    */
/*     888  "Y8888P"   "Y8888P"  "Y888888 888  888  "Y888 "Y88P"   88888P'    */
/*   .d88P                                                                    */
/* .d88P"                                                                     */
/*888P"                                                                       */
/*                                                                            */
/* Programa:	Open VNC                                                      */
/* Descripción:	Abrir Archivos VNC                                            */
/* Fecha:		18 - Jul - 2022                                               */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#define BUFFER_SIZE 1


int		ft_strlen(const char *string)
{
	int cnt;

	cnt = 0;
	while (*string != '\0')
	{
		string++;
		cnt++;
	}
	return (cnt);
}

char	*ft_strjoin(const char *string1, const char *string2)
{
	char	*str_join;
	int		count;

	count = 0;
	if (string1 == NULL || string2 == NULL)
		return (NULL);
	str_join = (char *)malloc(sizeof(char) *
		(ft_strlen(string1) + ft_strlen(string2)) + 1);
	if (str_join == NULL)
		return (NULL);
	while (*string1 != '\0')
	{
		str_join[count] = *string1;
		count++;
		string1++;
	}
	while (*string2 != '\0')
	{
		str_join[count] = *string2;
		count++;
		string2++;
	}
	str_join[count] = '\0';
	return (str_join);
}

char	*ft_strdup(const char *string1)
{
	char	*str_dup;
	int		count;

	count = 0;
	str_dup = (char *)malloc(sizeof(char) * (ft_strlen(string1)) + 1);
	if (str_dup == NULL)
		return (NULL);
	while (string1[count] != '\0')
	{
		str_dup[count] = string1[count];
		count++;
	}
	str_dup[count] = '\0';
	return (str_dup);
}

char	*ft_strchr(const char *string, int chr)
{
	while (*string != 0)
	{
		if (*string == (char)chr)
			return ((char *)string);
		string++;
	}
	if ((char)chr == '\0')
		return ((char *)string);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*string;
	size_t			count;
	unsigned int	ft_len;

	count = 0;
	if (s == NULL)
		return (NULL);
	if ((string = (char *)malloc(sizeof(*s) * (len + 1))) == 0)
		return (NULL);
	ft_len = (unsigned int)(ft_strlen(s));
	while (count < len && start < ft_len)
	{
		string[count] = s[count + start];
		count++;
	}
	string[count] = '\0';
	return (string);
}

void	ft_strdel(char **string)
{
	if (string != NULL && *string != NULL)
	{
		free(*string);
		*string = NULL;
	}
}

int	ft_add(char **read_fd, int fd, char **line)
{
	int		count;
	char	*tmp1;

	count = 0;
	while (read_fd[fd][count] != '\n')
		count++;
	*line = ft_substr(read_fd[fd], 0, count);
	tmp1 = ft_strdup(&read_fd[fd][count + 1]);
	free(read_fd[fd]);
	read_fd[fd] = tmp1;
	return (1);
}

int	fn_return(char **line, int fd, char **read_fd, ssize_t bytes_read)
{
	if (bytes_read < 0)
		return (-1);
	else if (bytes_read == 0 && (read_fd[fd] == NULL || read_fd[fd][0] == '\0'))
		{
			*line = ft_strdup("");
			ft_strdel(&read_fd[fd]);
			return (0);
		}
	else if (ft_strchr(read_fd[fd], '\n'))
		return (ft_add(read_fd, fd, line));
	else
		{
			*line = ft_strdup(read_fd[fd]);
			ft_strdel(&read_fd[fd]);
			return (0);
		}
}

void	read_buffer(char *buffer, int bytes_read, char **read_fd, int fd)
{
	char	*tmp;

	tmp = NULL;
	buffer[bytes_read] = '\0';
	if (read_fd[fd] == NULL)
		read_fd[fd] = ft_strdup(buffer);
	else
	{
		tmp = ft_strjoin(read_fd[fd], buffer);
		free(read_fd[fd]);
		read_fd[fd] = tmp;
	}
}

int	get_next_line(int fd, char **line)
{
	char		*buffer;
	ssize_t		bytes_read;
	static char	*read_fd[4096];

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || line == 0 || BUFFER_SIZE < 1 || (!buffer))
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		read_buffer(buffer, bytes_read, read_fd, fd);
		if (ft_strchr(read_fd[fd], '\n') != 0)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (fn_return(line, fd, read_fd, bytes_read));
}

int main()
{
	char	*command;
	char	**line;
	char	*ip;
	char	*port;
	char	*pass;
	int		fd;


	command = NULL;
	line = NULL;
	ip = NULL;
	port = NULL;
	pass = NULL;
	fd = open("/Users/juancarlossantos/Downloads/console.vv", O_RDWR);
	command = malloc(sizeof (char) * 100);
	line = malloc(sizeof (char) * 100);
	ip = malloc(sizeof (char) * 18);
	port = malloc(sizeof (char) * 5);
	pass = malloc(sizeof (char) * 14);
	get_next_line(fd, line);
	get_next_line(fd, line);
	get_next_line(fd, line);
	ip = ft_substr(*line, 5, 100);
	get_next_line(fd, line);
	port = ft_substr(*line, 5,100);
	get_next_line(fd, line);
	pass = ft_substr(*line, 9, 100);
	command = ft_strjoin(command, "open vnc://:");
	command = ft_strjoin(command, pass);
	command = ft_strjoin(command, "@");
	command = ft_strjoin(command, ip);
	command = ft_strjoin(command, ":");
	command = ft_strjoin(command, port);
	system (command);
	close(fd);
	remove("/Users/juancarlossantos/Downloads/console.vv");
	return 0;
}
