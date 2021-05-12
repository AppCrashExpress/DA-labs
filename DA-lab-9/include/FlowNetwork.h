#ifndef FLOW_NETWORK_H
#define FLOW_NETWORK_H

#include <array>
#include <vector>
#include <limits>
#include "StaticQueue.h"

class TFlowNetwork {
public:
    TFlowNetwork(std::vector<std::vector<long long>>, size_t);
    
    long long FindMaxFlow();
private:
    typedef long long TFlowSize;
    typedef std::vector<std::vector<TFlowSize>> TGraph;
    typedef size_t TIndex;

    TGraph graph;
    TIndex graphSize;
    std::array<TIndex, 2000> parent;

    bool FindPath(const TIndex, const TIndex);

};

#endif
