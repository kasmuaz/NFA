#ifndef NFA_H_INCLUDED
#define NFA_H_INCLUDED

#include <exception>
#include <algorithm>
#include <map>
#include <utility>
#include <memory>


using namespace std;

class NFA
{
    vector<State> states;
    vector<int> acceptS;
    State startS;
    int start;
    int NofStates;
    vector<char> alphabet;
    map<pair<State,char>,vector<State>> transitions;
    vector<State> CreatePowerSet();
public:

    NFA(string file);
    void printNFA();
    bool Accepts(string w);
    vector<State> GetStates();
    friend void readFileNFA(string FileName,vector<char> &alphabet,int &noState,vector<int> &acceptStates, int &startState,map<pair<State,char>,State>& transitions);
    _DFA* CreateEquivalentDFA();
};


#endif // NFA_H_INCLUDED
