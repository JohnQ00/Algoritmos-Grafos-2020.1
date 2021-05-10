#include <iostream>
#include <list>
#include <queue>

#define INFINITY 999999

using namespace std;

class Graph{
    private:
        int V; // Vértices

    list<pair<int, int> > *adjList; // Inicializando a lista de adjacência

    public: 
        // Cria a lista de adjacência através do tamanho/número de vértices dado pelo usuário
        Graph(int V){
            this->V = V;
            adjList = new list<pair<int, int> >[V]; // Adiciona numa lista já feita (adjList) uma lista de pares formados por vértice e peso
        }

        // Adiciona uma aresta de V_1 para V_2 
        void addEdge(int V_1, int V_2, int weight){
            adjList[V_1].push_back(make_pair(V_2, weight)); // Aqui ele adiciona na lista de V_1 -> <V_2, peso> -> X ->
        }
        
        // Djikstra te permite encontrar o menor custo dado um caminho que passa por arestas com pesos positivos
        // Na função, a entrada é o vértice de início e o vértice de destino
        int djikstra(int start, int end){

            int dist[V]; // Distância de cada vértice
            int prev[V]; // Vai servir para guardar o caminho feito

            priority_queue<pair<int, int>, 
                vector<pair<int, int> >, greater<pair<int, int> > > priority_q; // Fila de prioridade mínima com cada vértice e seus pesos

            // Apenas inicializando distância e anteriores
            for (int i = 0; i < V; i++){
                dist[i] = INFINITY;
                prev[i] = -INFINITY;
            }

            // Todos os vértices têm distância 0 para eles mesmos
            dist[start] = 0;
    
            priority_q.push(make_pair(dist[start], start));

            while(!priority_q.empty()){
                pair<int, int> top_verticeAndWeight = priority_q.top(); // Pega o par do vértice com menor distância
                int top_vertice = top_verticeAndWeight.second; // Aqui pega o vértice propriamente dito
                priority_q.pop();

                list<pair<int, int> >::iterator it;
                for(it = adjList[top_vertice].begin(); it != adjList[top_vertice].end(); it++){
                    int top_neighbor_vertice = it->first;
                    int top_neighbor_weight = it->second;

                    if (dist[top_neighbor_vertice] > (dist[top_vertice] + top_neighbor_weight)){
                        dist[top_neighbor_vertice] = dist[top_vertice] + top_neighbor_weight;
                        prev[top_neighbor_vertice] = top_vertice;
                        priority_q.push(make_pair(dist[top_neighbor_vertice], top_neighbor_vertice));
                        cout << prev[top_neighbor_vertice] << "->" << top_neighbor_vertice << endl;
                    }
                }
            }
            return dist[end];
        }
};

int main(int argc, char const *argv[])
{
    Graph g(5);
    
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 1, 1);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 4, 1);

    cout << endl << "Custo minimo: " << g.djikstra(0, 4) << endl;
    return 0;
}
