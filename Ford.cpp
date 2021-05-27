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
	// cria um array de vértices visitados
	bool visit_vextex[V];
	memset(visit_vextex, 0, sizeof(visit_vextex));
	queue<int> q; //cria fila
	q.push(s); // enfileira o vértice inicial
	visit_vextex[s] = true; // marca como visitado
	parent[s] = -1;

	while (!q.empty()) { // enquanto a fila não estiver vazia, u recebe o primeiro elemento da fila
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++) {
			if (visit_vextex[v] == false && res_graph[u][v] > 0) {
				if (v == t) { // se atingiu o destino t
					parent[v] = u; // adiciona u como nó pai de v no caminho
					return true; // existe um caminho de s a t
				}
				q.push(v); 
				parent[v] = u; // guarda o caminho a cada passo
				visit_vextex[v] = true; // marca o vértice como visitado
			}
		}
	}

	return false; // destino t não atingido
}

int ford_fulkerson(vector<vector<int>>& graph, int s, int t)
{
	int u, v;
	vector<vector<int>>& res_graph = graph; // grafo de capacidades residuais de i a j para cada elemento res_graph[i][j]
    int parent[V]; // array de caminhos de s a t
	int f_max = 0; // fluxo inicial

	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			res_graph[u][v] = graph[u][v];

	// busca e atualização do fluxo até o máximo enquanto houver caminho de s a t
	while (BFS(res_graph, s, t, parent)) { 
		int f_path = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			f_path = min(f_path, res_graph[u][v]); // capacidade residual mínima ao longo de um dado caminho dado por 'parent'
		}

        // capacidades residuais atualizadas ao longo do caminho
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

