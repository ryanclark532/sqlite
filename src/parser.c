#include <string.h>
#include <stdlib.h>

#include "../include/parser.h"
#include "../include/input_buffer.h"

MetaCommandResult do_meta_command(InputBuffer *ib)
{
    if (strcmp(ib->buffer, ".exit") == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareStatement prepare_statement(InputBuffer *ib, Statement *statement)
{
    if (strncmp(ib->buffer, "insert", 6) == 0)
    {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strncmp(ib->buffer, "select", 6) == 0)
    {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement *statement)
{
    switch (statement->type)
    {
    case STATEMENT_INSERT:
        printf("insert\n");
        break;
    case STATEMENT_SELECT:
        printf("select\n");
        break;
    }
}