#include <iostream>
#include "graph.h"

int main()
{
    Graph g;
    g.addEdge("Paris", "Lyon", 100);
    g.addEdge("Paris", "Marseille", 150);
    g.addEdge("Lyon", "Nice", 80);
    g.addEdge("Marseille", "Nice", 70);
    g.addEdge("Nice", "Paris", 200);
    std::cout << "\n##### GRAPHE ÉTUDIÉ #####\n" << std::endl;
    std::cout << g << std::endl;

    // PARCOURS EN PROFONDEUR RÉCURSIF
    std::cout << "##### DFS RÉCURSIF #####\n" << std::endl;
    g.dfs_rec();

    // PARCOURS EN PROFONDEUR ITÉRATIF
    std::cout << "##### DFS ITÉRATIF #####\n" << std::endl;
    g.dfs_it();

    // PARCOURS EN LARGEUR
    std::cout << "##### BFS #####\n" << std::endl;
    g.bfs();

    return 0;
}