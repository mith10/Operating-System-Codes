#include <iostream>
#include <vector>
#include <map>

using namespace std;

void FirstFit(vector<int> processes, vector<int> blocks)
{

  vector<int> allocation(blocks.size(), -1);
  for (int i = 0; i < processes.size(); i++)
  {
    for (int j = 0; j < blocks.size(); j++)
    {
      if (blocks[j] >= processes[i] && allocation[j] == -1)
      {
        allocation[j] = i;
        blocks[j] -= processes[i];
        break;
      }
    }
  }

  cout << "------------------------------------------------------------------"
       << endl
       << "First Fit Allocation: \n"
       << endl;
  cout << "Block No.\tProcess No.\tProcess Size\tRemaining_block_Size\n";
  for (int i = 0; i < blocks.size(); i++)
  {
    cout << i + 1 << "\t\t" << allocation[i] + 1 << "\t\t" << processes[allocation[i]] << "\t\t" << blocks[i] << endl;
  }
}

void BestFit(vector<int> processes, vector<int> blocks)
{
  vector<int> allocation(blocks.size(), -1);
  map<int, int> allocation_map;

  for (int i = 0; i < processes.size(); i++)
  {
    int best_index = -1;

    for (int j = 0; j < blocks.size(); j++)
    {
      if (allocation[j] == -1 && blocks[j] >= processes[i] && (best_index == -1 || blocks[j] < blocks[best_index]))
      {
        best_index = j;
      }
    }

    if (best_index != -1)
    {
      allocation[best_index] = i;
      blocks[best_index] -= processes[i];
      allocation_map[i + 1] = best_index + 1;
    }
  }

  cout << "------------------------------------------------------------------"
       << endl
       << "Best Fit Allocation: \n"
       << endl;
  cout << "Block No.\tProcess No.\tProcess Size\tRemaining_block_Size\n";

  for (auto it = allocation_map.begin(); it != allocation_map.end(); it++)
  {
    cout << it->second << "\t\t" << it->first << "\t\t" << processes[it->first - 1] << "\t\t" << blocks[it->second - 1] << endl;
  }
}

void WorstFit(vector<int> processes, vector<int> blocks)
{
  vector<int> allocation(blocks.size(), -1);
  map<int, int> allocation_map;

  for (int i = 0; i < processes.size(); i++)
  {
    int worst_index = -1;

    for (int j = 0; j < blocks.size(); j++)
    {
      if (allocation[j] == -1 && blocks[j] >= processes[i] && (worst_index == -1 || blocks[j] > blocks[worst_index]))
      {
        worst_index = j;
      }
    }

    if (worst_index != -1)
    {
      allocation[worst_index] = i;
      blocks[worst_index] -= processes[i];
      allocation_map[i + 1] = worst_index + 1;
    }
  }

  cout << "------------------------------------------------------------------"
       << endl
       << "Worst Fit Allocation: \n"
       << endl;
  cout << "Block No.\tProcess No.\tProcess Size\tRemaining_block_Size\n";

  for (auto it = allocation_map.begin(); it != allocation_map.end(); it++)
  {
    cout << it->second << "\t\t" << it->first << "\t\t" << processes[it->first - 1] << "\t\t" << blocks[it->second - 1] << endl;
  }
}

void NextFit(vector<int> processes, vector<int> blocks)
{
  vector<int> allocation(blocks.size(), -1);
  map<int, int> allocation_map;

  int allocation_index;
  cout << "------------------------------------------------------------------"<< endl;
  cout << "Enter the index of the block to start allocation from: ";
  cin >> allocation_index;

  for (int i = 0; i < processes.size(); i++)
  {
    for (int j = allocation_index % blocks.size(); j < blocks.size(); j++)
    {
      if (blocks[j] >= processes[i] && allocation[j] == -1)
      {
        allocation[j] = i;
        blocks[j] -= processes[i];
        allocation_map[i + 1] = j + 1;
        allocation_index = j;
        break;
      }
    }
  }

  cout << "------------------------------------------------------------------"
       << endl
       << "Next Fit Allocation: \n"
       << endl;
  cout << "Block No.\tProcess No.\tProcess Size\tRemaining_block_Size\n";

  for (auto it = allocation_map.begin(); it != allocation_map.end(); it++)
  {
    cout << it->second << "\t\t" << it->first << "\t\t" << processes[it->first - 1] << "\t\t" << blocks[it->second - 1] << endl;
  }
}

int main()
{

  int no_processes;
  cout << "------------------------------------------------------------------"<< endl;
  cout << "Enter the number of processes: ";
  cin >> no_processes;

  vector<int> processes(no_processes);

  cout << "Enter the burst time of each process: ";
  for (int i = 0; i < no_processes; i++)
  {
    cin >> processes[i];
  }

  int no_blocks;
  cout << "Enter the number of blocks: ";
  cin >> no_blocks;

  vector<int> blocks(no_blocks);

  cout << "Enter the size of each block: ";
  for (int i = 0; i < no_blocks; i++)
  {
    cin >> blocks[i];
  }

  FirstFit(processes, blocks);
  BestFit(processes, blocks);
  WorstFit(processes, blocks);
  NextFit(processes, blocks);
}