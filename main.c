#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/parser.h"
#include "include/input_buffer.h"

int main(int argc, char *argv[])
{
    Table *table = new_table();
    InputBuffer *input_buffer = new_input_buffer();
    while (true)
    {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.')
        {
            switch (do_meta_command(input_buffer, table))
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
        case (PREPARE_SYNTAX_ERROR):
            printf("Syntax error\n");
            continue;
        case (PREPARE_STRING_TOO_LONG):
            printf("Too long string\n");
            continue;
        case (PREPARE_NEGATIVE_ID):
            printf("ID must be positive\n");
            continue;
        case (PREPARE_UNRECOGNIZED_STATEMENT):
            printf("Unrecognized statement\n");
            continue;
        }

        switch (execute_statement(&statement, table))
        {
        case (EXECUTE_SUCCESS):
            printf("Executed successfully\n");
            break;
        case (EXECUTE_TABLE_FULL):
            printf("Table is full\n");
            break;
        }
    }
}