#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include "decommentHeader.h"

/* This is the ADT to hold the different states of the DFA Design. */
typedef enum StateEnum {
    NORMAL,
    TRANSITION_COMMENT,
    COMMENT,
    RETURN_FROM_COMMENT,
    STRING_LITERAL,
    CHARACTER_LITERAL
} State;


// these are the function prototypes used to be executed in each state.

void normalCodeHandler(char entered, State* state);
void transitionStateHandler(char entered, State* state, int*, const int* line);
void commentHandler(char entered, State* state);
void returnFromCommentHandler(char entered, State* state, const int*, const int*);
void stringLiteralHandler(char entered, State* state);
void characterLiteralHandler(char entered, State* state);
// this is used for determining unterminated comments.
void checkForError(State* state, const int* commentline);

void main()
{
    int line = 1;
    int commentline = 0;
    State state = NORMAL;

for (;;)
{   
    
    char entered = getchar();
    if (entered == '\n')
        line++;
    // If it finished reading it checks for unterminated comments.
    if (entered == EOF)
    {checkForError(&state, &commentline);
    break;}
    
    // this is switch statements to check for states and call functions accordingly.
    switch (state)
    {
    case NORMAL:
        normalCodeHandler(entered, &state);
        break;
    case TRANSITION_COMMENT:
        transitionStateHandler(entered, &state, &commentline, &line);
        break;
    case COMMENT:
        commentHandler(entered, &state);
        break;
    case RETURN_FROM_COMMENT:
        returnFromCommentHandler(entered, &state, &commentline, &line);
        break;
    case STRING_LITERAL:
        stringLiteralHandler(entered, &state);
        break;
    case CHARACTER_LITERAL:
        characterLiteralHandler(entered, &state);
        break;

    }
}

}
// this function is called in normal state.
void normalCodeHandler(char entered, State* state){
    
    if (entered == '/')
    {*state = TRANSITION_COMMENT;}
    else if (entered == '\"'){
        *state = STRING_LITERAL;
    }
    else if (entered == '\'')
    { *state = CHARACTER_LITERAL;}
    if (*state != TRANSITION_COMMENT){
    putchar(entered);}

}
/* this function checks if transition from normal code section to comment section is possible.
if possible it changes the state to comment state. if it changes the state to normal state. or if / is encountered it remains in transition state.
*/
void transitionStateHandler(char entered, State* state, int* commentline, const int* line){
    if (entered == '/'){
        putchar('/');
    }
    else if (entered == '*')
    {
        *state = COMMENT;
        *commentline = *line;
    }
    else{
        putchar('/');
        putchar(entered);
        *state = NORMAL;
    }
}
//this function runs in comment section skipping characters as the program is supposed.
void commentHandler(char entered, State* state){
    if (entered == '\n'){
        putchar(entered);
    }
    else if(entered == '*'){
        *state = RETURN_FROM_COMMENT;
    }


}
// this function checks for if return from comment section to normal code section state is possible.
void returnFromCommentHandler(char entered, State* state, const int* line, const int* commentline){
    if (entered == '/'){
        if (*commentline == *line)
        putchar(' ');
        *state = NORMAL;
    }
    else if (entered == '*')
    {
        *state = RETURN_FROM_COMMENT;
    }
    else{
        if (entered == '\n')
        putchar(entered);
        *state = COMMENT;
    }
}
// this function checks for if it is the end of string literal and puts 'entered' characters.
void stringLiteralHandler(char entered, State* state){
    if (entered == '\"'){
        *state = NORMAL;
    } 
    putchar(entered);
    
}
// this function checks for if it is the end of character literal and puts 'entered' characters.
void characterLiteralHandler(char entered, State* state){
    if (entered == '\''){
        *state = NORMAL;
    } 
    putchar(entered);
}
// this function puts error on standard error stream if unterminated comment encountered.
void checkForError(State* state, const int* commentline){
    if (*state == COMMENT || *state == RETURN_FROM_COMMENT){
        fprintf(stderr, "Error: line %d: unterminated comment. \n", *commentline);

    }
}
