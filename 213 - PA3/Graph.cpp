#include "Graph.h"
#include "GraphExceptions.h"

#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>

// Literally do nothing here
// default constructors of the std::vector is enough
Graph::Graph()
{}

Graph::Graph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[3];

    std::ifstream mapFile(filePath.c_str());
    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if(line.empty()) continue;
        // Comment Skip
        if(line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while(stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if(i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly three tokens (Meaning it is an edge)
        else if(i == 3)
        {
            int weight = std::atoi(tokens[0].c_str());
            if(!ConnectVertices(tokens[1], tokens[2], weight))
            {
                std::cerr << "Duplicate edge on "
                          << tokens[0] << "-"
                          << tokens[1] << std::endl;
            }
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

void Graph::InsertVertex(const std::string& vertexName)
{
    // TODO
    int size = vertexList.size();
    for(int i = 0; i < size; i++){
        if(vertexList[i].name == vertexName){
            throw DuplicateVertexNameException();
        }
    }
    GraphVertex v;
    v.edgeCount = 0;
    v.name = vertexName;
    vertexList.push_back(v);
}

bool Graph::ConnectVertices(const std::string& fromVertexName,
                            const std::string& toVertexName,
                            int weight)
{
    // TODO
    int size = vertexList.size(), i, j, k = 0;
    for(i = 0; i < size; i++){
        if(vertexList[i].name == fromVertexName){
            break;
        }
        if(i == size - 1)
            throw VertexNotFoundException();
    }
    for(j = 0; j < size; j++){
        if(vertexList[j].name == toVertexName){
            break;
        }
        if(j == size - 1)
            throw VertexNotFoundException();
    }
    if(vertexList[i].edgeCount == MAX_EDGE_PER_VERTEX){
        throw TooManyEdgeOnVertexExecption();
    }
    if(vertexList[j].edgeCount == MAX_EDGE_PER_VERTEX){
        throw TooManyEdgeOnVertexExecption();
    }
    if(i == j){
        return false;
    }
    for(k = 0; k < vertexList[i].edgeCount; k++){
        if((edgeList[vertexList[i].edgeIds[k]].vertexId0 == i) && (edgeList[vertexList[i].edgeIds[k]].vertexId1 == j)){
            return false;
        }
        if((edgeList[vertexList[i].edgeIds[k]].vertexId0 == j) && (edgeList[vertexList[i].edgeIds[k]].vertexId1 == i)){
            return false;
        }
    }
    vertexList[i].edgeIds[vertexList[i].edgeCount] = edgeList.size();
    vertexList[i].edgeCount++;
    vertexList[j].edgeIds[vertexList[j].edgeCount] = edgeList.size();
    vertexList[j].edgeCount++;
    GraphEdge e;
    e.weight = weight;
    e.vertexId0 = i;
    e.vertexId1 = j;
    e.masked = false;
    edgeList.push_back(e);
    return true;
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
                         const std::string& from,
                         const std::string& to) const
{
    // TODO
    int size = vertexList.size(), i, j, cur, v;
    for(i = 0; i < size; i++){
        if(vertexList[i].name == from){
            break;
        }
        if(i == size - 1)
            throw VertexNotFoundException();
    }
    for(j = 0; j < size; j++){
        if(vertexList[j].name == to){
            break;
        }
        if(j == size - 1)
            throw VertexNotFoundException();
    }
    std::priority_queue<DistanceVertexIdPair> pq;
    std::vector<int> distances(vertexList.size(), LARGE_NUMBER);
    std::vector<int> prevs(vertexList.size(), -1);
    for(int k = 0; k < vertexList.size(); k++){
        DistanceVertexIdPair a(k, LARGE_NUMBER);
        pq.push(a);
    }
    DistanceVertexIdPair a(i, 0);
    pq.push(a);
    distances[i] = 0;
    while(!pq.empty()){
        if(pq.top().currentWeight == LARGE_NUMBER) break;
        cur = pq.top().vId;
        pq.pop();
        for(int t = 0; t < vertexList[cur].edgeCount; t++){
            int z = vertexList[cur].edgeIds[t];
            if(edgeList[z].masked == false){
                if(edgeList[z].vertexId0 == cur){
                    v = edgeList[z].vertexId1;
                }
                else{
                    v = edgeList[z].vertexId0;
                }
                int weight = edgeList[z].weight;
                if(distances[cur] + weight < distances[v]){
                    distances[v] = distances[cur] + weight;
                    DistanceVertexIdPair a(v, distances[v]);
                    pq.push(a);
                    prevs[v] = cur;
                }
            }
            
        }
        
    }
    if(prevs[j] == -1){
        return false;
    }
    else{
        orderedVertexIdList.insert(orderedVertexIdList.begin(), j);
        while(prevs[j] != i){
            orderedVertexIdList.insert(orderedVertexIdList.begin(), prevs[j]);
            j = prevs[j];
            
        }
        orderedVertexIdList.insert(orderedVertexIdList.begin(), i);
        return true;
    }
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{
    // TODO
    int i, j, k;
    UnMaskAllEdges();
    for(i = 0; i < numberOfShortestPaths; i++){
        std::vector<int> one;
        if(ShortestPath(one, from, to)){
            orderedVertexIdList.push_back(one);
            int max = 0, hold = 0;
            for(j = 0; j < one.size() - 1; j++){
                for(k = 0; k  < vertexList[one[j]].edgeCount; k++){
                    if((edgeList[vertexList[one[j]].edgeIds[k]].vertexId0 == one[j] && edgeList[vertexList[one[j]].edgeIds[k]].vertexId1 == one[j+1]) || (edgeList[vertexList[one[j]].edgeIds[k]].vertexId1 == one[j] && edgeList[vertexList[one[j]].edgeIds[k]].vertexId0 == one[j+1])){
                        if(edgeList[vertexList[one[j]].edgeIds[k]].weight > max){
                            max = edgeList[vertexList[one[j]].edgeIds[k]].weight;
                            hold = vertexList[one[j]].edgeIds[k];
                        }
                    }
                }
                
            }
            edgeList[hold].masked = true;
        }
        else{
            break;
        }
    }
    return i;
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{
    // TODO
    int n = vertexNames.size(), size = vertexList.size(), i, j, t;
    for(int k = 0; k < n; k++){
        for(i = 0; i < size; i++){
            if(vertexList[i].name == vertexNames[k].s0){
                break;
            }
            if(i == size - 1)
                return;
        }
        for(j = 0; j < size; j++){
            if(vertexList[j].name == vertexNames[k].s1){
                break;
            }
            if(j == size - 1)
                return;
        }
        for(t = 0; t < vertexList[i].edgeCount; t++){
            if((edgeList[vertexList[i].edgeIds[t]].vertexId0 == i) && (edgeList[vertexList[i].edgeIds[t]].vertexId1 == j)){
                edgeList[vertexList[i].edgeIds[t]].masked = true;
            }
            if((edgeList[vertexList[i].edgeIds[t]].vertexId0 == j) && (edgeList[vertexList[i].edgeIds[t]].vertexId1 == i)){
                edgeList[vertexList[i].edgeIds[t]].masked = true;
            }
        }
    }
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
    // TODO
    int n = vertexNames.size(), size = vertexList.size(), i, j, t;
    for(int k = 0; k < n; k++){
        for(i = 0; i < size; i++){
            if(vertexList[i].name == vertexNames[k].s0){
                break;
            }
            if(i == size - 1)
                return;
        }
        for(j = 0; j < size; j++){
            if(vertexList[j].name == vertexNames[k].s1){
                break;
            }
            if(j == size - 1)
                return;
        }
        for(t = 0; t < vertexList[i].edgeCount; t++){
            if((edgeList[vertexList[i].edgeIds[t]].vertexId0 == i) && (edgeList[vertexList[i].edgeIds[t]].vertexId1 == j)){
                edgeList[vertexList[i].edgeIds[t]].masked = false;
            }
            if((edgeList[vertexList[i].edgeIds[t]].vertexId0 == j) && (edgeList[vertexList[i].edgeIds[t]].vertexId1 == i)){
                edgeList[vertexList[i].edgeIds[t]].masked = false;
            }
        }
    }
}

void Graph::UnMaskAllEdges()
{
    // TODO
    int size = edgeList.size(), i;
    for(i = 0; i < size; i++){
        edgeList[i].masked = false;
    }
}

void Graph::MaskVertexEdges(const std::string& name)
{
    // TODO
    int size = vertexList.size(), i;
    for(i = 0; i < size; i++){
        if(vertexList[i].name == name){
            int j;
            for(j = 0; j < vertexList[i].edgeCount; j++){
                edgeList[vertexList[i].edgeIds[j]].masked = true;
            }
        }
    }
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
    // TODO
    int size = vertexList.size(), i;
    for(i = 0; i < size; i++){
        if(vertexList[i].name == name){
            int j;
            for(j = 0; j < vertexList[i].edgeCount; j++){
                edgeList[vertexList[i].edgeIds[j]].masked = false;
            }
        }
    }
}

void Graph::ModifyEdge(const std::string& vName0,
                       const std::string& vName1,
                       float newWeight)
{
    // TODO
    int size = vertexList.size(), i, j, t;
    for(i = 0; i < size; i++){
        if(vertexList[i].name == vName0){
            break;
        }
        if(i == size - 1)
            throw VertexNotFoundException();
    }
    for(j = 0; j < size; j++){
        if(vertexList[j].name == vName1){
            break;
        }
        if(j == size - 1)
            throw VertexNotFoundException();
    }
    for(t = 0; t < vertexList[i].edgeCount; t++){
        if((edgeList[vertexList[i].edgeIds[t]].vertexId0 == i) && (edgeList[vertexList[i].edgeIds[t]].vertexId1 == j)){
            edgeList[vertexList[i].edgeIds[t]].weight = newWeight;
        }
        if((edgeList[vertexList[i].edgeIds[t]].vertexId0 == j) && (edgeList[vertexList[i].edgeIds[t]].vertexId1 == i)){
            edgeList[vertexList[i].edgeIds[t]].weight = newWeight;
        }
    }
}

void Graph::ModifyEdge(int vId0, int vId1,
                       float newWeight)
{
    // TODO
    int t;
    if(vId0 < 0 || vId0 >= vertexList.size() || vId1 < 0 || vId1 >= vertexList.size())
        return;
    for(t = 0; t < vertexList[vId0].edgeCount; t++){
        if((edgeList[vertexList[vId0].edgeIds[t]].vertexId0 == vId0) && (edgeList[vertexList[vId0].edgeIds[t]].vertexId1 == vId1)){
            edgeList[vertexList[vId0].edgeIds[t]].weight = newWeight;
        }
        if((edgeList[vertexList[vId0].edgeIds[t]].vertexId0 == vId1) && (edgeList[vertexList[vId0].edgeIds[t]].vertexId1 == vId0)){
            edgeList[vertexList[vId0].edgeIds[t]].weight = newWeight;
        }
    }
}

void Graph::PrintAll() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for(size_t i = 0; i < vertexList.size(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for(int j = 0; j < v.edgeCount; j++)
        {
            int edgeId = v.edgeIds[j];
            const GraphEdge& edge = edgeList[edgeId];
            // Skip printing this edge if it is masked
            if(edge.masked)
                continue;

            // List the all vertex names and weight
            std::cout << "-" << std::setfill('-')
                             << std::setw(2) << edge.weight
                             << "-> ";
            int neigVertexId = (static_cast<int>(i) == edge.vertexId0)
                                 ? edge.vertexId1
                                 : edge.vertexId0;
            std::cout << vertexList[neigVertexId].name << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void Graph::PrintPath(const std::vector<int>& orderedVertexIdList,
                      bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //
    for(size_t i = 0; i < orderedVertexIdList.size(); i++)
    {
        int vertexId = orderedVertexIdList[i];
        if(vertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if(!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if(i == orderedVertexIdList.size() - 1) break;
        int nextVertexId = orderedVertexIdList[i + 1];
        if(nextVertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        // Find the edge between these two vertices
        int edgeId = INVALID_INDEX;
        if(vertexId     < static_cast<int>(vertexList.size()) &&
           nextVertexId < static_cast<int>(vertexList.size()))
        {
            // Check all of the edges of vertex
            // and try to find
            const GraphVertex& fromVert = vertexList[vertexId];
            for(int i = 0; i < fromVert.edgeCount; i++)
            {
                int eId = fromVert.edgeIds[i];
                // Since the graph is not directional
                // check the both ends
                if((edgeList[eId].vertexId0 == vertexId &&
                    edgeList[eId].vertexId1 == nextVertexId)
                ||
                   (edgeList[eId].vertexId0 == nextVertexId &&
                    edgeList[eId].vertexId1 == vertexId))
                {
                    edgeId = eId;
                    break;
                }
            }
        }
        if(edgeId != INVALID_INDEX)
        {
            const GraphEdge& edge = edgeList[edgeId];
            std::cout << "-" << std::setfill('-')
                      << std::setw(2)
                      << edge.weight << "->";
        }
        else
        {
            std::cout << "-##-> ";
        }
    }
    // Print endline on the last vertex if same line is set
    if(sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

int Graph::TotalVertexCount() const
{
    // TODO
    return vertexList.size();
}

int Graph::TotalEdgeCount() const
{
    // TODO
    return edgeList.size();
}

std::string Graph::VertexName(int vertexId) const
{
    // TODO
    if(vertexList.size() <= vertexId || vertexId < 0){
        return "";
    }
    else{
        return vertexList[vertexId].name;
    }
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    // TODO
    int j, k, sum = 0;
    for(j = 0; j < orderedVertexIdList.size() - 1; j++){
        int x = orderedVertexIdList[j];
        if(vertexList.size() <= x || x < 0){
            throw VertexNotFoundException();
        }
        for(k = 0; k  < vertexList[x].edgeCount; k++){
            if((edgeList[vertexList[x].edgeIds[k]].vertexId0 == x && edgeList[vertexList[x].edgeIds[k]].vertexId1 == orderedVertexIdList[j+1]) || (edgeList[vertexList[x].edgeIds[k]].vertexId1 == x && edgeList[vertexList[x].edgeIds[k]].vertexId0 == orderedVertexIdList[j+1])){
                sum += edgeList[vertexList[x].edgeIds[k]].weight;
                break;
            }
            else if(k == vertexList[x].edgeCount - 1){
                return -1;
            }
        }
        
    }
    return sum;
}
