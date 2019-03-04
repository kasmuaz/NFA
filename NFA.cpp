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
#include "NFA.h"

using namespace std;

pair<State,char> make_simple_pair(State s,char a)
{
    auto par = make_pair(State(),a);
    par.first = s;
    cout <<"*******\n";
    par.first.print();
    cout << "********\n";

    return par;
}

pair<pair<State,char>,State> make_simple_pair2(State p,char a,State s)
{
    auto par = make_pair(State(),a);
    par.first = p;

    auto par2 = make_pair(par,State());
    par2.first = par;
    par2.second = s;

    return par2;
}

void readFileNFA(string FileName,vector<char> &alphabet,int &noState,vector<int> &acceptStates, int &startState,map<pair<State,char>,vector<State>>& transitions)
{
    std::ifstream ulazni_tok(FileName);

    if(!ulazni_tok)
        throw std::domain_error("Nije uspjelo ucitavanje fajla " +FileName + "!\n");
    else
    {

        std::string red_datoteke;
        int linija = 0;
        while(std::getline(ulazni_tok, red_datoteke))
        {
            if(linija == 0)
            {
                int i = 0;
                while(red_datoteke[i] != ':')
                    i++;

                for(int j = i+1; j < red_datoteke.size(); j++)
                {
                    if(red_datoteke[j] == ' ' || red_datoteke[j] == ',')
                        continue;
                    alphabet.push_back(red_datoteke[j]);
                }
                linija++;
            }
            else if(linija == 1)
            {
                int i = 0;
                while(red_datoteke[i] != ':')
                    i++;

                for(int j = i+1; j < red_datoteke.size(); j++)
                {
                    if(red_datoteke[j] == ' ')
                        continue;
                    noState = red_datoteke[j] - '0';
                }
                linija++;
            }

            else if(linija == 2)
            {

                int i = 0;
                while(red_datoteke[i] != ':')
                    i++;

                for(int j = i+1; j < red_datoteke.size(); j++)
                {
                    if(red_datoteke[j] == ' ')
                        continue;

                    if(red_datoteke[j] == '(')
                    {
                        j++;
                        int k;
                        k = red_datoteke[j];
                        j+=2;
                        char z;
                        z = red_datoteke[j];
                        j+=2;
                        vector<int> pom1;
                        vector<State> pom2;
                        if(red_datoteke[j] == '{')
                        {

                            for(int t = j+1; red_datoteke[t] != '}'; t++)
                            {
                                if(red_datoteke[t] == ' ' || red_datoteke[t] == ',')
                                    continue;
                                pom2.push_back(State({red_datoteke[t] - '0'}));
                                j = t;
                            }

                            pom1.push_back(k-'0');
                            j++;
                        }
                        else
                        {
                            int l;
                            l =red_datoteke[j];
                            j+=2;

                            pom1.push_back(k-'0');

                            pom2.push_back(State({l-'0'}));
                        }

                        State s(pom1);

                        transitions[pair<State,char>(s,z)] = pom2;
                    }
                }
                linija++;
            }
            else if(linija == 3)
            {
                int i = 0;
                while(red_datoteke[i] != ':')
                    i++;

                for(int j = i+1; j < red_datoteke.size(); j++)
                {
                    if(red_datoteke[j] == ' ')
                        continue;
                    startState = red_datoteke[j] - '0';
                }
                linija++;
            }
            else
            {
                int i = 0;
                while(red_datoteke[i] != ':')
                    i++;

                for(int j = i+1; j < red_datoteke.size(); j++)
                {
                    if(red_datoteke[j] == ' ' || red_datoteke[j] ==',')
                        continue;
                    acceptStates.push_back(red_datoteke[j]-'0');
                }
                linija++;
            }
        }
    }
    ulazni_tok.close();
}


NFA::NFA(string file)
{
    try
    {
        readFileNFA(file,alphabet,NofStates,acceptS,start,transitions);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what();
    }
    sort(acceptS.begin(),acceptS.end());
    for(int i = 0; i < NofStates; i++)
    {
        bool flag1 = false;
        if(binary_search(acceptS.begin(),acceptS.end(),i+1))
            flag1 = true;
        bool flag2 = false;
        if(start==i+1)
        {
            flag2 = true;
        }
        vector<int> v;
        v.push_back(i+1);
        auto p = make_shared<State>(v,flag2,flag1);
        if (flag2)
            startS = *p;
        states.push_back(*p);
    }

}
void NFA::printNFA()
{
    cout << "Broj stanja je " << NofStates << ".\n" <<"Pocetno stanje je: " << start << ".\n"<<"Zavrsna stanja su: ";
    for(auto x : acceptS)
        cout << x << " ";
    cout << " \nTranzcija je data sa:\n";
    for(auto x : transitions)
    {
        auto p = x.first.first.GetState();
        auto q = x.first.second;
        auto z = x.second;
        cout <<"( "<< p[0] << "," << q << ",";
        for(auto x : z)
            x.print();
        cout<<")\n";
    }
    cout << "*******************\n Stanja su:\n";
    for(auto x : states)
        x.print();



}
vector<State> NFA::GetStates()
{
    return states;
}
bool NFA::Accepts(string w)
{
    return false;

}


vector<State> NFA::CreatePowerSet()
{
    int p = 1;
    p = p<<states.size();
    vector<State> NewStates(p);
    NewStates[0].Add(0);

    for(int i = 0; i < p; i++)
    {
        for(int j = 0; j < states.size(); j++)
        {
            if(i & (1<<j))
                NewStates[i].Add(j+1);
        }
    }
    return NewStates;
}

