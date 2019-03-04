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
#include "_DFA.h"

using namespace std;

   _DFA::_DFA(vector<State> s,vector<char> a,map<pair<vector<int>,char>,State> t)
   {

       NofStates = s.size();
       states = s;

       alphabet = a;
       transitions = t;

       for(int i = 0; i <  states.size(); i++)
       if(states[i].GetStart()){
        startS = states[i];
        break;
        }

       for(int i = 0;  i<states.size(); i++)
       if(states[i].GetAcceptance())
        acceptS.push_back(states[i]);


   }

void _DFA::ExcessStates()
{
    vector<State> visited;

    for(auto x : transitions)
     {
         bool flag = true;
         for(int i  = 0; i < visited.size(); i++)
         {
             if(visited[i] == x.second){
                flag = false;
                break;
             }
         }
         if(flag)
         visited.push_back(x.second);
     }

     cout << "Stanja u koja se ne moze doci su:\n";

     vector<bool> vek(states.size(),false);
     for(int i = 0; i < states.size(); i++){
     for(auto x : visited)
     {
        if(x == states[i])
        {
            vek[i] = true;
            break;
        }

     }
     }

    for(int i = 0; i < vek.size(); i++)
        if(!vek[i])
    {
       for(auto x : states[i].GetState())
        cout << x <<" ";
       cout << "\n";
    }
}
void _DFA::printDFA()
{
    cout << "Broj stanja je " << NofStates << ".\n" <<"Pocetno stanje je: ";
    for(auto x : startS.GetState())
        cout << x << " ";

    cout << ".\n"<<"Zavrsna stanja su:\n";
    for(auto x : acceptS)
       {
          for(auto y : x.GetState())
        cout << y << " ";
        cout << "\n";
       }
    cout << " \nTranzcija je data sa:\n";
    for(auto x : transitions)
    {
        auto p = x.first.first;
        auto q = x.first.second;
        auto z = x.second.GetState();
      cout << "( ";
      for(auto y : p)
        cout <<y << " ";
      cout << q << " ";
      for(auto y : z)
        cout << y << " ";
      cout << ")\n";
    }
    cout << "*******************\n Stanja su:\n";
    for(auto x : states)
        x.print();
    ExcessStates();



}
bool _DFA::Accepts(string w)
{
    if(w.length() == 0)
        return startS.IsAccept();

    State x =  transitions[pair<vector<int>,char>(startS.GetState(),w[0])];

    for(int i = 1; i < w.length(); i++)
        x = transitions[pair<vector<int>,char>(x.GetState(),w[i])];


    for(int i = 0; i < NofStates; i++)
        if(states[i].GetState()[0] == x.GetState()[0])
        {
            x = states[i];
        }
    if(x.IsAccept())
        return true;
    else
        return false;

}



















