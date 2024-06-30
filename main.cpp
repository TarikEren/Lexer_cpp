#include "headers/lexer.h"

int main() {
    //File name for the file to be read. (Change this to argv[1] for user input)
    const char* filename = "test.txt";
    //Initialised lexer object for interacting with functions
    auto lexer = new Lexer;

    //Read file
    //If the file could not be read, return -1
    bool file_read = lexer->read_file(filename);
    if (!file_read) return -1;

    //Parse the input text
    lexer->parse();
    lexer->print_words();
    //Delete the lexer object as it's heap allocated
    delete lexer;
    return 0;
}
