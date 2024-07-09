#include "KDTree.h"
#include <iostream>

int main() {
    KDTree tree;
    std::vector<std::vector<float>> points = {
            {3, 6}, {17, 15}, {13, 15}, {6, 12}, {9, 1}, {2, 7}, {10, 19}
    };

    for (const auto& point : points) {
        tree.insert(point);
    }

    std::vector<float> pointToSearch = {10, 19};
    if (tree.search(pointToSearch)) {
        std::cout << "Point found\n";
    } else {
        std::cout << "Point not found\n";
    }

    tree.deletePoint(pointToSearch);
    if (tree.search(pointToSearch)) {
        std::cout << "Point found\n";
    } else {
        std::cout << "Point not found\n";
    }

    return 0;
}
