#include "Graf_regiune.h"

bool Tree_graph :: check_cycle(int v,bool viz[],int tata)
{
    viz[v] = true;
    for (auto x : lista_adj[v])
    {
        if (!viz[x.first])
        {
           if (check_cycle(x.first, viz, v))
              return true;
        }
        else if (x.first != tata)
           return true;
    }
    return false;
}

void Tree_graph :: adauga_drum(const std :: string A,const std :: string B)
{
    if(A != B)
    {
        oras a,b;
        //cautam orasele dupa nume
        a = cauta_oras(A);
        b = cauta_oras(B);

        lista_adj[a.id_oras].push_back(std :: make_pair(b.id_oras,a.distanta_euclid(b)));
        lista_adj[b.id_oras].push_back(std :: make_pair(a.id_oras,b.distanta_euclid(a)));

        /*ma asigur ca introducrea drumului nu introduce un ciclu in graf, pt a pastra
        structura de arbore */

        bool vizitat[nr_orase_curent];
        for(int i = 0; i < nr_orase_curent; i++)
            vizitat[i] = false;
        for(int j = 0; j < nr_orase_curent && !vizitat[a.id_oras]; j++)
            if (!vizitat[j])
                if (check_cycle(j,vizitat,-1))
                {
                    elimina_drum(A,B);
                    break;
                }
    }
}
