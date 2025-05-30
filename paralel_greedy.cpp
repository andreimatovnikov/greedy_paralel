#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

struct Item {
    int value;
    int weight;
    double ratio;
    int index;
};

int main() {
    int n, W;
    std::cin >> n >> W;

    std::vector<Item> items(n);

#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        std::cin >> items[i].value >> items[i].weight;
        items[i].index = i;
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
        });

    int total_weight = 0, total_value = 0;
    std::vector<int> taken;

    for (const auto& item : items) {
        if (total_weight + item.weight <= W) {
            total_weight += item.weight;
            total_value += item.value;
            taken.push_back(item.index);
        }
    }

    std::cout << total_value << std::endl;
    for (int idx : taken)
        std::cout << idx << " ";
    std::cout << std::endl;

    return 0;
}