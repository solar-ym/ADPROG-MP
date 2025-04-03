#include "TunnelManager.h"

TunnelManager :: TunnelManager() {
    for (int i = 0; i < DIRT_HEIGHT; i++) {
        for (int j = 0; j < DIRT_WIDTH; j++) {
            allTunnels[i][j] = nullptr;
        }
    }
}

void TunnelManager :: updateTunnels(Tunnel* newTunnel) {
    // cout << "[Tunnel Manager] : Updating tile" << endl;
    int x = newTunnel->getTileX();
    int y = newTunnel->getTileY();
    // cout << "   > X: " << x << "\n  > Y: " << y << endl;
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

// vector<MovementComp::MOVE_TYPE> TunnelManager :: observe(int x, int y) {
//     vector<MovementComp::MOVE_TYPE> available;
//     Tunnel* observing = allTunnels[y][x];
//     Tunnel::TunnelType type = observing->getTunnelType();
//     Angle rotation = observing->getSprite()->getRotation();

//     cout << "Rotation recieved: " << rotation.asDegrees() << endl;

//     if (type == Tunnel::CAP) {
//         if (rotation == degrees(90)) {

//         }
//     } else if (type == Tunnel::CORNER) {

//     } else if (type == Tunnel::STRAIGHT) {

//     }

// }

bool TunnelManager :: hasTunnel(int x, int y) {
    // cout << "[Tunnel Manager] : Getting Status" << endl;
    if (allTunnels[y][x] == nullptr)
        return false;
    else 
        return true;
}

TunnelManager :: ~TunnelManager() {
}