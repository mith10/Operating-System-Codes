#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

void FCFS(int len_seq, int seq[], int block_size)
{

  list<int> myQueue(block_size, -1);

  int page_fault = 0;

  for (int i = 0; i < len_seq; i++)
  {

    if (find(myQueue.begin(), myQueue.end(), seq[i]) == myQueue.end())
    {
      page_fault += 1;
      myQueue.pop_front();
      myQueue.push_back(seq[i]);
    }
  }

  cout << endl
       << "Page Fault(FCFS):" << page_fault;
}

void LRU(int len_seq, int seq[], int block_size)
{
  vector<int> block(block_size, -1);
  vector<int> block_uses(block_size, 0);

  int page_faults = 0;

  for (int i = 0; i < len_seq; i++)
  {

    auto found_at = find(block.begin(), block.end(), seq[i]);

    if (found_at != block.end())
    {
      block_uses[(found_at - block.begin())] = i;
    }
    else
    {
      page_faults++;
      auto min_it = min_element(block_uses.begin(), block_uses.end());
      int min_index = min_it - block_uses.begin();
      block[min_index] = seq[i];
      block_uses[min_index] = i;
    }
  }

  cout << endl
       << "LRU Page Faults: " << page_faults;
}

void Optimal(int len_seq, int seq[], int block_size)
{
  vector<int> block;
  vector<int> position(block_size, 999);

  int page_faults = 0;

  for (int i = 0; i < len_seq; i++)
  {
    if (find(block.begin(), block.end(), seq[i]) == block.end())
    {

      if (block.size() < block_size)
      {
        block.push_back(seq[i]);
      }
      else
      {

        page_faults++;

        for (int j = 0; j < block_size; j++)
        {
          for (int k = i + 1; k < len_seq; k++)
          {
            if (block[j] == seq[k])
            {
              position[j] = k;
              break;
            }
          }
        }

        auto max_it = max_element(position.begin(), position.end());
        int max_index = max_it - position.begin();
        block[max_index] = seq[i];
      }
    }
  }

  cout << endl
       << "Optimal Page Faults: " << page_faults;
}


int main()
{

  int len_seq = 0;
  cout << "Enter length of input seq: ";
  cin >> len_seq;

  int seq[len_seq];
  cout << "Enter seq separated by space: ";
  for (int i = 0; i < len_seq; i++)
  {
    cin >> seq[i];
  }

  int block_size = 0;
  cout << "enter block size: ";
  cin >> block_size;

  FCFS(len_seq, seq, block_size);
  LRU(len_seq, seq, block_size);
  Optimal(len_seq, seq, block_size);

  cout << endl;

  return 0;
}