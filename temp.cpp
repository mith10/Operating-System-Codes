//  Not working



#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

std::mutex mtx;
int readers = 0, writers = 0, resource = 0;

void syncReader(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    while (writers > 0)
        std::cout << "Reader " << id << " waits as a writer is writing\n";
    ++readers;
    lock.unlock();

    // Read
    std::this_thread::sleep_for(std::chrono::seconds(1));
    lock.lock();
    --readers;
}

void syncWriter(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    while (readers > 0 || writers > 0)
        std::cout << "Writer " << id << " waits for readers/writers\n";
    ++writers;

    // Write
    resource = id;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    --writers;
}

void asyncReader(int id) {
    // Read
    std::cout << "Reader " << id << " reads\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void asyncWriter(int id) {
    // Write
    resource = id;
    std::cout << "Writer " << id << " writes\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void runSync(int numReaders, int numWriters) {
    std::vector<std::thread> threads;

    for (int i = 1; i <= numReaders; ++i)
        threads.emplace_back(syncReader, i);

    for (int i = 1; i <= numWriters; ++i)
        threads.emplace_back(syncWriter, i);

    for (auto& t : threads)
        t.join();
}

void runAsync(int numReaders, int numWriters) {
    std::vector<std::thread> threads;

    for (int i = 1; i <= numReaders; ++i)
        threads.emplace_back(asyncReader, i);

    for (int i = 1; i <= numWriters; ++i)
        threads.emplace_back(asyncWriter, i);

    for (auto& t : threads)
        t.join();
}

int main() {
    int numReaders, numWriters, mode;
    std::cout << "Enter number of readers: ";
    std::cin >> numReaders;
    std::cout << "Enter number of writers: ";
    std::cin >> numWriters;
    std::cout << "Enter mode (1 for sync, 2 for async): ";
    std::cin >> mode;

    if (mode == 1)
        runSync(numReaders, numWriters);
    else if (mode == 2)
        runAsync(numReaders, numWriters);
    else
        std::cout << "Invalid mode\n";

    return 0;
}
