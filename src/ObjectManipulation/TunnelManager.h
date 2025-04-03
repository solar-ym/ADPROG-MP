#pragma once

#include "../Objects/Tunnel.h"
#include "../Components/MovementComp.h"
#include "../Objects/Drillku.h"

class TunnelManager {
    private:
        Tunnel* allTunnels[DIRT_HEIGHT][DIRT_WIDTH];
    public:
        TunnelManager();
        void updateTunnels(Tunnel* newTunnel);
        void fullReset();
        // vector<MovementComp::MOVE_TYPE> observe(int x, int y);
        bool hasTunnel(int x, int y);
        ~TunnelManager();
};