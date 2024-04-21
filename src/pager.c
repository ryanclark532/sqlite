#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include "../include/pager.h"

Pager *pager_open(const char *filename)
{
    int fd = open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);

    if (fd == -1)
    {

        printf("Failed to open %s\n", filename);
        exit(EXIT_FAILURE);
    }

    off_t file_length = lseek(fd, 0, SEEK_END);

    Pager *pager = malloc(sizeof(Pager));
    pager->file_descriptor = fd;
    pager->file_length = file_length;

    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
    {
        pager->pages[i] = NULL;
    }
    return pager;
}

void *get_page(Pager *pager, uint32_t page_number)
{
    if (page_number > TABLE_MAX_PAGES)
    {
        printf("Tried to get page numer out of bounds. %d > %d\n", page_number, TABLE_MAX_PAGES);
        exit(EXIT_FAILURE);
    }
    if (pager->pages[page_number] == NULL)
    {
        void *page = malloc(PAGE_SIZE);
        uint32_t num_pagers = pager->file_length / PAGE_SIZE;
        if (pager->file_length % PAGE_SIZE)
        {
            num_pagers++;
        }

        if (page_number <= num_pagers)
        {
            lseek(pager->file_descriptor, page_number * PAGE_SIZE, SEEK_SET);
            ssize_t read_bytes = read(pager->file_descriptor, page, PAGE_SIZE);
            if (read_bytes == -1)
            {
                printf("Error reading file %d\n", errno);
                exit(EXIT_FAILURE);
            }
        }
        pager->pages[page_number] = page;
    }
    return pager->pages[page_number];
}

void pager_flush(Pager *pager, uint32_t page_num, uint32_t size)
{
    if (pager->pages[page_num] == NULL)
    {
        printf("Tried to flush full page\n");
        exit(EXIT_FAILURE);
    }
    off_t offset = lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);
    if (offset == -1)
    {
        printf("Error seeking to page %d\n", errno);
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_written = write(pager->file_descriptor, pager->pages[page_num], size);
    if (bytes_written == -1)
    {
        printf("Error writing to file %d\n", errno);
        exit(EXIT_FAILURE);
    }
}