Input settings for automaton are read from input file (ulazNFA.txt). Input file is structured in the following manner:
alphabet: alphabet symbols
noState: number of states
delta: transition function (current state,next symbol in string,next state) or  (current state,next symbol in string,{next state,next state,...})
start: start state
accept: accept states 

Program asks user to enter strings which are then processed through given automaton and program outputs whether string is accepted or not.
Entering "kraj" terminates the program.  
