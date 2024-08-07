#include "defs.h"

int graph_add_node(graph_t *graph, char node_id) {
    for (int i = 0; i < graph->ids.size(); i++) {
        if (graph->ids[i] == node_id) {
            printf("node %c: already exists!\n", node_id);
            return -1;
        }
    }
    graph->ids.push_back(node_id);

    std::vector<int> vec;
    for (int i = 0; i < graph->ids.size()-1; i++) {
        vec.push_back(INF);
    }
    vec.push_back(0);
    
    graph->mat.push_back(vec); 
    for (int i = 0; i < graph->ids.size()-1; i++) {
        graph->mat[i].resize(graph->ids.size());
        graph->mat[i].at(graph->mat[i].size()-1) = INF;
    }
    
    return 0;
}

int graph_add_edge(graph_t *graph, char src_node_id, char dst_node_id, int weight) {
    if (!graph_check_node(*graph, src_node_id)) {
        graph_add_node(graph, src_node_id);
    }
    if (!graph_check_node(*graph, dst_node_id)) {
        graph_add_node(graph, dst_node_id);
    }

    if (graph_check_edge(graph, src_node_id, dst_node_id)) {
        printf("edge %c -> %c already exists!\n", src_node_id, dst_node_id);
        return -1;
    }
    if (weight < 1) {
        printf("edge weight should greater than 0");
        return -1;
    }

    int src_index = graph_get_node_index(*graph, src_node_id); 
    int dst_index = graph_get_node_index(*graph, dst_node_id); 
    graph->mat[src_index][dst_index] = weight; 
    return 0;
}

int graph_delete_node(graph_t *graph, char node_id) {
    if (graph->mat.size() < 1) {
        printf("El grafo esta vacio!\n");
        return -1;
    }

    if (!graph_check_node(*graph, node_id)) {
        printf("El nodo %c no existe!\n", node_id);
        printf("\n");
        return -1;
    }

    for (int i = 0; i < graph->ids.size(); i++) {
        if (graph->ids[i] == node_id) {
            graph->ids.erase(graph->ids.begin()+i);
            for (int j = 0; j < graph->mat.size(); j++) {
                graph->mat[j].erase(graph->mat[j].begin()+i);
            }
            graph->mat.erase(graph->mat.begin()+i);
            return 0;
        }
    }
    
    return -1; 
}

int graph_delete_edge(graph_t *graph, char src_node_id, char dst_node_id) {
    if (graph->mat.size() < 1) {
        printf("graph is empty!\n");
        return -1;
    }

    if (!graph_check_node(*graph, src_node_id)) {
        printf("source node %c: doesnt exists!\n", src_node_id);
        return -1;
    }
    if (!graph_check_node(*graph, dst_node_id)) {
        printf("destination node %c: doesnt exists!\n", dst_node_id);
        return -1;
    }

    if (graph_check_edge(graph, src_node_id, dst_node_id)) {
        int src_index = graph_get_node_index(*graph, src_node_id); 
        int dst_index = graph_get_node_index(*graph, dst_node_id); 
        graph->mat[src_index][dst_index] = INF;
        return 0;
    }
    
    printf("edge %c -> %c: doesnt exist!\n", src_node_id, dst_node_id);
    return -1; 
}

int graph_get_node_index(graph_t graph, char node_id) {
    if (graph.mat.size() < 1) {
        printf("graph is empty!\n");
        return -1;
    }
    if (!graph_check_node(graph, node_id)) {
        printf("node %c doesnt exists!\n", node_id);
        return -1;
    }

    for (int i = 0; i < graph.ids.size(); i++) {
        if (graph.ids[i] == node_id) {
            return i;
        }
    }
    
    return -1;
}

bool graph_check_node(graph_t graph, char node_id) {
    for (int i = 0; i < graph.ids.size(); i++) {
        if (graph.ids[i] == node_id) {
            return true; 
        }
    }

    return false;
}

bool graph_check_edge(graph_t *graph, char src_node_id, char dst_node_id) {
    if (graph->mat.size() < 1) {
        printf("graph is empty!\n");
        return false;
    }

    int src_index = graph_get_node_index(*graph, src_node_id); 
    int dst_index = graph_get_node_index(*graph, dst_node_id); 
    if (graph->mat[src_index][dst_index] != INF) {
        return true;
    }

    return false;
}

void graph_print_nodes(graph_t graph) {
    if (graph.mat.size() < 1) {
        printf("graph is empty!\n");
        return;
    }

    printf("Informacion de nodos:\n");
    for (int i = 0; i < graph.mat.size(); i++) {
        printf("%c -> ", graph.ids[i]);
        for (int j = 0; j < graph.mat[i].size(); j++) {
            if (graph.mat[i][j] > 0 && graph.mat[i][j] != INF) {
                printf("(%c: %d), ", graph.ids[j], graph.mat[i][j]);
            } 
        }
        printf("\n");
    }
    printf("\n");
}

