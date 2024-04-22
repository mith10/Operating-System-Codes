

#include <iostream>
#include <vector>

using namespace std;

int main()
{

  // int no_processes = 5;
  // int no_resources = 4;
  // int total_resources[] = {6, 7, 12, 12};

  // int max_requirment[][4] = {{0, 0, 1, 2},
  //                            {2, 7, 5, 0},
  //                            {6, 6, 5, 0},
  //                            {4, 3, 5, 6},
  //                            {0, 6, 5, 2}};

  // int allocated_resources[][4] = {{0, 0, 1, 2},
  //                                 {2, 0, 0, 0},
  //                                 {0, 0, 3, 4},
  //                                 {2, 3, 5, 4},
  //                                 {0, 3, 3, 2}};

  int no_processes;
  cout << "Enetr the number of processes: ";
  cin >> no_processes;

  int no_resources;
  cout << "Enter the number of resources: ";
  cin >> no_resources;

  int total_resources[no_resources];
  cout << "Enter the total resources: ";
  for (int i = 0; i < no_resources; i++)
  {
    cin >> total_resources[i];
  }

  int max_requirment[no_processes][no_resources];
  for (int i = 0; i < no_processes; i++)
  {

    cout << "Enter the maximum requirment of process " << i + 1 << " : ";

    for (int j = 0; j < no_resources; j++)
    {
      cin >> max_requirment[i][j];
    }
  }

  int allocated_resources[no_processes][no_resources];
  for (int i = 0; i < no_processes; i++)
  {

    cout << "Enter the allocated resources of process " << i + 1 << " : ";

    for (int j = 0; j < no_resources; j++)
    {
      cin >> allocated_resources[i][j];
    }
  }

  int available_resources[no_resources];
  for (int i = 0; i < no_resources; i++)
  {

    available_resources[i] = total_resources[i];
    for (int j = 0; j < no_processes; j++)
    {
      available_resources[i] -= allocated_resources[j][i];
    }
  }

  vector<int> safe_sequence;
  vector<bool> finish(no_processes, false);

  int count = 0;

  while (count < no_processes)
  {
    bool found_sequence = false;

    for (int i = 0; i < no_processes; i++)
    {
      if (!finish[i])
      {
        bool suffecient_resources = true;

        for (int j = 0; j < no_resources; j++)
        {
          if (max_requirment[i][j] - allocated_resources[i][j] > available_resources[j])
          {
            suffecient_resources = false;
            break;
          }
        }

        if (suffecient_resources)
        {
          for (int j = 0; j < no_resources; j++)
          {
            available_resources[j] += allocated_resources[i][j];
          }
          safe_sequence.push_back(i);
          finish[i] = true;
          found_sequence = true;
          count++;
        }
      }
    }

    if (!found_sequence)
    {
      break;
    }
  }

  if (safe_sequence.size() == no_processes)
  {
    cout << "Safe sequence is: ";
    for (int i = 0; i < safe_sequence.size(); i++)
    {
      cout << safe_sequence[i] << " ";
    }
    cout << endl;
  }
  else
  {
    cout << "No safe sequence exists" << endl;
  }

  return 0;
}