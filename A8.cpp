  #include <iostream>
  #include <vector>
  #include <algorithm>
  #include <list>

  using namespace std;

  void FIFO(int no_request, int barrel_size, vector<int> &request, int head_position)
  {

    cout << "FIFO Sequence: " << request[0] << "->";
    int total_dist = 0;

    for (int i = 0; i < (no_request - 1); i++)
    {
      cout << request[i + 1] << "->";
      total_dist += abs(request[i] - request[i + 1]);
    }

    cout << endl
        << "Total distance: " << total_dist << endl;
  }

  // SSTF Disk Scheduling Algorithm
  void SSTF(int no_request, int barrel_size, vector<int> &request, int head_position)
  {

    vector<int> temp = request;
    int total_seek_distance = 0;
    int current_head_position = head_position;

    cout << "SSTF Sequence: ";

    for (int i = 0; i < no_request; i++)
    {
      int min_distance = barrel_size + 1;
      int min_index = -1;

      for (int j = 0; j < temp.size(); j++)
      {
        if (abs(temp[j] - current_head_position) < min_distance)
        {
          min_distance = abs(temp[j] - current_head_position);
          min_index = j;
        }
      }

      total_seek_distance += min_distance;
      cout << temp[min_index] << "->";
      current_head_position = temp[min_index];
      temp.erase(temp.begin() + min_index);
    }

    cout << endl
        << "Total distance: " << total_seek_distance << endl;
  }

  // SCAN
  void SCAN(int no_request, int barrel_size, vector<int> &request, int head_position)
  {

    sort(request.begin(), request.end());

    vector<int> left(request.begin(), find(request.begin(), request.end(), head_position));
    vector<int> right(find(request.begin(), request.end(), head_position), request.end());

    reverse(left.begin(), left.end());
    left.push_back(0);
    right.push_back(barrel_size);

    // combine left and right
    vector<int> final_request;
    final_request.insert(final_request.end(), right.begin(), right.end());
    final_request.insert(final_request.end(), left.begin(), left.end());

    int total_seek_distance = 0;

    cout << "SCAN Sequence: ";
    for (int i = 0; i < final_request.size(); i++)
    {
      total_seek_distance += abs(final_request[i] - final_request[i + 1]);
      cout << final_request[i] << "->";
    }

    cout << endl
        << "Total distance: " << total_seek_distance << endl;
  }

  // c Scan
  void CSCAN(int no_request, int barrel_size, vector<int> &request, int head_position)
  {

    sort(request.begin(), request.end());

    vector<int> final_request;
    final_request.insert(final_request.end(), find(request.begin(), request.end(), head_position), request.end());
    final_request.push_back(barrel_size);
    final_request.push_back(0);
    final_request.insert(final_request.end(), request.begin(), find(request.begin(), request.end(), head_position));

    int total_seek_distance = 0;

    cout << "CSCAN Sequence: ";

    int i = 0;

    for (i = 0; i < final_request.size() - 1; i++)
    {
      total_seek_distance += abs(final_request[i] - final_request[i + 1]);
      cout << final_request[i] << "->";
    }

    cout << endl
        << "Total distance: " << total_seek_distance << endl;
  }

  int main()
  {

    int no_request;
    cout << "Enter number of request: ";
    cin >> no_request;

    int barrel_size;
    cout << "Enter Barel Size: ";
    cin >> barrel_size;

    vector<int> request;

    cout << "Enter requests space separated: ";
    for (int i = 0; i < no_request; i++)
    {
      int req;
      cin >> req;
      request.push_back(req);
    }

    int head_position;
    cout << "Enter head position: ";
    cin >> head_position;

    FIFO(no_request, barrel_size, request, head_position);
    SSTF(no_request, barrel_size, request, head_position);
    SCAN(no_request, barrel_size, request, head_position);
    CSCAN(no_request, barrel_size, request, head_position);
  }
