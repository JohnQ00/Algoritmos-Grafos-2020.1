#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

// Inicializa o número de vértices do grafo
#define V 7

// Retorna True se existe caminho de s a t no grafo residual
bool BFS(vector<vector<int>>& res_graph, int s, int t, int parent[])
{
	// Cria um array de vértices visitados
	bool visit_vextex[V];
	memset(visit_vextex, 0, sizeof(visit_vextex));
	queue<int> q; // Cria fila
	q.push(s); // Enfileira o vértice inicial
	visit_vextex[s] = true; // Marca como visitado
	parent[s] = -1;

	while (!q.empty()) { // Enquanto a fila não estiver vazia, u recebe o primeiro elemento da fila
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++) {
			if (visit_vextex[v] == false && res_graph[u][v] > 0) {
				if (v == t) { // Se atingiu o destino t
					parent[v] = u; // Adiciona u como nó pai de v no caminho
					return true; // Existe um caminho de s a t
				}
				q.push(v); 
				parent[v] = u; // Guarda o caminho a cada passo
				visit_vextex[v] = true; // Marca o vértice como visitado
			}
		}
	}

	return false; // Destino t não atingido
}

int ford_fulkerson(vector<vector<int>>& graph, int s, int t)
{
	int u, v;
	vector<vector<int>>& res_graph = graph; // Grafo de capacidades residuais de i a j para cada elemento res_graph[i][j]
    int parent[V]; // Array de caminhos de s a t
	int f_max = 0; // Fluxo inicial

	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			res_graph[u][v] = graph[u][v];

	// Busca e atualização do fluxo até o máximo enquanto houver caminho de s a t
	while (BFS(res_graph, s, t, parent)) { 
		int f_path = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			f_path = min(f_path, res_graph[u][v]); // Capacidade residual mínima ao longo de um dado caminho dado por 'parent'
		}

        // Capacidades residuais atualizadas ao longo do caminho
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			res_graph[u][v] = res_graph[u][v] - f_path;
			res_graph[v][u] = res_graph[v][u] + f_path;
		}

		f_max += f_path;
	}
	return f_max;
}

void add_edge(vector<vector<int>>& graph,
             int u, int v, int w)
{
    graph[u][v] = w;
}

int main()
{
    vector<vector<int>> graph(V, vector<int> (V, 0));

    add_edge(graph, 0, 1, 4);
    add_edge(graph, 0, 3, 3);
    add_edge(graph, 1, 2, 4);
    add_edge(graph, 2, 3, 3);
    add_edge(graph, 2, 5, 2);
    add_edge(graph, 5, 2, 3);
    add_edge(graph, 3, 4, 6);
    add_edge(graph, 4, 5, 6);
    
    cout << "Fluxo máximo: " <<
			 ford_fulkerson(graph, 1, 3) 
			 << endl;
    return 0;
}

