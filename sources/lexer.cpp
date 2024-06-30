#include "../headers/lexer.h"

//A way of coping with C++'s complex naming system.
using ifstream = std::ifstream;
using sstream = std::stringstream;

/* Section: Main functions */
bool Lexer::read_file(const char *filename)  {
    //If a file name is not provided, return false
    if (!filename) {
        raise_error(FILENAME_NOT_PROVIDED);
        return false;
    }
    //Initialise an input file stream
    ifstream file;

    //Open file
    file.open(filename, std::ios::in);

    //Buffer for file contents
    std::string contents;

    //String stream for reading file
    sstream str_stream;

    //Pass the buffer to the string stream
    str_stream << file.rdbuf();

    //Add the string contents to the buffer
    contents = str_stream.str();

    //Initialise the input_text variable using the buffer
    this->input_text = contents;

    //CLose the file
    file.close();

    //Set the current character (Will be used for parsing through the text) to the current index of the input_text
    //In this case it's the first character
    this->current = this->input_text[this->index];

    //Return true if no problems were encountered
    return true;
}

void Lexer::parse() {
    if (this->input_text.empty()) {
        raise_error(EMPTY_INPUT_TEXT);
        return;
    }
    //Continue until the current character is the null terminator
    while (this->current != '\0') {
        while (isalnum(this->current)) {
            this->buffer_add();
            this->consume();
        }
        //If a new line has been encountered, increment the line count and set the col count to 1
        if (this->current == '\n') {
            this->inc_line();
            this->reset_col();
            if (!this->buffer.empty()) {
                this->word_add();
                this->buffer.clear();
            }
        }
        else {
            //Increment the col count.
            if (this->current == ' ') {
                if (!this->buffer.empty()) {
                    this->word_add();
                    this->buffer.clear();
                }
            }
            this->inc_col();
        }
        //Consume the current character (Move forward)
        this->consume();
    }
}

void Lexer::raise_error(error_type error) const {
    switch (error) {
        case FILENAME_NOT_PROVIDED:
            std::cerr << "ERROR: File name not found. Aborting" << std::endl;
            break;
        case EMPTY_INPUT_TEXT:
            std::cerr << "ERROR: Input text is empty. Aborting" << std::endl;
            break;
        case SYNTAX_ERROR:
            std::cerr << "ERROR: Syntax error." << " Error Location: Line: " << this->get_line() << " Col: " << this->get_col() << std::endl;
            break;
        default:
            std::cerr << "ERROR: Unknown error" << std::endl;
            break;
    }
}
/* Section END */

/* Section: Debugging functions (Because GDB doesn't work on my end for some reason) */
size_t Lexer::get_col() const {
    return this->col;
}

size_t Lexer::get_line() const {
    return this->line;
}

[[maybe_unused]] std::string Lexer::get_str() const {
    return this->input_text;
}
/* Section END */

/* Section: Helper functions */
void Lexer::consume() {
    this->index += 1;
    this->current = this->input_text[this->index];
}

[[maybe_unused]] void Lexer::step_back() {
    this->index -= 1;
    this->current = this->input_text[this->index];
}

[[maybe_unused]] char Lexer::peek() {
    if (this->index != this->input_text.size() -2) return this->input_text[this->index + 1];
    else return '\0';
}

void Lexer::print_words() const {
    std::cout << "---WORDS START---" << std::endl;
    for (auto& word : this->words) {
        std::cout << word << std::endl;
    }
    std::cout << "---WORDS END---" << std::endl;
}

void Lexer::buffer_add() {
    this->buffer.push_back(this->current);
}

void Lexer::word_add() {
    this->words.push_back(this->buffer);
}

void Lexer::inc_line() {
    this->line += 1;
}

void Lexer::inc_col() {
    this->col += 1;
}

void Lexer::reset_col() {
    this->col = 1;
}

std::vector<std::string> Lexer::get_words() const {
    return this->words;
}

/* Section END */
