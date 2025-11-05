#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<math.h>

#define MAX_VERTICES 100
#define MAX_EDGES 1000

typedef struct {
    int src, dest;
    double weight;
} Edge;

typedef struct {
    double lat;
    double lon;
} Location;

void bellmanFord(Edge edges[], int V, int E, int src) {
    double dist[MAX_VERTICES];
  
    for (int i = 0; i < V; i++) {
        dist[i] = DBL_MAX; 
    }
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            double w = edges[j].weight;
            if (dist[u] != DBL_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        double w = edges[j].weight;
        if (dist[u] != DBL_MAX && dist[u] + w < dist[v]) {
            printf("Negative weight cycle detected\n");
            return;
        }
    }

    printf("Vertex\tDistance from Source (%d)\n", src);
    for (int i = 0; i < V; i++) {
        if (dist[i] == DBL_MAX)
            printf("%d\tInfinity\n", i);
        else
            printf("%d\t%.4lf\n", i, dist[i]);
    }
}

int main() {
    int V = 7;

    Location locations[MAX_VERTICES] = {
        {21.1466, 79.0888}, // 0 - Zero Mile (Depot)
        {21.1500, 79.0907}, // 1 - Sitabuldi
        {21.1534, 79.0806}, // 2 - Civil Lines
        {21.1612, 79.0948}, // 3 - Sadar
        {21.1445, 79.0613}, // 4 - Dharampeth
        {21.1383, 79.0526}, // 5 - Ambazari
        {21.1462, 79.1166}  // 6 - Itwari
    };

    Edge edges[MAX_EDGES];
    int edgeCount = 0;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j) {
                double dx = locations[i].lat - locations[j].lat;
                double dy = locations[i].lon - locations[j].lon;
                double distance = sqrt(dx * dx + dy * dy);

                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = distance;
                edgeCount++;
            }
        }
    }

    int source = 0; // Zero Mile (Depot)
    bellmanFord(edges, V, edgeCount, source);

    return 0;
}
