#include<iostream>
#include "include/string.h"

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;


typedef struct
{
    String buffer;
    // size_t buffer_length;
    // ssize_t input_length;
} InputBuffer;

typedef struct{
    unsigned int id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
} Row;

typedef struct{
    StatementType type;
    Row row_to_insert;
} Statement;


InputBuffer* new_input_buffer(){
    InputBuffer* input_buffer = new InputBuffer;
    // input_buffer->buffer_length = 0;
    // input_buffer->input_length = 0;
    return input_buffer;
}

void print_prompt(){ std::cout << "db > "; }

void read_input(InputBuffer* input_buffer){
    char read[2048];
    std::cin.getline(read, 2048);
    input_buffer->buffer.set(read);

    if (input_buffer->buffer == "\0"){
        std::cout << "Error reading input\n";
        std::exit(EXIT_FAILURE);
    }
}

void close_input_buffer(InputBuffer* input_buffer){
    input_buffer->buffer.release();
    delete input_buffer;
}

MetaCommandResult do_meta_command(InputBuffer* input_buffer){
    if (input_buffer->buffer == ".exit"){
        std::exit(EXIT_SUCCESS);
    }
    else{
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement){
    if (input_buffer->buffer.strncmp("insert", 6)){
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (input_buffer->buffer == "select"){
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement){
    switch (statement->type){
        case (STATEMENT_INSERT): std::cout << "This is where we would do an insert.\n"; break;
        case (STATEMENT_SELECT): std::cout << "This is where we would do a select.\n"; break;
    }
}


int main(int argc, char* argv[]){
    InputBuffer* input_buffer = new_input_buffer();
    Statement statement;

    while (true){
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.'){
            switch (do_meta_command(input_buffer)){
                case (META_COMMAND_SUCCESS): continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND): {
                    std::cout << "Unrecognized command '";
                    input_buffer->buffer.PRINT();
                    std::cout << "'\n";
                    continue;
                }
            }
        }
        
        switch(prepare_statement(input_buffer, &statement)){
            case (PREPARE_SUCCESS): break;
            case (PREPARE_UNRECOGNIZED_STATEMENT): {
                std::cout << "Unrecognized keyword at start of '";
                input_buffer->buffer.PRINT();
                std::cout << "'\n";
                continue;
            }
        }
        execute_statement(&statement);
        std::cout << "Executed.\n";
    }
}
