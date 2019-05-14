#include "Graf_regiune.h"

void Linear_graph :: adauga_drum(const std :: string A,const std :: string B)
{
    if(A != B)
    {
        oras a,b;
        //cautam orasele dupa nume
        a = cauta_oras(A);
        b = cauta_oras(B);
        /*ma asigur ca orasul mai un singur drum cu un alt oras, pt a pastra
        structura de graf linie */
        if(lista_adj[a.id_oras].size()<2 && lista_adj[b.id_oras].size()<2)
        {
            lista_adj[a.id_oras].push_back(std :: make_pair(b.id_oras,a.distanta_euclid(b)));
            lista_adj[b.id_oras].push_back(std :: make_pair(a.id_oras,b.distanta_euclid(a)));
        }
    }
}

double Linear_graph :: dist_min(int start,int stop,double min_dist,bool viz[])
{
    viz[start] = 1;
    int it = start,pred = stop;
    while(it!=stop && it!=pred)
    {
        pred = it;
        if(!viz[lista_adj[it][0].first])
        {
            it = lista_adj[it][0].first;
            min_dist += lista_adj[start][0].second;
            viz[it] = 1;
        }
        else if(lista_adj[it].size()>1 && !viz[lista_adj[it][1].first])
        {
            it = lista_adj[it][1].first;
            min_dist += lista_adj[it][1].second;
            viz[it] = 1;
        }
    }
    if(it!=stop)
        return Inf;
    else return min_dist;
}

double Linear_graph :: calculeaza_drum_minim(const std :: string A,const std :: string B)
{
    int start,stop;
    start = cauta_oras(A).id_oras;
    stop = cauta_oras(B).id_oras;
    double d= 0;
    bool vizitat[nr_orase_curent];
    for(int i = 0; i < nr_orase_curent; i++)vizitat[i]=0;
    vizitat[start] = 1;
    if(lista_adj[start].size()>1)
        return std :: min(dist_min(lista_adj[start][0].first,stop,d + lista_adj[start][0].second,vizitat),
                   dist_min(lista_adj[start][1].first,stop,d + lista_adj[start][1].second,vizitat));
    else return dist_min(lista_adj[start][0].first,stop,d + lista_adj[start][0].second,vizitat);
}
