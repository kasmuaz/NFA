#include <iostream>
#include <vector>
#include <math.h>
#include "State.h"
#include "_DFA.h"
#include "NFA.h"

using namespace std;

int main()
{
     NFA nfa("ulazNFA.txt");
    _DFA* dfa = nfa.CreateEquivalentDFA();
    dfa->printDFA();

    string w;
    cout << "Unosi stringove (kraj za kraj): ";

    while(1)
    {
        cin >> w;
        if(w == "kraj")
            break;
         if(dfa->Accepts(w))
        cout << "PRIHVATA\n";
    else
        cout << "NE PRIHVATA\n";

    }

    delete dfa;
    return 0;
}
