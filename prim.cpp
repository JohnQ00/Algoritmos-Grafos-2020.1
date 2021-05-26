#include <iostream>
#include <tuple>
#include <queue>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

void add_edge(vector<vector<pair<int,int>>>& graph, int u, int v, int w)
{
    graph[u].push_back(make_pair(v, w));
    graph[v].push_back(make_pair(u, w));
}

vector<tuple<int,int,int>> prim(vector<vector<pair<int,int>>>& graph, int begin)
{
    int n = graph.size();
    vector<int> parent(n, -1); // vetor que guarda os pais de cada vértice da MST
    vector<bool> mst_included(n, false); // indica os vértices já incluídos na MST
    vector<int> aux_weight(n, INT_MAX); // vetor auxiliar que recebe os pesos das arestas na formação da MST
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; // fila de prioridade com o elemento de menor aux_weight na primeira posição
    
    pq.push(make_pair(0, begin)); // insere o par (peso auxiliar, vértice) do nó inicial na fila
    aux_weight[begin] = 0; 
    
    vector<tuple<int,int,int>> mst; // vetor que guarda a MST
    while (!pq.empty()) // enquanto a fila tiver elementos
    {
        int v = pq.top().second; // seta o vértice com aresta de menor peso na fila
        pq.pop();
        if (parent[v] != -1 && mst_included[v] == false) // se o vértice escolhido tiver nó pai determinado e ainda não está na MST
            mst.emplace_back(make_tuple(parent[v], v, aux_weight[v])); // adicione na MST

        mst_included[v] = true; // marca o vértice como incluído na MST
        for(auto elem : graph[v]) // para cada vizinho de v
        {
            int adj_v = elem.first;
            int weight = elem.second;
            if (mst_included[adj_v] == false && aux_weight[adj_v] > weight) // se o vértice adj_v não foi visitado e o peso w(a, adj_v) for menor que aux_weight[adj_v] atual  
            {
                parent[adj_v] = v; // o vizinho recebe v como pai
                aux_weight[adj_v] = weight; // aux_weight é atualizada
                pq.push(make_pair(aux_weight[adj_v],adj_v)); // par é inserido na fila
            }
        }
    }
    return mst;
}

int main(){
    int V = 4; // define o número de vértices
    vector<vector<pair<int,int>>> graph(V, vector<pair<int,int>>(V));

    // cria as arestas
    add_edge(graph, 0, 1, 5);
    add_edge(graph, 0, 2, 8);
    add_edge(graph, 1, 2, 10);
    add_edge(graph, 1, 3, 15);
    add_edge(graph, 2, 3, 20);

    vector<tuple<int,int,int>> final_mst = prim(graph, 0);
    cout << "MST (edges, weights): " << endl;
    for (tuple<int,int,int> t : final_mst)
        cout << "(" << get<0>(t) << "-" 
            << get<1>(t) << "," << get<2>(t) << ")" << endl;
    return 0;
}