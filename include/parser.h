

#ifndef PARSER_H
#define PARSER_H
#include <stdint.h>

#include "pager.h"
#include "input_buffer.h"

typedef enum
{
    META_COMMAND_SUCCESSS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_STRING_TOO_LONG,
    PREPARE_NEGATIVE_ID,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareStatement;

typedef enum
{
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL
} ExecuteStatement;

typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct
{
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
} Row;

typedef struct
{
    StatementType type;
    Row row_to_insert;
} Statement;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct *)0)->Attribute)
const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;
const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 100
const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const uint32_t TABLE_MAX_ROWS = TABLE_MAX_PAGES * ROWS_PER_PAGE;

typedef struct
{
    uint32_t num_rows;
    Pager *pager;
} Table;

PrepareStatement
prepare_statement(InputBuffer *ib, Statement *statement);
ExecuteStatement execute_statement(Statement *statement, Table *table);
MetaCommandResult do_meta_command(InputBuffer *ib, Table *table);

void free_table(Table *table);
Table *new_table();
#endif /* PARSER_H */