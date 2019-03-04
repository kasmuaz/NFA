#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <vector>
using namespace std;


class State
{
    vector<int> v;
    bool start = false;
    bool accept = false;


public:
    State(vector<int> p);
    State(vector<int> p,bool s, bool a);
    State();

    vector<int> GetState() const;
    bool IsAccept();
    bool operator <(const State& rhs) const;
    bool operator == (const State& s) const;
    void print();
    void SetAcceptance();
    void SetStart();
    void Add(int i);
    bool GetAcceptance();
    bool GetStart();
    int vel(){return v.size();}
    int GetIth(int i){return v[i];}


};

#endif // STATE_H_INCLUDED
