#include <functional>
#include <thread>
#include <vector>

const uint8_t workerAmount = 2;
std::vector<std::thread> workers;

void parallel_loop(uint32_t amount, std::function<void(uint32_t)> func) {

    for (int workerSlot = 0; workerSlot < workerAmount; workerSlot++) {
        int min = amount * workerSlot / workerAmount;
        int max = amount * (workerSlot + 1) / workerAmount;

        workers.push_back(std::thread([&]() {
            for (int i = min; i < max; i++) {
                func(i);
            }
        }));
    }
}

void parallel_join_all_workers() {
    for(std::thread& v : workers) {
        v.join();
    }
}