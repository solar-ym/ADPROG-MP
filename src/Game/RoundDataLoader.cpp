#include "RoundDataLoader.h"

vector<int> RoundDataLoader :: loadData(int roundNumber) {
    dataFile.open("../../src/Utility/round_data.csv", ios::in);

    vector<int> roundData;

    int n = 1;
    bool running = true;
    string tunnelData;
    char escChar = ',';
    if (roundNumber == 1) escChar = ' ';

    while (getline(dataFile, tunnelData, escChar) && running) {
        if (n == roundNumber && tunnelData != ',') {
            roundData.push_back(stoi(tunnelData));
        }
        if (containsChar(tunnelData, ',')) {
            cout << "[ DATA LOADER ] All data loaded. Terminating." << endl;
            running = false;
        }
        if (n < roundNumber) n++;
        if (n == roundNumber) escChar = ' ';
    }

    dataFile.close();

    return roundData;
}