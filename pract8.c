#include <stdio.h> 
 
int isSafe(int v, int graph[20][20], int color[], int c, int V) { 
    for (int i = 0; i < V; i++) 
        if (graph[v][i] && color[i] == c) 
            return 0; 
    return 1; 
} 
 
int solve(int graph[20][20], int m, int color[], int v, int V) { 
    if (v == V) 
        return 1; 
 
    for (int c = 1; c <= m; c++) { 
        if (isSafe(v, graph, color, c, V)) { 
            color[v] = c; 
            if (solve(graph, m, color, v + 1, V)) 
                return 1; 
            color[v] = 0; 
        } 
    } 
    return 0; 
} 
 
int main() { 
    int V, m; 
    int graph[20][20], color[20] = {0}; 
 
    printf("Enter number of vertices: "); 
    scanf("%d", &V); 
 
    printf("Enter adjacency matrix:\n"); 
    for (int i = 0; i < V; i++) 
        for (int j = 0; j < V; j++) 
            scanf("%d", &graph[i][j]); 
 
    printf("Enter number of colors: "); 
    scanf("%d", &m); 
 
    if (!solve(graph, m, color, 0, V)) { 
        printf("No solution\n"); 
        return 0; 
    } 
 
    printf("Assigned Colors:\n"); 
    for (int i = 0; i < V; i++) 
        printf("Vertex %d -> Color %d\n", i, color[i]); 
 
    return 0; 
} 
