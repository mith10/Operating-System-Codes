#include <iostream>
#include <vector>

using namespace std;

int n, m;  // Number of processes and resources

vector<int> available;
vector<vector<int>> maximum;
vector<vector<int>> allocation;
vector<vector<int>> need;

void inputData() {
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;

    available.resize(m);
    maximum.resize(n, vector<int>(m));
    allocation.resize(n, vector<int>(m));
    need.resize(n, vector<int>(m));

    cout << "Enter the number of available instances of each resource:" << endl;
    for (int j = 0; j < m; j++) {
        cout << "Resource R" << j << ": ";
        cin >> available[j];
    }

    cout << "Enter the maximum demand of each process:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "For process P" << i << ":" << endl;
        for (int j = 0; j < m; j++) {
            cout << "Resource R" << j << ": ";
            cin >> maximum[i][j];
        }
    }

    cout << "Enter the current allocation of each process:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "For process P" << i << ":" << endl;
        for (int j = 0; j < m; j++) {
            cout << "Resource R" << j << ": ";
            cin >> allocation[i][j];
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

void printMatrix(const vector<vector<int>>& matrix, const string& name) {
    cout << name << " matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isSafe() {
    vector<int> work = available;
    vector<bool> finish(n, false);
    vector<int> safeSequence;

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safeSequence.push_back(i);
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            cout << "System is not in a safe state!" << endl;
            return false;
        }
    }

    cout << "System is in a safe state. Safe sequence: ";
    for (int i = 0; i < n - 1; i++) {
        cout << "P" << safeSequence[i] << " -> ";
    }
    cout << "P" << safeSequence[n - 1] << endl;

    return true;
}


int main() {
    inputData();

    printMatrix(maximum, "Maximum Need");
    printMatrix(allocation, "Current Allocation");
    printMatrix(need, "Remaining Need");

    isSafe();

    return 0;
}
