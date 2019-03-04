#include <iostream>
#include <vector>
#include "State.h"

using namespace std;

State::State(vector<int> p) {v = p;}
State::State(vector<int> p,bool s, bool a):v(p),start(s),accept(a) {}
State::State()
{
}
vector<int> State::GetState() const
{
    return v;
}

 bool State::operator == (const State& s) const
 {
   return (v == s.v );
 }
bool State::IsAccept()
{
    return accept;
}
bool State::operator <(const State& rhs) const
{
    auto p = rhs.GetState();
    return v[0] < p[0];
}
void State::print()
{
    for (auto x : v)
        cout << x << " ";
        if(v.size() == 0)
            cout <<"0 ";
    if(accept)
        cout << " P ";
    else
        cout << " O ";
    if(start)
        cout << " S ";
    cout << "\n";

}
void State::Add(int i)
{
    v.push_back(i);
}

void State::SetAcceptance()
{
    accept = true;
}

void State::SetStart()
{
    start = true;
}
bool State::GetAcceptance()
{
    return accept;
}
bool State::GetStart()
{
    return start;
}


