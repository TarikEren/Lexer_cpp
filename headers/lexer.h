#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

//Error types
typedef enum error_type {
    FILENAME_NOT_PROVIDED,
    EMPTY_INPUT_TEXT,
    SYNTAX_ERROR
}error_type;

//Lexer class
class Lexer {
private:
    size_t line = 1, col = 1, index = 0;
    std::string input_text;
    char current{};
    std::vector<std::string> words;
    std::string buffer{};
public:
    /* Section: Main functions */
    //Function for file reading. Initialises the input_text variable.
    bool read_file(const char* filename);
    //Parse the input_text variable. input_text must be initialised beforehand.
    void parse();
    /* Section END */

    /* Section: Helper functions */
    //Move forward
    void consume();
    //Move back
    [[maybe_unused]] void step_back();
    //Peek next character
    [[maybe_unused]] char peek();
    //Push the current character into buffer
    void buffer_add();
    //Push the buffer into word list
    void word_add();
    //Increments the line count
    void inc_line();
    //Increments the col count
    void inc_col();
    //Resets the col count
    void reset_col();
    /* Section END */

    /* Section: Debugging /Getter-Setter functions */
    //Get col
    [[nodiscard]] size_t get_col() const;
    //Get line
    [[nodiscard]] size_t get_line() const;
    //Get input_text
    [[maybe_unused]] [[nodiscard]] std::string get_str() const;
    //Print words
    void print_words() const;
    //Get words
    [[maybe_unused]] [[nodiscard]] std::vector<std::string> get_words() const;
    /* Section END */

    //Error function
    void raise_error(error_type error) const;


};

