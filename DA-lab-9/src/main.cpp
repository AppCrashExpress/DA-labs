#include <iostream>
#include "FlowNetwork.h"

TFlowNetwork CreateGraph(std::istream& is) {
    size_t nodeCount, edgeCount;
    is >> nodeCount >> edgeCount;
    std::vector<std::vector<long long>> graph =
        std::vector<std::vector<long long>> (
            nodeCount,
            std::vector<long long> (nodeCount)
        );

    for (size_t i = 0; i < edgeCount; ++i) {
        size_t u, v;
        is >> u >> v;
        is >> graph[u - 1][v - 1];
    }

    return TFlowNetwork(graph, nodeCount);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    TFlowNetwork graph = CreateGraph(std::cin);    

    std::cout << graph.FindMaxFlow() << std::endl;
}
