#ifndef GRAF_REGIUNE_H_INCLUDED
#define GRAF_REGIUNE_H_INCLUDED
#include <vector>
#include <iomanip>
#include <map>
#include <stack>
#include "oras.h"
#pragma once

typedef std :: pair<int,double> oras_dist;

const double Inf = 0x3f3f3f3f;

//Curiously Recurring Template Pattern
template<class T>
class Graph_regiune
{
    protected:
        std :: string nume_regiune;
        std :: vector <oras> orase;
        static unsigned nr_orase_curent;
        static unsigned id_regiune;
        std :: vector<std :: vector<oras_dist> > lista_adj;
        void sterge_oras_id(int );
    public:
        Graph_regiune(int nr_orase);
        Graph_regiune( );
        ~Graph_regiune(){id_regiune--;}
        void adauga_oras(oras &);
        oras cauta_oras(const std :: string &) const;
        std :: string cauta_nume(int ) const;
        void sterge_oras_nume(const std :: string &);
        void afiseaza_drumurile(std :: ostream &) const;
        void elimina_drum(const std :: string , const std :: string );
        void aduaga_drum(const std :: string a, const std :: string b)
        {
            return static_cast<T&>(*this).adauga_drum(a,b);
        }
        double calculeaza_drum_minim(const std :: string a,const std :: string b);
        template<typename X>
        friend std :: istream & operator>>(std :: istream &,Graph_regiune<X> &);
        template<typename X>
        friend std :: ostream & operator<<(std :: ostream &,const Graph_regiune<X> &);
};

class Linear_graph : public Graph_regiune<Linear_graph>
{
        double dist_min(int ,int ,double ,bool []);
    public:
        Linear_graph():Graph_regiune(){};
        Linear_graph(int n):Graph_regiune(n){};
        void adauga_drum(const std :: string ,const std :: string );
        double calculeaza_drum_minim(const std :: string ,const std :: string );
};

class Tree_graph : public Graph_regiune<Tree_graph>
{
        bool check_cycle(int ,bool [],int );
    public:
        Tree_graph():Graph_regiune(){};
        Tree_graph(int n):Graph_regiune(n){};
        void adauga_drum(const std :: string ,const std :: string );
};

class DAG_graph : public Graph_regiune<DAG_graph>
{
        bool check_cycle(int ,bool [],bool []);
    public:
        DAG_graph():Graph_regiune(){};
        DAG_graph(int n):Graph_regiune(n){};
        void sortare_topologica(int ,bool [],std :: stack <int> &);
        void adauga_drum(const std :: string ,const std :: string );
        double calculeaza_drum_minim(const std :: string ,const std :: string );
};


class General_graph : public Graph_regiune<General_graph>
{
    public:
        bool check_cycle(int ,bool [],int );
        General_graph():Graph_regiune(){};
        General_graph(int n):Graph_regiune(n){};
        void adauga_drum(const std :: string ,const std :: string );
};

class Complet_graph : public Graph_regiune<Complet_graph>
{
        void elimina_drum(const std :: string , const std :: string ){};
    public:
        Complet_graph():Graph_regiune(){};
        Complet_graph(int n):Graph_regiune(n){};
        void adauga_drum(const std :: string ,const std :: string );
        void adauga_oras(oras &);
        friend std :: istream & operator>>(std :: istream &,Complet_graph &);
        double calculeaza_drum_minim(const std :: string ,const std :: string );
};

template<typename T>
unsigned Graph_regiune<T> :: nr_orase_curent = 0;

template<typename T>
unsigned Graph_regiune<T> :: id_regiune = 0;

template<typename T>
Graph_regiune<T> :: Graph_regiune(int nr_orase)
{
    lista_adj.resize(nr_orase);
    id_regiune++;
}

template<typename T>
Graph_regiune<T> :: Graph_regiune()
{
    lista_adj.resize(10);
    id_regiune++;
}

template<typename T>
oras Graph_regiune<T> :: cauta_oras(const std :: string &A) const
{
    for(auto x : orase)
            if(x.nume==A)
                return x;
}

template<typename T>
std :: string Graph_regiune<T> :: cauta_nume(int p) const
{
    for(auto x : orase)
            if(x.id_oras==p)
                return x.nume;
}

template<typename T>
void Graph_regiune<T> :: afiseaza_drumurile(std :: ostream &out) const
{
    out << "Drumurile + distante sunt: " << std :: endl;
    std :: cout << std::fixed;
    std :: cout << std::setprecision(2);
    for(int i = 0; i < nr_orase_curent; i++)
    {
        out << std::setw(18) << cauta_nume(i) << ": ";
        for(auto x : lista_adj[i])
            out << std::setw(14) << cauta_nume(x.first) << "-" << std::right  << x.second << ", ";
        out << std :: endl;
    }
}

template<typename T>
void Graph_regiune<T> :: adauga_oras(oras &o)
{
    o.id_oras = nr_orase_curent;
    nr_orase_curent++;
    orase.push_back(o);
    int n = orase.size();
    if(lista_adj.size() < n )
    {
        lista_adj.resize(n);
    }
}

