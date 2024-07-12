#include <stdio.h>
#include <omp.h>
#define V 11          // Number of vertices in the graph
#define NUM_THREADS 4 // Number of threads to use
char vertexLabels[V] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
int visited[V] = {0}; // Array to track visited vertices
int parent[V];        // Array to store the parent of each vertex during traversal
int graph[V][V] = {
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
};

void DFS(int v)
{
    visited[v] = 1;
    for (int i = 0; i < V; i++)
    {
        if (graph[v][i] && !visited[i])
        {
            parent[i] = v;
            DFS(i);
        }
    }
}
int main()
{
    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for
    for (int v = 0; v < V; v++)
    {
        if (!visited[v])
        {
            DFS(v);
        }
    }
    printf("\nEdges of the spanning tree:\n");
    for (int i = 1; i < V; i++)
    {
        printf("(%c, %c)\n", vertexLabels[parent[i]], vertexLabels[i]);
    }
    return 0;
}
