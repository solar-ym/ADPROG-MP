#include "TunnelManager.h"

TunnelManager :: TunnelManager() {
    for (int i = 0; i < DIRT_HEIGHT; i++) {
        for (int j = 0; j < DIRT_WIDTH; j++) {
            allTunnels[i][j] = nullptr;
        }
    }
}

void TunnelManager :: updateTunnels(Tunnel* newTunnel) {
    int x = newTunnel->getTileX();
    int y = newTunnel->getTileY();

    if (newTunnel == nullptr || allTunnels[y][x] != nullptr)
        cout << "[ ERROR ] Tunnel status invalid." << endl;
    else
        allTunnels[y][x] = newTunnel;
}

void TunnelManager :: fullReset() {
    for (int i = 0; i < DIRT_HEIGHT; i++) {
        for (int j = 0; j < DIRT_WIDTH; j++) {
            allTunnels[i][j] = nullptr;
        }
    }
}

bool TunnelManager :: hasTunnel(int x, int y) {
    if (allTunnels[y][x] == nullptr)
        return false;
    else if ((x >= 0 && x <= 13) && (y >= 0 && y <= 11) )
        return true;
    else
        return false;
}

TunnelManager :: ~TunnelManager() {
}