void graph_print_adjacency_mat(graph_t graph) {
    for (int i = 0; i < graph.mat.size(); i++) {
        printf(" %c", graph.ids[i]);
    }
    printf("\n");
    for (int i = 0; i < graph.mat.size(); i++) {
        printf("%c ", graph.ids[i]);
        for (int j = 0; j < graph.mat[i].size(); j++) {
            if (graph.mat[i][j] != INF) {
                printf("%d ", graph.mat[i][j]);
            } else {
                printf("~ ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void print_mat(std::vector<std::vector<int> > mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            if (mat[i][j] != INF) {
                printf("%d ", mat[i][j]);
            } else {
                printf("~ ");
            }
        }
        printf("\n");
    }
}

void graph_print_node(graph_t graph, char node_id) {
    if (graph.mat.size() < 1) {
        printf("graph is empty!\n");
        return;
    }

    if (!graph_check_node(graph, node_id)) {
        printf("node %c doesnt exists!\n", node_id);
        return;
    }

    printf("Informacion del nodo %c:\n", graph.ids[graph_get_node_index(graph, node_id)]);
    int node_index = graph_get_node_index(graph, node_id);

    printf("%c -> ", graph.ids[node_index]);
    for (int i = 0; i < graph.mat[node_index].size(); i++) {
        if (graph.mat[node_index][i] > 0 && graph.mat[node_index][i] != INF) {
            printf("(%c: %d), ", graph.ids[i], graph.mat[node_index][i]);
        } 
    }
    printf("\n");
}

std::vector<std::vector<int> > floyd_warshall_graph(graph_t graph) {
    std::vector<std::vector<int> > dist = graph.mat;
    int n = dist.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    printf("Matriz despues de aplicar floyd-warshall\n");
    graph_t new_graph = {
        .mat = dist,
        .ids = graph.ids,
    };
    graph_print_adjacency_mat(new_graph);
//  print_mat(dist);
    return dist;
}

void graph_is_connected(graph_t graph) {
    std::vector<std::vector<int> > mat = floyd_warshall_graph(graph);

    int n = mat.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            if (mat[j][i] == 0 || mat[j][i] == INF) {
                printf("el grafo es conexo\n");
                for (int i = 0; i < n; i++) {
                    int check_fuente = 0;
                    int check_pozo = 0;
                    for (int j = 0; j < n; j++) {
                        if (i == j) {
                            continue;
                        }
                        if (graph.mat[j][i] == 0 || graph.mat[j][i] == INF) {
                            check_fuente++;
                        }     
                    }

                    for (int k = 0; k < n; k++) {
                        if (i == k) {
                            continue;
                        }
                        if (graph.mat[i][k] == 0 || graph.mat[i][k] == INF) {
                            check_pozo++;
                        }     
                    }

                    if (check_fuente == n-1) {
                        printf("nodo %c: es fuente\n", graph.ids[i]);
                    }
                    if (check_pozo == n-1) {
                        printf("nodo %c: es pozo\n", graph.ids[i]);
                    }
                }
                printf("\n");
                return;
            }
        }
    }
    printf("el grafo es fuertamente conexo\n");
    printf("\n");
}

void dijkstra(graph_t graph, int start) {
    int n = graph.mat.size();
    int dist[n];
    bool visited[n];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[start] = 0;

    printf("Dijkstra desde el nodo %c:\n\n", graph.ids[start]);
    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        visited[u] = true;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph.mat[u][v] && dist[u] != INF && dist[u] + graph.mat[u][v] < dist[v]) {
                dist[v] = dist[u] + graph.mat[u][v];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            printf("Vertice %c es inalcanzable desde vertice %d\n", graph.ids[start], start);
        } else {
            printf("Distancia del vertice %c al vertice %c es: %d\n", graph.ids[start], graph.ids[i], dist[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    graph_t graph;

    std::fstream f;
    f.open("arista.txt", std::ios::in);
    if (!f.is_open()) {
        printf("Error abriendo el archivo arista.txt\n");
        exit(1);
    }

    std::string str;
    std::getline(f, str);
    int edge_count = std::stoi(str); 
    while (std::getline(f, str)) {
        char src_node_id = str[0];
        char dst_node_id = str[3];
        int weight = std::stoi(str.substr(5, str.length()-1));
        std::string sub = str.substr(1, 2);
        graph_add_edge(&graph, src_node_id, dst_node_id, weight);
    }

    while (true) {
        CLEAR;
        std::string in;
        printf("1. Ver informacion del grafo\n");
        printf("2. Eliminar un nodo del grafo\n");
        printf("3. Salir\n\n");
        printf("> ");
        std::getline(std::cin, in);
        fflush(stdin);

        CLEAR;
        if (!in.compare("1")) {
            printf("Grafo:\n");
            printf("Cantidad de nodos: %zu\n", graph.ids.size());
            printf("Cantidad de vertices: %d\n", edge_count);
            printf("Tamano de la matriz de adyacencia: %zux%zu\n ", graph.mat.size(), graph.mat[0].size());
            graph_print_adjacency_mat(graph);
            graph_print_nodes(graph);
            graph_is_connected(graph);

            dijkstra(graph, 2);
            printf("Presione ENTER para regresar al menu");
            getchar();
            CLEAR;
            continue;
        }

        if (!in.compare("2")) {
            if (graph.mat.size() < 1) {
                printf("el grafo esta vacio\n"); 
                continue;
            }
            graph_print_nodes(graph);
            printf("Introduzca el id del nodo que desea eliminar: ");
            std::getline(std::cin, in);
            fflush(stdin);

            if (graph_delete_node(&graph, in[0]) > -1) {
                printf("\nNodo %c: eliminado correctamente\n\n", in[0]);

                printf("Nuevo grafo:\n");
                graph_print_nodes(graph);
            } else {
                printf("Nodo %c: no se pudo eliminar\n", in[0]);
            }
            printf("Presione ENTER para regresar al menu");
            getchar();
            CLEAR;
            continue;
        }

        if (!in.compare("3")) {
            break;
        }
    }

    return 0;
}
