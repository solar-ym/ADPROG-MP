#include "TunnelManager.h"

void TunnelManager :: dig(vector<GameObject*> sceneObjects) {
    MovementComp::MOVE_TYPE isFacing = player->getMoveComp()->isFacing();
    
    
}

Tunnel*  TunnelManager :: createTunnel(Tunnel::TunnelType stage) {
    Tunnel* newTunnel = new Tunnel(stage);

}