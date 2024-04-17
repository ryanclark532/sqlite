#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/parser.h"
#include "include/input_buffer.h"

int main(int argc, char *argv[])
{
    InputBuffer *input_buffer = new_input_buffer();
    while (true)
    {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.')
        {
            switch (do_meta_command(input_buffer))
            {
            case (META_COMMAND_SUCCESSS):
                continue;
            case (META_COMMAND_UNRECOGNIZED_COMMAND):
                printf("Unrecognized command\n");
                continue;
            }
        }
        Statement statement;
        switch (prepare_statement(input_buffer, &statement))
        {
        case (PREPARE_SUCCESS):
            break;
        case (PREPARE_UNRECOGNIZED_STATEMENT):
            printf("Unrecognized statement\n");
            continue;
        }

        execute_statement(&statement);
        printf("Executed statement\n");
    }
}