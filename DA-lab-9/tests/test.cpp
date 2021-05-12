#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../FlowNetwork.hpp"
#include "../include/Catch2.hpp"
using namespace NFlowNetwork;

std::vector<TNode> GetNodes(std::ifstream& stream) {
    unsigned int nodeAmount, edgeAmount;
    stream >> nodeAmount >> edgeAmount;
    std::vector<TNode> node(nodeAmount, TNode(nodeAmount)); 

    for (unsigned int i = 0; i < nodeAmount; ++i) {
        node[i].index = i;
    }

    for (unsigned int i = 0; i < edgeAmount; ++i) {
        unsigned int u, v, capacity;
        stream >> u >> v >> capacity;
        node[u - 1].edge[v - 1] = capacity;
    }

    return node;
}

TEST_CASE("Edmond-Karp test", "[graph]")
{
    std::ifstream file;
    
    SECTION("Direct link")
    {
        file.open("01-DirectLink.txt");
        TFlowNetwork graph( GetNodes(file) );
        REQUIRE( graph.MaxFlow() == 5 );
        file.close();
    }

    SECTION("Long link")
    {
        file.open("02-LongDirect.txt");
        TFlowNetwork graph( GetNodes(file) );
        REQUIRE( graph.MaxFlow() == 5 );
        file.close();
    }

    SECTION("Long link decreasting")
    {
        file.open("03-DirectDecreasing.txt");
        TFlowNetwork graph( GetNodes(file) );
        REQUIRE( graph.MaxFlow() == 2 );
        file.close();
    }

    SECTION("Branching")
    {
        file.open("04-Branching.txt");
        TFlowNetwork graph( GetNodes(file) );
        REQUIRE( graph.MaxFlow() == 1 );
        file.close();
    }

    SECTION("No link to end")
    {
        file.open("05-NoLink.txt");
        TFlowNetwork graph( GetNodes(file) );
        REQUIRE( graph.MaxFlow() == 0 );
        file.close();
    }

}
