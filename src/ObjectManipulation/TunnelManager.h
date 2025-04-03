#pragma once

#include "../Objects/Tunnel.h"
#include "../Components/MovementComp.h"
#include "../Objects/Drillku.h"

class TunnelManager {
    private:
        Tunnel* allTunnels[DIRT_HEIGHT][DIRT_WIDTH];
    public:
        TunnelManager();
        void updateTunnels(int x, int y, Tunnel* newTunnel);
        void fullReset();
        Tunnel::TunnelType observe(int x, int y, vector<int> available);
        ~TunnelManager();
};