template<typename T>
void Graph_regiune<T> :: sterge_oras_id(int p)
{
    int i,n = orase.size();
    std :: vector <oras_dist> :: iterator it;
    //stergem din lista de adiacenta nodurile corespunzatoare orasului cu id p
    for(i = 0; i < n; i++)
    {
        it = lista_adj[i].begin();
        while(it != lista_adj[i].end())
        {
            if(it->first == p)
                it = lista_adj[i].erase(it);
            else it++;
        }
    }

    for(i = p; i < n-1; i++)
        std :: swap(lista_adj[i],lista_adj[i+1]);

    //apoi facem resizeul listei de adiacenta si stergem din vectorul oraselor pe cel cu id p
    lista_adj.resize(n-1);
    orase.erase(orase.begin()+p);

    //apoi facem o renumeroatre a oraselor si scadem nr oraselor si valorarea curenta pt id-uri
    for(i = p; i < n-1; i++)
        orase[i].id_oras -= 1;
    nr_orase_curent--;
}

template<class T>
void Graph_regiune<T> :: elimina_drum(const std :: string A, const std :: string B)
{
    if(A != B)
    {
        oras a,b;
        a = cauta_oras(A);
        b = cauta_oras(B);
        std :: vector <oras_dist> :: iterator it = lista_adj[a.id_oras].begin();
        while(it != lista_adj[a.id_oras].end())
        {
           if(it->first==b.id_oras)
                it = lista_adj[a.id_oras].erase(it);
            else it++;
        }
        it = lista_adj[b.id_oras].begin();
        while(it != lista_adj[b.id_oras].end())
        {
           if(it->first==a.id_oras)
                it = lista_adj[b.id_oras].erase(it);
            else it++;
        }
    }
}

template<typename T>
void Graph_regiune<T> :: sterge_oras_nume(const std :: string &nume)
{
    for(int i = 0; i < orase.size(); i++)
        if(orase[i].nume == nume)
            sterge_oras_id(i);
}

template<typename T>
std :: istream & operator>>(std :: istream &in,Graph_regiune<T> &graf)
{
    in.ignore(1,'\n');
    getline(in,graf.nume_regiune);
    if(graf.nume_regiune[graf.nume_regiune.length()-1]=='\r')
        graf.nume_regiune.erase(graf.nume_regiune.begin()+graf.nume_regiune.length()-1);
    int nr;
    in >> nr;
    oras o;
    for(int i = 0; i < nr; i++)
    {
        in >> o;
        graf.adauga_oras(o);
    }
    in.ignore(1,'\n');
    std :: string drumuri;
    getline(in,drumuri);
    std :: string token,token_a,token_b,delim1 = ", ", delim2 = "-";
    size_t poz,poz1;
    while((poz = drumuri.find(delim1)) != std::string::npos)
    {
        token = drumuri.substr(0,poz);
        poz1 = token.find(delim2);
        token_a = token.substr(0,poz1);
        token_b = token.substr(poz1 + delim2.length(),token.length());
        graf.aduaga_drum(token_a,token_b);
        drumuri.erase(0,poz + delim1.length());
    }
    if(drumuri[drumuri.length()-1]=='\r')
        drumuri.erase(drumuri.begin()+drumuri.length()-1);
    poz1 = drumuri.find(delim2);
    token_a = drumuri.substr(0,poz1);
    token_b = drumuri.substr(poz1 + delim2.length(),token.length());
    graf.aduaga_drum(token_a,token_b);
    return in;
}

template<typename T>
std :: ostream & operator<<(std :: ostream &out,const  Graph_regiune<T> &graf)
{
    out << std :: endl << "Regiunea " << graf.nume_regiune << " are orasele: " <<std :: endl;
    for(auto x : graf.orase)
        out << x;
    graf.afiseaza_drumurile(out);
    return out;
}

//Dijstra cu map pseudo min_heap si oprire la nodul de stop
template<typename T>
double Graph_regiune<T> :: calculeaza_drum_minim(const std :: string A, const std :: string B)
{
    if(A == B)
        return 0;
    int start,stop;
    start = cauta_oras(A).id_oras;
    stop = cauta_oras(B).id_oras;

    std :: map< double,int > mp;
    std :: vector <double> dist(nr_orase_curent,Inf);

    mp.insert(std :: make_pair(0,start));
    dist[start] = 0;

    int u,v;
    double w;
    while(!mp.empty() )
    {
        std :: pair<double, int> tmp = *(mp.begin());
        mp.erase(mp.begin());
        u = tmp.second;
        if( u == stop )
            return dist[u];

        for (auto x : lista_adj[u])
        {
             v = x.first;
             w = x.second;

            if (dist[v] > dist[u] + w)
            {
                if (dist[v] != Inf)
                    mp.erase(mp.find(dist[v]));

                dist[v] = dist[u] + w;
                mp.insert(std :: make_pair(dist[v], v));
            }
        }
    }
    return Inf;
}


#endif // GRAF_REGIUNE_H_INCLUDED
