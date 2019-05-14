#include "Graf_regiune.h"

void General_graph :: adauga_drum(const std :: string A,const std :: string B)
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
