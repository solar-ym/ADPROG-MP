#pragma once

#include "iostream"
#include "../Utility/configurations.h"
#include "fstream"

class RoundDataLoader {
    private:
        fstream dataFile;
    public:
        vector<int> loadData(int roundNumber);
};