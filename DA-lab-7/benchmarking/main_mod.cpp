#include <iostream>
#include <vector>
#include <limits>

#include <chrono>

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

    for (int inputVal = 1192762; inputVal < 1192763 + 20; ++inputVal) {
        std::vector<TOptimalNode> costFor(inputVal + 1, {actUndef, 0});

        auto start = std::chrono::high_resolution_clock::now();

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

        // std::cout << costFor[inputVal].cost << '\n';
        for (int i = inputVal; i > 1; ) {
            switch(costFor[i].action) {
                case divBy3:
                    i /= 3;
                    // std::cout << "/3 ";
                    break;

                case divBy2:
                    i /= 2;
                    // std::cout << "/2 ";
                    break;

                case sub1:
                    i -= 1;
                    // std::cout << "-1 ";
                    break;

                default:
                    throw std::logic_error("Undefined action for value");
                    break;
            }
        }
        // std::cout << std::endl;

        auto stop = std::chrono::high_resolution_clock::now();

        std::cout << inputVal << " " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << std::endl;
    }

}
