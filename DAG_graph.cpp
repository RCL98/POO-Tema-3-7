#include "Graf_regiune.h"

bool DAG_graph :: check_cycle(int v,bool viz[],bool st_viz[])
{
    if(!viz[v])
    {
        viz[v] = 1;
        st_viz[v] = 1;
        for (auto x : lista_adj[v])
        {
           if ( !viz[x.first] && check_cycle(x.first, viz, st_viz) )
                return 1;
            else if (st_viz[x.first])
                return 1;
        }
    }
    st_viz[v] = false;
    return false;
}

void DAG_graph :: adauga_drum(const std :: string A,const std :: string B)
{
    if(A != B)
    {
        oras a,b;
        //cautam orasele dupa nume
        a = cauta_oras(A);
        b = cauta_oras(B);

        lista_adj[a.id_oras].push_back(std :: make_pair(b.id_oras,a.distanta_euclid(b)));

        /*ma asigur ca introducrea drumului nu introduce un ciclu in graf, pt a pastra
        structura de DAG */
        bool vizitat[nr_orase_curent],st_viz[nr_orase_curent];
        for(int i = 0; i < nr_orase_curent; i++)
            vizitat[i] = st_viz[i] = 0;
        for(int j = 0; j < nr_orase_curent && !vizitat[a.id_oras]; j++)
            if (!vizitat[j])
                if (check_cycle(j,vizitat,st_viz))
                {
                    elimina_drum(A,B);
                    break;
                }
    }
}

void DAG_graph :: sortare_topologica(int start,bool viz[],std :: stack<int> &st)
{
    viz[start] = true;

    for (auto x : lista_adj[start])
    {
        if (!viz[x.first])
            sortare_topologica(x.first,viz,st);
    }
    st.push(start);
}

double DAG_graph :: calculeaza_drum_minim(const std :: string A,const std :: string B)
{
    if(A == B)
        return 0;
    int start,stop;
    start = cauta_oras(A).id_oras;
    stop = cauta_oras(B).id_oras;

    int i,v;
    std :: stack <int> st;
    bool viz[nr_orase_curent];
    std :: vector <double> dist(nr_orase_curent,Inf);

    for (i = 0; i < nr_orase_curent; i++)
        viz[i] = 0;

    for (i = 0; i < nr_orase_curent; i++)
        if (viz[i] == false)
            sortare_topologica(i,viz,st);

    dist[start] = 0;
    while(!st.empty())
    {
        v = st.top();
        st.pop();
        if( v == stop )
            return dist[v];

        if (dist[v] != Inf)
        {
          for (auto x : lista_adj[v])
             if (dist[x.first] > dist[v] + x.second)
                dist[x.first] = dist[v] + x.second;
        }
    }
    return Inf;
}