inline bool operator ==( State& lhs,  State& rhs)
{

    if(lhs.GetState().size() != rhs.GetState().size())
        return false;
    sort(lhs.GetState().begin(),lhs.GetState().end());
    sort(rhs.GetState().begin(),rhs.GetState().end());

    return(lhs.GetState() == rhs.GetState() && rhs.GetAcceptance() == lhs.GetAcceptance() && rhs.GetStart() == lhs.GetStart());
}

bool Equal (State s, vector<State> p)
{
    auto v1  = s.GetState();
    vector<int> v2;


    for(int i = 0; i < p.size(); i++)
    {
        for(int j = 0; j < p[i].vel(); j++)
            v2.push_back(p[i].GetIth(j));
    }
    sort(v1.begin(),v1.end());
    sort(v2.begin(),v2.end());
    return v1 == v2;
}


State MakeState(vector<vector<State>> v)
{
    vector<int> pom;

    for(int i =0; i <  v.size(); i++)
    {
        for(int j = 0; j < v[i].size(); j++){
            pom.push_back(v[i][j].GetIth(0));
        }
    }
    if(pom.size()>1){
        sort(pom.begin(),pom.end());
     auto last = std::unique(pom.begin(), pom.end());
    pom.erase(last, pom.end());
    }
    return State(pom);
}
_DFA* NFA::CreateEquivalentDFA()
{
    vector<State> DFAstates = CreatePowerSet();
    bool flag = false;

    vector<State> temp;
    if(transitions.find(pair<State,char>(startS,'e')) != transitions.end())
        temp = transitions[pair<State,char>(startS,'e')];
    else
        flag = true;

    if(flag)
    {
        for(int i = 0; i < DFAstates.size(); i++)
        {
            if(DFAstates[i].GetIth(0) == startS.GetIth(0) && DFAstates[i].vel() == 1)
            {
                DFAstates[i].SetStart();
                break;
            }
        }

    }
    else
    {
        temp.push_back(startS);
        for(int i = 0; i < DFAstates.size(); i++)
        {
            if(Equal(DFAstates[i],temp))
            {
                DFAstates[i].SetStart();
                break;
            }
        }
    }

    for(int i = 0; i < DFAstates.size(); i++)
    {
        for(int j = 0; j < DFAstates[i].vel(); j++)
        {
            for(int k = 0;  k < acceptS.size(); k++)
                if(DFAstates[i].GetIth(j) == acceptS[k])
                {
                    DFAstates[i].SetAcceptance();
                    break;
                }
        }
    }

    map<pair<vector<int>,char>,State> trans;


    for(int i =0; i < DFAstates.size(); i++)
{
        auto pom = DFAstates[i].GetState();
        vector<State> m;
        for(int j = 0; j < pom.size(); j++)
        {
            m.push_back(State({pom[j]}));
        }


        for(int k = 0; k < alphabet.size(); k++)
        {
            //cout << "#####################################\n";
            vector<vector<State>> rez;
            for(auto a : m)
            {
                  //  cout << "********************************\n Sada ispitujem stanje ";
                    //   a.print();
                //cout << " i slovo " << alphabet[k] << "\n";
                vector<State> eps;
                if(transitions.find(make_pair(a,alphabet[k])) != transitions.end())
                {
                    rez.push_back(transitions[make_pair(a,alphabet[k])]);
                    eps = transitions[make_pair(a,alphabet[k])];

                }
                for(int q = 0;  q < eps.size(); q++){

                if(transitions.find(make_pair(eps[q],'e'))!= transitions.end())
                    {
                        rez.push_back(transitions[make_pair(eps[q],'e')]);
                        //for(auto o : transitions[make_pair(a,alphabet[k])])
                        //o.print();
                    }
                }

                // stanje.print();

            }
             auto stanje  = MakeState(rez);
              //  cout << "i dobijam stanje : "; stanje.print();
              //  cout << "Ukupna tranzicije pocinje: ";
               // DFAstates[i].print();
               // cout <<"**************\nVektor:";
               if(stanje.vel() == 0)
                stanje.Add(0);
                vector<int> f = DFAstates[i].GetState();
                 //for(auto h : f )
                 //   cout << h << " ";
               //  cout << "\n*********************\n";

               auto par = make_pair(f,alphabet[k]);
               auto paru = make_pair(par,stanje);
              // cout <<"OVo ";
               //paru.first.first.print();
               //paru.second.print();
               //auto it = trans.end();
              trans.insert(paru);
             //trans[pair<State,char>(State(f),alphabet[k])] = stanje;


        }
}

/*
         map<pair<State,char>,State> t;
         for(auto x : trans)
         {
             //t.insert( std::map< pair<State,char>, State>::value_type ( {State(x.first.first),x.first.second}, State(x.second) ) );
             t.emplace(make_simple_pair2(State(x.first.first),x.first.second,State(x.second)));
               // t[make_simple_pair(State(x.first.first),x.first.second)] = State(x.second);
         }


*/
/*
        for(auto x : trans){
            auto p = x.first.first;
            //cout << p.size() << " \n";

            auto q = x.first.second;
            auto z = x.second.GetState();

           for(auto w : p)
                cout << w << " ";

            cout  << q << " ";

            for(auto w : z)
                cout << w << " ";
            cout << "\n";
        }
*/
        return new _DFA(DFAstates,alphabet,trans);





}

















