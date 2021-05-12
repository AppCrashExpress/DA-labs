#include "FlowNetwork.h"

TFlowNetwork::TFlowNetwork(std::vector<std::vector<long long>> graph, size_t size) 
    : graph(graph), graphSize(size) {
    
}

// Should make a copy of graph to avoid ruining it
// but who cares at this point tbh
long long TFlowNetwork::FindMaxFlow() {
    const TIndex beginIndex = 0;
    const TIndex endIndex   = graphSize - 1;
    TFlowSize maxFlow = 0;

    while (FindPath(beginIndex, endIndex)) {
        TIndex current = endIndex;
        TFlowSize bottleneck = std::numeric_limits<long long>::max();

        while (current != beginIndex) {
            TIndex currParent = parent[current];
            TFlowSize flow = graph[currParent][current];
            bottleneck = std::min(bottleneck, flow);
            current = currParent;
        }

        maxFlow += bottleneck;

        current = endIndex;
        while (current != beginIndex) {
            TIndex currParent = parent[current];

            // On path, currParent precedes current
            // Decrease flow from parent to current,
            //      increase from current to parent
            graph[current][currParent] += bottleneck;
            graph[currParent][current] -= bottleneck;
            current = currParent;
        }
    }

    return maxFlow;
}

bool TFlowNetwork::FindPath(const TIndex begin, const TIndex end) {
    TStaticQueue<TIndex, 2000> nodeQueue;
    std::array<bool, 2000>     visited;

    visited.fill(0);
    parent.fill(-1);
    
    nodeQueue.PushBack(begin);
    visited[begin] = true;

    while(!nodeQueue.Empty()) {
        TIndex node = nodeQueue.Front();
        nodeQueue.RemoveFirst();

        std::vector<TFlowSize>& nodeVecRef = graph[node];
        for (TIndex i = 0; i < graphSize; ++i) {
            if (visited[i] || nodeVecRef[i] <= 0) {
                continue;
            }
            nodeQueue.PushBack(i);
            visited[i] = true;
            parent[i] = node;
        }
    }

    return visited[end];
}
