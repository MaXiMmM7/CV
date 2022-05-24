#include <iostream>
#include <vector>
#include<fstream>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <tuple>
#include <time.h>
#include <iostream>
using namespace std;

void placeParticle(vector<vector<int>> &matrix, int row, int col);
tuple<int, int> getRandomParticleLocation(vector<vector<int> > &matrix);
bool isValidLocation(vector<vector<int> > &matrix, int row, int col);
void randomWalk(vector<vector<int> > &matrix, int& row, int& col);
bool isOutOfbounds(vector<vector<int> > &matrix, int row, int col);
bool adjacentToGrowingCrystal(vector<vector<int> > &matrix, int row, int col);
bool exceededNumMoves(int numMoves);
bool increaseRadius(int row, int col);
void printMatrix(vector<vector<int> > matrix);

//int ROWS = 71;
//int COLS = 71;


int ROWS = 71;
int COLS = 71;

int MAXMOVES =100;
int ORIGINROW = ROWS / 2;
int ORIGINCOL = ROWS / 2;
int RADIUS = 0;

int main(int argc, char **argv) {
    srand (time(0));
    unsigned long numParticles = 2000;
    vector<int> singleRow(COLS, 0);
    vector<vector<int> > simulationGrid(ROWS, singleRow);

    simulationGrid[ORIGINROW][ORIGINCOL] = 1;

    for (unsigned long p = 0; p < numParticles; p++) {
        if (RADIUS >= ORIGINROW - 1) {
            cout << "Radius is " << RADIUS << ", so the simulation is done." << endl;
            break;
        }

        const auto point = getRandomParticleLocation(simulationGrid);
        int row = std::get<0>(point);
        int col = std::get<1>(point);

        randomWalk(simulationGrid, row, col);
    }
    printMatrix(simulationGrid);

    {const string res="tree.txt";
    ofstream output(res);
    output << left;
    for(int i = 0; i < static_cast<int>(simulationGrid.size()); i++) {
                for(int j = 0; j < static_cast<int>(simulationGrid[i].size()); j++) {
                	if(simulationGrid[i][j]==1){
                		output << "*";
                	}
                	else{
                		output << " ";
                	}

                }
               output << "\n";
            }

    }

}

void placeParticle(vector<vector<int> > &matrix, int row, int col) {
    matrix[row][col] = 1;
    return;
}

tuple<int, int> getRandomParticleLocation(vector<vector<int> > &matrix) {
    bool particlePlaced = false;
    while (!particlePlaced) {
        int randomRow = rand() % matrix.size();
        int randomCol = rand() % matrix[0].size();
        if (matrix[randomRow][randomCol] == 0){
            particlePlaced = true;
            return make_tuple(randomRow, randomCol);
        }
    }
}

bool isValidLocation(vector<vector<int> > &matrix, int row, int col) {
    if ((row == ORIGINROW && col == ORIGINCOL) ||
            (abs(ORIGINROW - row) <= (RADIUS + 1)) ||
            (abs(ORIGINCOL - col) <= (RADIUS + 1))) {
        return false;
    }
    else {
        return true;
    }
}

void randomWalk(vector<vector<int> > &matrix, int &x, int &y) {
    while (x >= 0 && x < COLS && y >= 0 && y < ROWS) {
        /* check if should stick */
        if (adjacentToGrowingCrystal(matrix, x, y)) {
            matrix[x][y] = 1;
            return;
        }

        /* generate next move */
        // const std::tuple<int, int> direction = nextMove(generator);
        const int dx = rand() % 3 - 1;
        const int dy = rand() % 3 - 1;

        x += dx;
        y += dy;
    }
}

bool isOutOfbounds(vector<vector<int> > &matrix, int row, int col) {
    return row < 0 || col < 0 || row > matrix.size() - 1 || col > matrix[0].size() - 1;
}


bool adjacentToGrowingCrystal(vector<vector<int> > &matrix, int row, int col) {
    for (int dRow = -1; dRow <= 1; dRow++) {
        for (int dCol = -1; dCol <= 1; dCol++) {
            int newRow = row + dRow;
            int newCol = col + dCol;
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
                if (matrix[newRow][newCol] == 1) {
                    return true;
                }
            }
        }
    }
    return false;

}

bool exceededNumMoves(int numMoves) {
    return (numMoves > MAXMOVES);
}

bool increaseRadius(int row, int col) {
    if ((abs(ORIGINROW - row) > RADIUS || (abs(ORIGINCOL - col) > RADIUS))) {
        return true;
    }
    return false;
}

void printMatrix(vector<vector<int> > matrix) {
    for(int i = 0; i < static_cast<int>(matrix.size()); i++) {
        for(int j = 0; j < static_cast<int>(matrix[i].size()); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
