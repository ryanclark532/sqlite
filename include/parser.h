

#ifndef PARSER_H
#define PARSER_H
#include "input_buffer.h"

typedef enum
{
    META_COMMAND_SUCCESSS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareStatement;

typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct
{
    StatementType type;
} Statement;

PrepareStatement prepare_statement(InputBuffer *ib, Statement *statement);
void execute_statement(Statement *statement);
MetaCommandResult do_meta_command(InputBuffer *ib);
#endif /* PARSER_H */