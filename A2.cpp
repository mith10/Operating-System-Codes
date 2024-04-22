#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Process
{
  int process_id;
  int arrival_time;
  int burst_time;
  int completion_time;
  int waiting_time;
  int turnaround_time;
  int priority;
};

void print_results(std::vector<Process> processes)
{

  std::cout << "\nProcess ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n";
  for (int i = 0; i < processes.size(); i++)
  {
    std::cout << processes[i].process_id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].priority << "\t\t" << processes[i].completion_time << "\t\t" << processes[i].waiting_time << "\t\t" << processes[i].turnaround_time << "\n";
  }

  double avg_waiting_time = 0;
  double avg_turnaround_time = 0;

  for (int i = 0; i < processes.size(); i++)
  {
    avg_waiting_time += processes[i].waiting_time;
    avg_turnaround_time += processes[i].turnaround_time;
  }


  std::cout << "\nAverage Waiting Time: " << avg_waiting_time / processes.size() << "\n";
  std::cout << "Average Turnaround Time: " << avg_turnaround_time / processes.size() << "\n";
}

void fcfs(std::vector<Process> processes)
{

  // calculate completion time
  int current_time = 0;

  for (int i = 0; i < processes.size(); i++)
  {

    if (current_time < processes[i].arrival_time)
    {
      current_time = processes[i].arrival_time;
    }

    processes[i].completion_time = current_time + processes[i].burst_time;
    current_time = processes[i].completion_time;
  }

  // calculate waiting time and turnaround time

  for (int i = 0; i < processes.size(); i++)
  {
    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
  }

  print_results(processes);
}

void sjf(vector<Process> processes){
  
  int current_time = 0;
  for(int i = 0; i < processes.size(); i++){

    if(current_time < processes[i].arrival_time){
      current_time = processes[i].arrival_time;
    }

    int min_burst_time = processes[i].burst_time;
    int min_burst_time_index = i;

    for(int j = i; j < processes.size(); j++){
      if(processes[j].arrival_time <= current_time && processes[j].burst_time < min_burst_time){
        min_burst_time = processes[j].burst_time;
        min_burst_time_index = j;
      }
    }

    Process temp = processes[i];
    processes[i] = processes[min_burst_time_index];
    processes[min_burst_time_index] = temp;

    processes[i].completion_time = current_time + processes[i].burst_time;
    current_time = processes[i].completion_time;
  }

  for(int i = 0; i < processes.size(); i++){
    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
  }

  print_results(processes);

}

void priority(vector<Process> processes){
  
  int current_time = 0;
  for(int i = 0; i < processes.size(); i++){

    if(current_time < processes[i].arrival_time){
      current_time = processes[i].arrival_time;
    }

    int min_priority = processes[i].priority;
    int min_priority_index = i;

    for(int j = i; j < processes.size(); j++){
      if(processes[j].arrival_time <= current_time && processes[j].priority < min_priority){
        min_priority = processes[j].priority;
        min_priority_index = j;
      }
    }

    Process temp = processes[i];
    processes[i] = processes[min_priority_index];
    processes[min_priority_index] = temp;

    processes[i].completion_time = current_time + processes[i].burst_time;
    current_time = processes[i].completion_time;
  }

  for(int i = 0; i < processes.size(); i++){
    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
  }

  print_results(processes);

}

void round_robin(vector<Process> processes, int quantum){
  
  int current_time = 0;
  int n = processes.size();
  int remaining_burst_time[n];
  for(int i = 0; i < n; i++){
    remaining_burst_time[i] = processes[i].burst_time;
  }

  while(true){
    bool done = true;
    for(int i = 0; i < n; i++){
      if(remaining_burst_time[i] > 0){
        done = false;
        if(remaining_burst_time[i] > quantum){
          current_time += quantum;
          remaining_burst_time[i] -= quantum;
        }else{
          current_time += remaining_burst_time[i];
          remaining_burst_time[i] = 0;
          processes[i].completion_time = current_time;
        }
      }
    }

    if(done){
      break;
    }
  }

  for(int i = 0; i < n; i++){
    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
  }

  print_results(processes);
}

int main()
{
  int n, choice;
  std::cout << "Enter the number of processes: ";
  std::cin >> n;

  std::vector<Process> processes(n);

  std::cout << "\nEnter the arrival time, burst time, and priority for each process:\n";
  for (int i = 0; i < n; i++)
  {
    processes[i].process_id = i + 1;
    std::cout << "\nProcess " << i + 1 << "\n";
    std::cout << "Arrival Time: ";
    std::cin >> processes[i].arrival_time;
    std::cout << "Burst Time: ";
    std::cin >> processes[i].burst_time;
    std::cout << "Priority: ";
    std::cin >> processes[i].priority;
  }

  // sort the processes based on arrival time
  std::sort(processes.begin(), processes.end(), [](Process a, Process b) {
    return a.arrival_time < b.arrival_time;
  });

  cout << "\nFCFS\n";
  fcfs(processes);

  cout << "\nSJF\n";
  sjf(processes);

  cout << "\nPriority\n";
  priority(processes);

  cout << "\nRound Robin\n";
  int quantum;
  std::cout << "Enter the time quantum for Round Robin: ";
  std::cin >> quantum;
  round_robin(processes, quantum);

  return 0;
}
