#include <stdio.h>
#include <limits.h>

#define MAX_NODES 10
#define INFINITY INT_MAX

struct Node {
    int distance[MAX_NODES];
    int next_hop[MAX_NODES];
};

void initialize(struct Node nodes[], int num_nodes, int cost_matrix[][MAX_NODES]) {
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            if (i == j) {
                nodes[i].distance[j] = 0;
                nodes[i].next_hop[j] = j;
            } else if (cost_matrix[i][j] > 0) {
                nodes[i].distance[j] = cost_matrix[i][j];
                nodes[i].next_hop[j] = j;
            } else {
                nodes[i].distance[j] = INFINITY;
                nodes[i].next_hop[j] = -1;
            }
        }
    }
}

void update_routing_table(struct Node nodes[], int num_nodes, int node) {
    int updated = 1;
    while (updated) {
        updated = 0;
        for (int dest = 0; dest < num_nodes; dest++) {
            if (dest == node) continue;
            
            for (int neighbor = 0; neighbor < num_nodes; neighbor++) {
                if (nodes[node].distance[neighbor] == INFINITY || neighbor == node) continue;
                
                int new_distance = nodes[node].distance[neighbor] + nodes[neighbor].distance[dest];
                
                if (new_distance < nodes[node].distance[dest]) {
                    nodes[node].distance[dest] = new_distance;
                    nodes[node].next_hop[dest] = neighbor;
                    updated = 1;
                }
            }
        }
    }
}

void print_routing_table(struct Node nodes[], int num_nodes, int node) {
    printf("\nRouting table for Node %d:\n", node);
    printf("Destination\tDistance\tNext Hop\n");
    for (int i = 0; i < num_nodes; i++) {
        if (nodes[node].distance[i] == INFINITY) {
            printf("%d\t\t∞\t\t-\n", i);
        } else {
            printf("%d\t\t%d\t\t%d\n", i, nodes[node].distance[i], nodes[node].next_hop[i]);
        }
    }
}

int main() {
    int num_nodes;
    printf("Enter number of nodes: ");
    scanf("%d", &num_nodes);

    int cost_matrix[MAX_NODES][MAX_NODES];
    printf("Enter cost matrix (use 0 for no direct connection):\n");
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            scanf("%d", &cost_matrix[i][j]);
            if (cost_matrix[i][j] == 0 && i != j) {
                cost_matrix[i][j] = INFINITY;
            }
        }
    }

    struct Node nodes[MAX_NODES];
    initialize(nodes, num_nodes, cost_matrix);

    // Simulate distance vector updates
    for (int i = 0; i < num_nodes; i++) {
        update_routing_table(nodes, num_nodes, i);
    }

    // Print final routing tables
    for (int i = 0; i < num_nodes; i++) {
        print_routing_table(nodes, num_nodes, i);
    }

    return 0;
}