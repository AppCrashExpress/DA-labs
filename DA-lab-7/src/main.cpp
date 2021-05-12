#include <iostream>
#include <vector>
#include <limits>

typedef long long TCost;

enum TAction {
    actUndef,
    divBy2,
    divBy3,
    sub1
};

// RENAME ME
struct TOptimalNode {
    TAction action;
    TCost   cost;
};

template<typename T>
T min (T a, T b) {
    return a < b ? a : b;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int inputVal;
    std::cin >> inputVal;

    std::vector<TOptimalNode> costFor(inputVal + 1, {actUndef, 0});

    for (int i = 2; i <= inputVal; ++i) {
        TOptimalNode temp {actUndef, std::numeric_limits<TCost>::max()};

        if (i % 3 == 0 && costFor[i / 3].cost < temp.cost) {
            temp = {divBy3, costFor[i / 3].cost};
        }
        if (i % 2 == 0 && costFor[i / 2].cost < temp.cost) {
            temp = {divBy2, costFor[i / 2].cost};
        }
        if (costFor[i - 1].cost < temp.cost) {
            temp = {sub1, costFor[i - 1].cost};
        }

        temp.cost += i;
        costFor[i] = temp;
    }

    std::cout << costFor[inputVal].cost << '\n';
    for (int i = inputVal; i > 1; ) {
        switch(costFor[i].action) {
            case divBy3:
                i /= 3;
                std::cout << "/3 ";
                break;

            case divBy2:
                i /= 2;
                std::cout << "/2 ";
                break;

            case sub1:
                i -= 1;
                std::cout << "-1 ";
                break;

            default:
                throw std::logic_error("Undefined action for value");
                break;
        }
    }
    std::cout << std::endl;
}
