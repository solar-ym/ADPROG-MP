#include "TunnelManager.h"

void TunnelManager :: updateStatus(int x, int y, int newStatus) {
    if (newStatus != 1 && newStatus != 0)
        cout << "[ ERROR ] Tunnel status invalid. Recieved: " << newStatus << endl;
    else
        status[y][x] = newStatus;
}

void TunnelManager :: fullResetStatus() {
    for (int i = 0; i < DIRT_HEIGHT; i++) {
        for (int j = 0; j < DIRT_WIDTH; j++) {
            status[i][j] = 0;
        }
    }
}
//                                                       {UP, DOWN, LEFT, RIGHT}
//                                                       { 0,    1,    2,     3}
Tunnel::TunnelType TunnelManager :: observe(int x, int y, int* adjacencyStatus) {
    int up, down, left, right;

    up = (y != 0) ? status[y-1][x] : -1;
    down = (y != DIRT_HEIGHT-1) ? status[y+1][x] : -1;
    left = (x != 0) ? status[y][x-1] : -1;
    right = (x != DIRT_WIDTH-1) ? status[y][x+1] : -1;
    
    adjacencyStatus[0] = up;
    adjacencyStatus[1] = down;
    adjacencyStatus[2] = left;
    adjacencyStatus[3] = right;
}