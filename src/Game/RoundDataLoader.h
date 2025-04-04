#pragma once

#include "iostream"
#include "../Utility/configurations.h"
#include "fstream"

// Used to load round data (starting tunnels and enemies)
class RoundDataLoader {
    private:
        fstream dataFile;
    public:
        vector<int> loadData(int roundNumber);
};