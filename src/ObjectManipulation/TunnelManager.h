#pragma once

#include "../Objects/Tunnel.h"
#include "../Components/MovementComp.h"
#include "../Objects/Drillku.h"

class TunnelManager {
    private:
        Drillku* player;
        Tunnel* currentTunnel;
    public:
        void dig(vector<GameObject*> sceneObjects);
        Tunnel* createTunnel(Tunnel::TunnelType stage);
};