#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../include/pipex.h"

void test_ft_printf_fd()
{
    int fd;
    char buffer[256];
    ssize_t bytes_read;

    // Create a temporary file
    fd = open("temp_test_file.txt", O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
    {
        perror("Failed to create temporary file");
        return;
    }

    // Write an error message using ft_printf_fd
    ft_printf_fd(fd, "Error: %s\n", "Test error message");

    // Reset file offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // Read the contents of the file
    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1)
    {
        perror("Failed to read from temporary file");
        close(fd);
        return;
    }

    // Null-terminate the buffer
    buffer[bytes_read] = '\0';

    // Verify the contents
    if (strcmp(buffer, "Error: Test error message\n") == 0)
    {
        printf("Test passed: Error message written correctly\n");
    }
    else
    {
        printf("Test failed: Unexpected output: %s\n", buffer);
    }

    // Clean up
    close(fd);
    remove("temp_test_file.txt");
}

int main()
{
    test_ft_printf_fd();
    return 0;
}
