#pragma once

#include <vector>
#include <queue>

namespace utils::graph {

template <class T>
class Vertex;
template <class T>
class Edge;

/**
 * @brief      It describes the whole graph, with its nodes and connections
 *             between them.
 *
 * @tparam     T     { description }
 */
template <typename T>
class Graph {
    std::vector<Vertex<T>*> vertexSet;
    void dfs(Vertex<T>* v, std::vector<T>& res) const;
    std::vector<T> pontosArt;
    int counter;

public:
    bool addVertex(const T& in);
    bool addEdge(const T& sourc, const T& dest, double w);
    bool removeVertex(const T& in);
    bool removeEdge(const T& sourc, const T& dest);
    std::vector<T> dfs() const;
    std::vector<T> bfs(Vertex<T>* v) const;
    int maxNewChildren(Vertex<T>* v, T& inf) const;
    std::vector<Vertex<T>*> getVertexSet() const;
    int getNumVertex() const;
    std::vector<T> findArt();
    void findArt(Vertex<T>* v);
    std::vector<Vertex<T>*> npo();
    void npoAux(Vertex<T>* v);
    void clone(Graph<T>& g);
};

template <typename T>
int Graph<T>::getNumVertex() const
{
    return vertexSet.size();
}

template <typename T>
std::vector<Vertex<T>*> Graph<T>::getVertexSet() const
{
    return vertexSet;
}

template <typename T>
bool Graph<T>::addVertex(const T& in)
{
    typename std::vector<Vertex<T>*>::iterator it = vertexSet.begin();
    typename std::vector<Vertex<T>*>::iterator ite = vertexSet.end();
    for (; it != ite; it++)
        if ((*it)->info == in)
            return false;
    Vertex<T>* v1 = new Vertex<T>(in);
    vertexSet.push_back(v1);
    return true;
}

template <typename T>
bool Graph<T>::removeVertex(const T& in)
{
    typename std::vector<Vertex<T>*>::iterator it = vertexSet.begin();
    typename std::vector<Vertex<T>*>::iterator ite = vertexSet.end();
    for (; it != ite; it++) {
        if ((*it)->info == in) {
            Vertex<T>* v = *it;
            vertexSet.erase(it);
            typename vector<Vertex<T>*>::iterator it1 = vertexSet.begin();
            typename vector<Vertex<T>*>::iterator it1e = vertexSet.end();
            for (; it1 != it1e; it1++) {
                (*it1)->removeEdgeTo(v);
            }
            delete v;
            return true;
        }
    }
    return false;
}

template <typename T>
bool Graph<T>::addEdge(const T& sourc, const T& dest, double w)
{
    typename std::vector<Vertex<T>*>::iterator it = vertexSet.begin();
    typename std::vector<Vertex<T>*>::iterator ite = vertexSet.end();
    int found = 0;
    Vertex<T>*edgeS, *edgeD;
    while (found != 2 && it != ite) {
        if ((*it)->info == sourc) {
            edgeS = *it;
            found++;
        }
        if ((*it)->info == dest) {
            edgeD = *it;
            found++;
        }
        it++;
    }
    if (found != 2)
        return false;
    edgeS->addEdge(edgeD, w);
    return true;
}

template <typename T>
bool Graph<T>::removeEdge(const T& sourc, const T& dest)
{
    typename std::vector<Vertex<T>*>::iterator it = vertexSet.begin();
    typename std::vector<Vertex<T>*>::iterator ite = vertexSet.end();
    int found = 0;
    Vertex<T>*edgeS, *edgeD;
    while (found != 2 && it != ite) {
        if ((*it)->info == sourc) {
            edgeS = *it;
            found++;
        }
        if ((*it)->info == dest) {
            edgeD = *it;
            found++;
        }
        it++;
    }
    if (found != 2)
        return false;
    return edgeS->removeEdgeTo(edgeD);
}

template <typename T>
void Graph<T>::clone(Graph<T>& gr)
{
    typename std::vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
    typename std::vector<Vertex<T>*>::const_iterator ite = vertexSet.end();

    // 1. clone vertices
    for (; it != ite; it++) {
        gr.addVertex((*it)->getInfo());
        gr.vertexSet[gr.getNumVertex() - 1]->visited = false;
    }

    // 2. clone edges
    for (it = vertexSet.begin(); it != ite; it++) {
        typename std::vector<Edge<T>>::iterator edgeIt = ((*it)->adj).begin();
        typename std::vector<Edge<T>>::iterator edgeIte = ((*it)->adj).end();
        for (; edgeIt != edgeIte; edgeIt++) {
            gr.addEdge(
                (*it)->getInfo(), edgeIt->dest->getInfo(), edgeIt->weight);
        }
    }
}

template <typename T>
std::vector<T> Graph<T>::dfs() const
{
    typename std::vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
    typename std::vector<Vertex<T>*>::const_iterator ite = vertexSet.end();
    for (; it != ite; it++)
        (*it)->visited = false;
    std::vector<T> res;
    it = vertexSet.begin();
    for (; it != ite; it++)
        if ((*it)->visited == false)
            dfs(*it, res);
    return res;
}

template <typename T>
void Graph<T>::dfs(Vertex<T>* v, std::vector<T>& res) const
{
    v->visited = true;
    res.push_back(v->info);
    typename std::vector<Edge<T>>::iterator it = (v->adj).begin();
    typename std::vector<Edge<T>>::iterator ite = (v->adj).end();
    for (; it != ite; it++)
        if (it->dest->visited == false)
            dfs(it->dest, res);
}

template <typename T>
std::vector<T> Graph<T>::bfs(Vertex<T>* v) const
{
    std::vector<T> res;
    std::queue<Vertex<T>*> q;
    q.push(v);
    v->visited = true;
    while (!q.empty()) {
        Vertex<T>* v1 = q.front();
        q.pop();
        res.push_back(v1->info);
        typename std::vector<Edge<T>>::iterator it = v1->adj.begin();
        typename std::vector<Edge<T>>::iterator ite = v1->adj.end();
        for (; it != ite; it++) {
            Vertex<T>* d = it->dest;
            if (d->visited == false) {
                d->visited = true;
                q.push(d);
            }
        }
    }
    return res;
}

template <typename T>
int Graph<T>::maxNewChildren(Vertex<T>* v, T& inf) const
{
    std::vector<T> res;
    std::queue<Vertex<T>*> q;
    std::queue<int> level;
    int maxChildren = 0;
    inf = v->info;
    q.push(v);
    level.push(0);
    v->visited = true;
    while (!q.empty()) {
        Vertex<T>* v1 = q.front();
        q.pop();
        res.push_back(v1->info);
        int l = level.front();
        level.pop();
        l++;
        int nChildren = 0;
        typename std::vector<Edge<T>>::iterator it = v1->adj.begin();
        typename std::vector<Edge<T>>::iterator ite = v1->adj.end();
        for (; it != ite; it++) {
            Vertex<T>* d = it->dest;
            if (d->visited == false) {
                d->visited = true;
                q.push(d);
                level.push(l);
                nChildren++;
            }
        }
        if (nChildren > maxChildren) {
            maxChildren = nChildren;
            inf = v1->info;
        }
    }
    return maxChildren;
}

template <typename T>
std::vector<T> Graph<T>::findArt()
{
    counter = 1;

    for (size_t i = 0; i < vertexSet.size(); i++) {
        vertexSet[i]->visited = false;
        vertexSet[i]->low = -1;
        vertexSet[i]->num = -1;
    }

    findArt(vertexSet[0]);
    return pontosArt;
}

template <typename T>
void Graph<T>::findArt(Vertex<T>* v)
{
    v->visited = true;
    v->low = v->num = counter++;

    for (size_t i = 0; i < v->adj.size(); i++) {
        Vertex<T>* w = v->adj[i].dest;
        if (!w->visited) {
            w->path = v;
            findArt(w);
            if (w->low >= v->num) {
                if (v != vertexSet[0])
                    pontosArt.push_back(v->getInfo());
            }
            v->low = min(v->low, w->low);
        } else {
            if (v->path != w)
                v->low = min(v->low, w->num);
        }
    }
}

template <typename T>
std::vector<Vertex<T>*> Graph<T>::npo()
{
    counter = 1;

    for (size_t i = 0; i < vertexSet.size(); i++) {
        vertexSet[i]->visited = false;
        vertexSet[i]->num = -1;
    }

    for (size_t i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->visited == false)
            npoAux(vertexSet[i]);
    return vertexSet;
}

template <typename T>
void Graph<T>::npoAux(Vertex<T>* v)
{
    v->visited = true;
    for (size_t i = 0; i < v->adj.size(); i++) {
        Vertex<T>* w = v->adj[i].dest;
        if (w->visited == false)
            npoAux(w);
    }
    v->num = counter++;
}

} // namespace utils::graph
