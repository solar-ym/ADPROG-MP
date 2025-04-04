#include "RoundDataLoader.h"

/*
    Opens a .csv located in the Utility folder and loads all appropriate data
    into a vector of ints and returns it.

    The csv is organized as such:
        - Every line is a new round
        - Every tunnel is represented by 4 numbers
            - x , y , enemy type, tunnel orientation
            - Therefore a tunnel represented by "10 3 0 1" would be
              located at x - 10, y = 3, extending vertically, with a Pookie enemy
*/
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
            running = false;
        }
        if (n < roundNumber) n++;
        if (n == roundNumber) escChar = ' ';
    }

    dataFile.close();

    return roundData;
}