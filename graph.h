#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <queue>

class Graph
{
private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> G;

public:
    void addSummit(const std::string &newS);
    void addEdge(const std::string &from, const std::string &to, const double &d);
    void printGraph() const;

    // PARCOURS EN PROFONDEUR RÉCURSIF
    void dfs_rec_from(const std::string &si, std::unordered_map<std::string, bool> &visited);
    void dfs_rec();

    // PARCOURS EN PROFONDEUR ITÉRATIF
    void dfs_it_from(const std::string &si);
    void dfs_it();

    // PARCOURS EN LARGEUR
    void bfs_from(const std::string &si);
    void bfs();

    friend std::ostream &operator<<(std::ostream &os, Graph &g);
};

inline void Graph::addSummit(const std::string &newS)
{
    if (G.contains(newS) == false) // si le sommet n'existe pas, on l'initialise par un vecteur vide, sinon rien
    {
        G[newS] = {};
    }
}

inline void Graph::addEdge(const std::string &from, const std::string &to, const double &d)
{
    addSummit(from); // on ajoute les sommets s'ils ne sont pas déjà dans le graphe
    addSummit(to);

    for (const std::pair<std::string, double> &p : G[from]) // on vérifie si l'arête existe déjà
    {
        if (p.first == to and p.second == d)
        {
            return;
        }
    }

    G[from].push_back({to, d}); // on ajoute l'arête orientée avec son poids
}

inline void Graph::printGraph() const
{
    std::cout << "{\n";
    for (const auto &e : G) // les éléments de G sont des couples (key, value) càd des std::pair<std::string, std::vector<...>>
    {
        std::cout << e.first << " -> [";
        for (const std::pair<std::string, double> &p : e.second) // e.second est un std::vector<std::pair<...>>
        {
            std::cout << " (" << p.first << ',' << p.second << ") ";
        }
        std::cout << "]\n";
    }
    std::cout << '}' << std::endl;
}

// PARCOURS EN PROFONDEUR RÉCURSIF

inline void Graph::dfs_rec_from(const std::string &si, std::unordered_map<std::string, bool> &visited) // parcours en profondeur récursif depuis un sommet
{
    if (visited.contains(si)) // on vérifie si le sommet a déjà été visité
    {
        return;
    }
    visited[si] = true; // on marque le sommet comme visité

    for (const auto &neighbor : G[si])
    {
        std::cout << si << " -> " << '(' << neighbor.first << ',' << neighbor.second << ')' << std::endl;
        dfs_rec_from(neighbor.first, visited);
    }
}

inline void Graph::dfs_rec()
{
    for (const auto &e : G)
    {
        std::unordered_map<std::string, bool> visited;

        std::cout << "Parcours en profondeur récursif depuis " << e.first << " :" << std::endl;
        dfs_rec_from(e.first, visited);
        std::cout << "\n";
    }
}

// PARCOURS EN PROFONDEUR ITÉRATIF

inline void Graph::dfs_it_from(const std::string &si)
{
    std::stack<std::string> neighbors_waiting; // pile d'attente
    std::unordered_map<std::string, bool> visited;
    neighbors_waiting.push(si); // on initialise avec le sommet initial

    while (!neighbors_waiting.empty()) // tant que la liste d'attente n'est pas vide
    {
        std::string summit{neighbors_waiting.top()}; // on dépile le dernier voisin entré
        neighbors_waiting.pop();                     // dans cette librairie, pop ne renvoie rien

        if (!visited.contains(summit)) // si sommet pas encore visité
        {
            visited[summit] = true;

            for (const auto &neighbor : G[summit])
            {
                neighbors_waiting.push(neighbor.first);
                std::cout << summit << " -> " << '(' << neighbor.first << ',' << neighbor.second << ')' << std::endl;
            }
        }
    }
}

inline void Graph::dfs_it()
{
    for (const auto &e : G)
    {
        std::cout << "Parcours en profondeur itératif depuis " << e.first << " :" << std::endl;
        dfs_it_from(e.first);
        std::cout << '\n';
    }
}

// PARCOURS EN LARGEUR

inline void Graph::bfs_from(const std::string &si)
{
    std::queue<std::string> neighbors_waiting; // file d'attente (first in first out)
    std::unordered_map<std::string, bool> visited;
    neighbors_waiting.push(si); // on initialise avec le sommet initial

    while (!neighbors_waiting.empty())
    {
        std::string summit{neighbors_waiting.front()};
        neighbors_waiting.pop();

        if (!visited.contains(summit))
        {
            visited[summit] = true;

            for (const auto &neighbor : G[summit])
            {
                neighbors_waiting.push(neighbor.first);
                std::cout << summit << " -> " << '(' << neighbor.first << ',' << neighbor.second << ')' << std::endl;
            }
        }
    }
}

inline void Graph::bfs()
{
    for (const auto &e : G)
    {
        std::cout << "Parcours en largeur depuis " << e.first << " :" << std::endl;
        bfs_from(e.first);
        std::cout << '\n';
    }
    return;
}

std::ostream &operator<<(std::ostream &os, Graph &g)
{
    g.printGraph();
    return os;
}
