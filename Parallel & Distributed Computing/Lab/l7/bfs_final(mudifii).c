#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define V 11 // Number of vertices in the graph
#define NUM_THREADS 4 // Number of threads to use

char vertexLabels[V] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
int visited[V] = {0}; // Array to track visited vertices
int parent[V]; // Array to store the parent of each vertex during traversal

int graph[V][V] = {
// 	      a  b  c  d  e  f  g  h  i  j  k
/*a*/    {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
/*b*/    {1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
/*c*/    {0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0},
/*d*/    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
/*e*/    {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
/*f*/    {0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0},
/*g*/    {0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0}
///*h*/    {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1},
///*i*/    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
///*j*/    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
///*k*/    {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},	
};

void BFS(int start_vertex) {
    // Create a queue for BFS
    int queue[V];
    int front = 0, rear = 0;

    // Enqueue the starting vertex
    queue[rear++] = start_vertex;
    visited[start_vertex] = 1;

    // Traverse the graph using BFS
    while (front != rear) {
        // Dequeue a vertex from the queue
        int current_vertex = queue[front++];
        
        // Traverse all adjacent vertices of the current vertex
        for (int i = 0; i < V; i++) {
            // If an adjacent vertex is not visited and there is an edge to it
            if (graph[current_vertex][i] && !visited[i]) {
                // Enqueue the adjacent vertex
                queue[rear++] = i;
                visited[i] = 1;
                // Set the parent of the adjacent vertex
                parent[i] = current_vertex;
            }
        }
    }
}

int main() {
    // Set the number of threads
    omp_set_num_threads(NUM_THREADS);

    // Traverse all vertices and start BFS from each unvisited vertex
    #pragma omp parallel for
    for (int v = 0; v < V; v++) {
        if (!visited[v]) {
            BFS(v);
        }
    }

    // Print the edges of the spanning tree
    printf("\nEdges of the spanning tree:\n");
    for (int i = 1; i < V; i++) {
        printf("(%c, %c)\n", vertexLabels[parent[i]], vertexLabels[i]);
    }

    return 0;
}
