#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

class Edge{
    int edge_1, edge_2, weight; // Seta os valores certos de uma aresta para facilitar a verificação do UF
    public:
        Edge(int e_1, int e_2, int w){
            edge_1 = e_1;
            edge_2 = e_2;
            this->weight = w;
        }

        // Três métodos de Get para os valores da aresta
        int getEdge_1(){
            return edge_1;
        }

        int getEdge_2(){
            return edge_2;
        }

        int getWeight(){
            return weight;
        }

        // Sobrescrita de operador, nesse caso, <. Para ordenar do menor valor para o maior valor no sort que será utilizado
        bool operator < (const Edge& edge_2) const {
            return (weight < edge_2.weight);
        }
};

class Graph{
    int V;
    vector<Edge> edges; // Dentro da classe Graph deve existir algo para representar suas arestas, sendo, nesse caso, um vector de edges com o tipo Edge feito acima

    public:
        // Construtora do grafo, recebendo quantidade de vértices
        Graph(int V){this->V = V;}
        // Adicionar arestas, igual à implementação de Djikstra
        void addEdge(int V_1, int V_2, int weight){ 
            Edge edge(V_1, V_2, weight);
            edges.push_back(edge);
        }
        // Aqui entra o Union Find(UF), sendo essa primeira parte o Find, basicamente ele procura as conexões de cada vértice para checar se há ciclo
        int find_UnionFind(int subset[], int i){
            if(subset[i] == -1){
                return i;
            }
            return find_UnionFind(subset, subset[i]);
        }
        // Aqui vem a parte de Union do UF, onde acontece a conexão de um vértice ao outro quando não há ciclo, confirmado pela Find
        void union_UnionFind(int subset[], int V_1, int V_2){
            int V1_set = find_UnionFind(subset, V_1);
            int V2_set = find_UnionFind(subset, V_2);
            subset[V1_set] = V2_set;
        }
        // A implementação de Kruskal propriamente dita, onde há um vetor para localizar a AGM mínima e a quantidade de arestas
        void kruskal(){
            vector<Edge> AGM;
            int edgeSize = edges.size();

            sort(edges.begin(), edges.end()); // Ordena os pesos das arestas presentes no grafo, do menor para o maior

            int * subset = new int[V]; // É a parte MakeSet do UF, onde é alocada memória para criar "V" subconjuntos

            memset(subset, -1, sizeof(int) * V); // Aqui ocorre a inicialização dos subconjuntos, todos são setados com -1

            for (int i = 0; i < edgeSize; i++){
                int V_1 = find_UnionFind(subset, edges[i].getEdge_1());
                int V_2 = find_UnionFind(subset, edges[i].getEdge_2());

                // Verifica se são diferentes, se forem não há formação de ciclo
                if (V_1 != V_2) {
                    AGM.push_back(edges[i]);
                    union_UnionFind(subset, V_1, V_2); // Faz a união no subset
                }
            }

            int AGMSize = AGM.size();

            for (int i = 0; i < AGMSize; i++){
                char vertice_1 = 'A' + AGM[i].getEdge_1();
                char vertice_2 = 'A' + AGM[i].getEdge_2();

                cout << "(" << vertice_1 << ", " << vertice_2 << ") = " << AGM[i].getWeight() << endl;
            }
        }
};

int main(int argc, char const *argv[])
{
    Graph g(7);

    g.addEdge(0, 1, 7);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 3, 9);
    g.addEdge(1, 4, 7);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 4, 15);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 8);
    g.addEdge(4, 6, 9);
    g.addEdge(5, 6, 11);

    g.kruskal();

    return 0;
}
