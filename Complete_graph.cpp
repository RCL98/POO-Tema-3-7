#include "Graf_regiune.h"

void Complet_graph :: adauga_drum(const std :: string A,const std :: string B)
{
    if(A != B)
    {
        oras a,b;
        a = cauta_oras(A);
        b = cauta_oras(B);

        lista_adj[a.id_oras].push_back(std :: make_pair(b.id_oras,a.distanta_euclid(b)));
        lista_adj[b.id_oras].push_back(std :: make_pair(a.id_oras,b.distanta_euclid(a)));
    }
}

std :: istream & operator>>(std :: istream &in,Complet_graph &graf)
{
    in.ignore(1,'\n');
    getline(in,graf.nume_regiune);
    int nr;
    in >> nr;
    oras o;
    for(int i = 0; i < nr; i++)
    {
        in >> o;
        graf.adauga_oras(o);
    }
}

void Complet_graph :: adauga_oras(oras &o)
{
    o.id_oras = nr_orase_curent;
    nr_orase_curent++;
    orase.push_back(o);
    int n = orase.size();
    if(lista_adj.size() < n )
    {
        lista_adj.resize(n);
    }
    for(auto x : orase)
    {
        aduaga_drum(o.nume,x.nume);
    }
}

double Complet_graph :: calculeaza_drum_minim(const std :: string A,const std :: string B)
{
    if(A == B)
        return 0;

    int a,b;
    a = cauta_oras(A).id_oras;
    b = cauta_oras(B).id_oras;

    for(auto x : lista_adj[a])
        if(x.first == b)
            return x.second;
}
