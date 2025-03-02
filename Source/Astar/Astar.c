#include "Astar.h"

extern char map[ROWS][COLS];
extern GHOST_STATE ghost_status;

int visited[ROWS][COLS];  // Array to keep track of visited nodes
Node allNodes[MAX_NODES];  // Array to store all nodes
int allNodesCount = 0;     // Counter for the next available node
Node* openList[MAX_NODES];  // List of nodes to explore
int openListSize = 0;  // Number of nodes in the open list

// Function to calculate the Manhattan distance (heuristic)
int heuristic(map_pos a, map_pos b) {
    return abs(a.i - b.i) + abs(a.j - b.j);
}

// Function to check if a position is valid (inside the map and not a wall)
int aisValid(int x, int y) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && map[x][y] != '#');
}

// Function to insert a node into the open list in order of f
void insertNodeInOpenList(Node* node) {
    openList[openListSize++] = node;

    // Sort the list by f (from smallest to largest)
    int i;
    for (i = openListSize - 1; i > 0; i--) {
        if (openList[i]->f < openList[i - 1]->f) {
            Node* temp = openList[i];
            openList[i] = openList[i - 1];
            openList[i - 1] = temp;
        } else {
            break;
        }
    }
}

// Function to extract the node with the minimum f from the open list
Node* extractMinNode() {
    if (openListSize == 0) {
        return NULL;
    }

    Node* minNode = openList[0];

    // Remove the first node (minimum f)
    int i;
    for (i = 1; i < openListSize; i++) {
        openList[i - 1] = openList[i];
    }
    openListSize--;

    return minNode;
}

// A* algorithm without heap and malloc
Node* aStar(map_pos start, map_pos goal) {
    openListSize = 0;
    allNodesCount = 0;
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            visited[i][j] = 0;
        }
    }

    // Create the start node and add it to the open list
    Node* startNode = &allNodes[allNodesCount++];
    startNode->pos = start;
    startNode->g = 0;
    startNode->h = heuristic(start, goal);
    startNode->f = startNode->g + startNode->h;
    startNode->parent = NULL;

    insertNodeInOpenList(startNode);
    visited[start.i][start.j] = 1;

    // Main A* loop
    while (openListSize > 0) {
        Node* current = extractMinNode();

        // If we reached the goal, return the path
        if (current->pos.i == goal.i && current->pos.j == goal.j) {
            return current;
        }

        // Examine the 4 neighbors (up, down, left, right)
        map_pos directions[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (i = 0; i < 4; i++) {
            map_pos neighbor = {current->pos.i + directions[i].i, current->pos.j + directions[i].j};

            // Check if the neighbor is valid and not visited
            if (aisValid(neighbor.i, neighbor.j) && !visited[neighbor.i][neighbor.j]) {
                Node* neighborNode = &allNodes[allNodesCount++];
                neighborNode->pos = neighbor;
                neighborNode->g = current->g + 1;
                neighborNode->h = heuristic(neighbor, goal);
                neighborNode->f = neighborNode->g + neighborNode->h;
                neighborNode->parent = current;

                insertNodeInOpenList(neighborNode);
                visited[neighbor.i][neighbor.j] = 1;
            }
        }
    }

    return NULL;  // No path found
}

// Function to get the next move of the ghost
void aggiornaPercorsoFantasma(map_pos *fantasmaPos, map_pos pacManPos) {
    allNodesCount = 0;
    openListSize = 0;
    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            visited[i][j] = 0;
        }
    }

    // Calculate the path using A* towards Pac-Man's position
    Node* goalNode = aStar(*fantasmaPos, pacManPos);

    if (goalNode != NULL) {
        Node* currentNode = goalNode;
        Node* previousNode = NULL;

        // Trace back to find the first move
        while (currentNode->parent != NULL) {
            previousNode = currentNode;
            currentNode = currentNode->parent;
        }

        // Now previousNode is the first move
        if (previousNode != NULL) {
            map_pos nextPos = previousNode->pos;

            // Ensure the ghost moves only if the position has changed
            if (fantasmaPos->i != nextPos.i || fantasmaPos->j != nextPos.j) {
                if (nextPos.i > fantasmaPos->i) {
                    fantasmaPos->i++;
                } else if (nextPos.i < fantasmaPos->i) {
                    fantasmaPos->i--;
                } else if (nextPos.j > fantasmaPos->j) {
                    fantasmaPos->j++;
                } else if (nextPos.j < fantasmaPos->j) {
                    fantasmaPos->j--;
                }
            }
        }
    }
}
