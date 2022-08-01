/* This is the header file for decomment.c c code. for more information please 
check the DFA design.*/
// this declares the Enum stateEnum ADT to hold different states of the DFA Design.
typedef enum StateEnum State;
//this fuction detects unterminated comment. and prints error message in standard error output.
void checkForError(State* state, const int* commentline);
//this function will be executed in normal state of the code. it puts characters based on conditions
void normalCodeHandler(char entered, State* state);
/* this function executes if a slash is incountered in normal 
code to check for transition to comment state.*/
void transitionStateHandler(char entered, State* state, int*, const int* line);
/* this fuction executes in comment state. it avoids writing 
characters except for new line character,which is used 
to preserve code line.*/
void commentHandler(char entered, State* state);
/*
this executed when asterics is encountered in comment state. it checks for
return from comment state to normal state. it returns to normal state when 
 / is encountered immediately after the asterics.
*/
void returnFromCommentHandler(char entered, State* state, const int*, const int*);
/*This is executed when the code is in string literal state in which characters are 
written as they are inputed.*/
void stringLiteralHandler(char entered, State* state);
/*This is executed when the code is in string literal state in which characters are 
written as they are inputed.*/
void characterLiteralHandler(char entered, State* state);
