#include "TunnelManager.h"

TunnelManager :: TunnelManager() {
    for (int i = 0; i < DIRT_HEIGHT; i++) {
        for (int j = 0; j < DIRT_WIDTH; j++) {
            allTunnels[i][j] = nullptr;
        }
    }
}

void TunnelManager :: updateTunnels(int x, int y, Tunnel* newTunnel) {
    if (allTunnels[y][x] == nullptr)
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

Tunnel::TunnelType TunnelManager :: observe(int x, int y, vector<int> available) {
    Tunnel* observing = allTunnels[y][x];
    Tunnel::TunnelType type = observing->getTunnelType();
    Angle rotation = observing->getSprite()->getRotation();

    if (type == Tunnel::CAP) {
        if (rotation == degrees(90)) {

        }
    } else if (type == Tunnel::CORNER) {

    } else if (type == Tunnel::STRAIGHT) {

    }

}

TunnelManager :: ~TunnelManager() {
    delete allTunnels;
}