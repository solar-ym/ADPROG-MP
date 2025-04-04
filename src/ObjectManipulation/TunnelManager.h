#pragma once

#include "../Objects/Tunnel.h"
#include "../Components/MovementComp.h"

/*
    Keeps track of how many tunnels there are in a round.
*/
class TunnelManager {
    private:
        Tunnel* allTunnels[DIRT_HEIGHT][DIRT_WIDTH];
    public:
        TunnelManager();
        void updateTunnels(Tunnel* newTunnel);
        void fullReset();
        bool hasTunnel(int x, int y);
        ~TunnelManager();
};