//
// Created by memonick on 17/04/2016.
//

#include "../headers/repl.h"

/**
 * Create the REPL, initializing the lexer and the parser
 */
repl::repl() {
    this->l = new lexer();
    this->p = new parser(l);
    this->i = new interpreter_visitor();
    this->s = new semantic_visitor();
}

/**
 * Delete the REPL, alongside its lexer and parser
 */
repl::~repl() {
    delete this->l;
    delete this->p;
    delete this->i;
    delete this->s;
}

/**
 * Run the REPL
 */
void repl::run() {
    repl_keyword command_keyword;
    do {
        string command = this->get_command();
        command_keyword = this->interpret_command(command);
        this->execute_command(command, command_keyword);
    } while (command_keyword != REPL_quit);
}

/**
 * Execute the user's command
 */
void repl::execute_command(string command_string, repl_keyword command_keyword) {
    switch (command_keyword) {
        case REPL_quit:
            break;
        case REPL_load:
            {
                string path = command_string.substr(6, command_string.size() - 6);
                string content = file::getFileString(path);
                this->l = new lexer(content);
                this->p = new parser(this->l);
                AST_program_node * program = this->p->parse();
                if (analyze_semantics(program)) {
                    interpret(program);
                }
            }
            break;
        case REPL_st:
            if (this->i != nullptr) {
                cout << this->i->get_symbol_table()->to_string() << endl;
            }
            break;
        case REPL_print:
            {
                string path = command_string.substr(7, command_string.size() - 7);
                this->l = new lexer(this->l->get_program());
                this->p = new parser(this->l);
                string tree = this->get_tree(this->p->parse());
                file::save(path, "output.xml", tree);
            }
            break;
        case REPL_other:
            {
                string content = command_string + " ";
                this->l = new lexer(content);
                this->p = new parser(this->l);
                AST_program_node * program = this->p->parse();
                if (analyze_semantics(program)) {
                    interpret(program);
                    cout << this->i->get_last().to_string() << endl;
                }
            }
            break;
    }
}

/**
 * Get the next user command
 * return           the user command
 */
string repl::get_command() {
    cout << "MLi> ";
    string s = "";
    getline (cin, s);
    return s;
}

/**
 * Isolate the keyword from the user's input
 * command          the user's command
 * return           the user's keyword
 */
string repl::get_key(string command) {
    char c;
    int position = 0;
    string actual_command = "";
    while (position < command.size() && c != ' ') {
        c = command.at(position++);
        if (c != ' ') {
            actual_command += c;
        }
    }
    return actual_command;
}

/**
 * Interpret the user's command and return its keyword
 * command          the user's command
 * return           the user's command as a keyword
 */
repl_keyword repl::interpret_command(string command) {
    string actual_command = this->get_key(command);

    if (actual_command == "#quit") {
        return REPL_quit;
    } else if (actual_command == "#load") {
        return REPL_load;
    } else if (actual_command == "#st") {
        return REPL_st;
    } else if (actual_command == "#print") {
        return REPL_print;
    } else {
        return REPL_other;
    }
}

/**
 * Get the textual representation of the command
 * command          the command whose textual representation will be retrieved
 * return           the textual representation of the command
 */
string repl::keyword_to_string(repl_keyword command) {
    switch (command) {
        case REPL_quit:
            return "REPL_quit";
        case REPL_load:
            return "REPL_load";
        case REPL_st:
            return "REPL_st";
        case REPL_other:
            return "REPL_other";
        case REPL_print:
            return "REPL_print";
    }
}

/**
 * Print the tokens of the lexer given
 * l                the lexer whose tokens will be printed
 */
void repl::print_tokens(lexer * l) {
    unsigned i = 0;
    token * t = l->peek(i);
    while (t->get_name() != TOK_eof) {
        cout << t->to_string() << endl;
        t = l->peek(++i);
    }
}

/**
 * Get the textual representation of the program given
 * program_node     the program whose textual representation will be retrieved
 * string           the textual representation of the program given
 */
string repl::get_tree(AST_program_node * program_node) {
    printer_visitor * printer = new printer_visitor();
    program_node->accept(printer);
    string tree = printer->get_last();
    delete printer;
    return tree;
}

/**
 * Analyze the program given to check whether it is semantically-correct or not
 * program_node     the program which will be semantically-analyzed
 * return           a boolean indicating whether the semantic analysis was successful (true), or not (false)
 */
bool repl::analyze_semantics(AST_program_node * program_node) {
    return this->s->analyze(program_node);
}

/**
 * Interpret the given program
 * program_node     the program to interpret
 */
void repl::interpret(AST_program_node * program_node) {
    this->i->analyze(program_node);
}