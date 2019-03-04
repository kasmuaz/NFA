#ifndef _DFA_H_INCLUDED
#define _DFA_H_INCLUDED


#ifndef DFA_H_INCLUDED
#define DFA_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <exception>
#include <algorithm>
#include <map>
#include <utility>
#include <memory>
#include "State.h"

using namespace std;

class _DFA
{
    vector<State> states;
    vector<State> acceptS;
    State startS;
    int NofStates;
    vector<char> alphabet;
    map<pair<vector<int>,char>,State> transitions;
    void ExcessStates();
public:

    _DFA(vector<State> s,vector<char> a,map<pair<vector<int>,char>,State> t);
    void printDFA();
    bool Accepts(string w);


};


#endif // DFA_H_INCLUDED

#endif // _DFA_H_INCLUDED
