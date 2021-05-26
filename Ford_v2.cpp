#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

// Inicializa o número de vértices do grafo
#define V 7

/* Retorna True se existe caminho de s a t no grafo residual and guarda o caminho em parent[] */
bool BFS(vector<vector<int>>& rGraph, int s, int t, int parent[])
{
	// cria um array de vértices visitados
	bool visited[V];
	memset(visited, 0, sizeof(visited));

	queue<int> q; //cria fila
	q.push(s); // enfileira o vértice inicial
	visited[s] = true; // marca como visitado
	parent[s] = -1; // caminho do vértice até s a s não precisa ser 

	// Standard BFS Loop
	while (!q.empty()) { // enquanto a fila não estiver vazia, u recebe o primeiro elemento da fila
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++) {
			if (visited[v] == false && rGraph[u][v] > 0) {
				if (v == t) { // se atingiu o destino t
					parent[v] = u; // adiciona u como nó pai de v no caminho
					return true; // existe um caminho de s a t
				}
				q.push(v); 
				parent[v] = u; // guarda o caminho a cada passo
				visited[v] = true; // marca o vértice como visitado
			}
		}
	}

	return false; // destino t não atingido
}

int ford_fulkerson(vector<vector<int>>& graph, int s, int t)
{
	int u, v;
	vector<vector<int>>& rGraph = graph; // grafo de capacidades residuais de i a j para cada elemento rGraph[i][j]
    int parent[V]; // array de caminhos de s a t
	int max_flow = 0; // fluxo inicial

	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			rGraph[u][v] = graph[u][v];

	// busca e atualização do fluxo até o máximo enquanto houver caminho de s a t
	while (BFS(rGraph, s, t, parent)) { 
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]); // capacidade residual mínima ao longo de um dado caminho dado por 'parent'
		}

        // capacidades residuais atualizadas ao longo do caminho
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		max_flow += path_flow;
	}

	return max_flow;
}

void addEdge(vector<vector<int>>& graph,
             int u, int v, int w)
{
    graph[u][v] = w;
}

int main()
{
    // int V = 6;
    vector<vector<int>> graph(V, vector<int> (V, 0));

    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 3, 3);
    addEdge(graph, 1, 2, 4);
    addEdge(graph, 2, 3, 3);
    addEdge(graph, 2, 5, 2);
    addEdge(graph, 5, 2, 3);
    addEdge(graph, 3, 4, 6);
    addEdge(graph, 4, 5, 6);
    
    cout << "Fluxo maximo: " << ford_fulkerson(graph, 0, 5) << endl;
    return 0;
}

