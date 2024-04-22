#include <iostream> 
#include <vector> 
#include <algorithm> 
using namespace std; 
 
class MemoryAllocation 
{ 
    vector<int> memory; 
    vector<int> process; 
    vector<pair<int, int>> memory_allocated; // Pair of block index and size 
    vector<pair<int, int>> process_allocated; // Pair of process index and 
size 
    int memory_size; 
    int process_size; 
 
public: 
    MemoryAllocation() 
    { 
        memory_size = 0; 
        process_size = 0; 
    } 
 
    void input() 
    { 
        cout << "Enter the number of memory blocks: "; 
        cin >> memory_size; 
        cout << "Enter the memory blocks: "; 
        for (int i = 0; i < memory_size; i++) 
        { 
            int temp; 
            cin >> temp; 
            memory.push_back(temp); 
        } 
        cout << "Enter the number of processes: "; 
        cin >> process_size; 
        cout << "Enter the processes: "; 
        for (int i = 0; i < process_size; i++) 
        { 
            int temp; 
            cin >> temp; 
            process.push_back(temp); 
        } 
    } 
 
    void first_fit() 
    { 
        memory_allocated.clear(); 
        process_allocated.clear(); 
        for (int i = 0; i < process_size; i++) 
        { 
            for (int j = 0; j < memory_size; j++) 
            { 
                if (process[i] <= memory[j]) 
                { 
                    memory_allocated.push_back({j, process[i]}); 
                    process_allocated.push_back({i, process[i]}); 
                    memory[j] -= process[i]; 
                    break; 
                } 
            } 
        } 
    } 
 
    void best_fit() 
    { 
        memory_allocated.clear(); 
        process_allocated.clear(); 
        for (int i = 0; i < process_size; i++) 
        { 
            int min_size = 9999; 
            int index = -1; 
            for (int j = 0; j < memory_size; j++) 
            { 
                if (process[i] <= memory[j] && memory[j] < min_size) 
                { 
                    min_size = memory[j]; 
                    index = j; 
                } 
            } 
            if (index != -1) 
            { 
                memory_allocated.push_back({index, process[i]}); 
                process_allocated.push_back({i, process[i]}); 
                memory[index] -= process[i]; 
            } 
        } 
    } 
 
    void next_fit() 
    { 
        memory_allocated.clear(); 
        process_allocated.clear(); 
        int start_index = 0; 
        for (int i = 0; i < process_size; i++) 
        { 
            for (int j = start_index; j < memory_size; j++) 
            { 
                if (process[i] <= memory[j]) 
                { 
                    memory_allocated.push_back({j, process[i]}); 
                    process_allocated.push_back({i, process[i]}); 
                    memory[j] -= process[i]; 
                    start_index = j; // Set next start index 
                    break; 
                } 
            } 
        } 
    } 
 
    void worst_fit() 
    { 
        memory_allocated.clear(); 
        process_allocated.clear(); 
         
        vector<bool> block_allocated(memory_size, false); // To track if a 
block is already allocated 
         
        for (int i = 0; i < process_size; i++) 
        { 
            int max_size = -1; 
            int index = -1; 
             
            for (int j = 0; j < memory_size; j++) 
            { 
                if (!block_allocated[j] && process[i] <= memory[j] && 
memory[j] > max_size) 
                { 
                    max_size = memory[j]; 
                    index = j; 
                } 
            } 
             
            if (index != -1) 
            { 
                memory_allocated.push_back({index, process[i]}); 
                process_allocated.push_back({i, process[i]}); 
                memory[index] -= process[i]; 
                block_allocated[index] = true; // Mark the block as allocated 
            } 
        } 
    } 
 
    void deallocateMemory() 
    { 
        for (auto& alloc : memory_allocated) 
        { 
            memory[alloc.first] += alloc.second; 
        } 
        memory_allocated.clear(); 
        process_allocated.clear(); 
    } 
 
    void display() 
{ 
    cout << "Memory Blocks: "; 
    for (int i = 0; i < memory_size; i++) 
    { 
        cout << memory[i] << " "; 
    } 
    cout << endl; 
    cout << "Processes: "; 
    for (int i = 0; i < process_size; i++) 
    { 
        cout << process[i] << " "; 
    } 
    cout << endl; 
    cout << "\nProcesses Allocation:"; 
    for (size_t i = 0; i < process_allocated.size(); i++) 
    { 
        cout << "\nprocess " << process_allocated[i].first + 1 << " "; 
        cout << "allocated to block " << memory_allocated[i].first + 1 << " "; 
    } 
    cout << endl; 
} 
}; 
 
int main() 
{ 
    MemoryAllocation m; 
    m.input(); 
 
    m.first_fit(); 
    cout << "First Fit: " << endl; 
    m.display(); 
    m.deallocateMemory(); 
 
    m.best_fit(); 
    cout << "\n\nBest Fit: " << endl; 
    m.display(); 
    m.deallocateMemory(); 
 
    m.next_fit(); 
cout << "\n\nNext Fit: " << endl; 
m.display(); 
m.deallocateMemory(); 
m.worst_fit(); 
cout << "\n\nWorst Fit: " << endl; 
m.display(); 
return 0; 
} 