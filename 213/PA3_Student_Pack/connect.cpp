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
    std::vector<GraphVertex>::iterator it=vertexList.begin();
    int i=0;
    if (vertexList.empty())
        {
        GraphVertex my_vertex;
        int aray[MAX_EDGE_PER_VERTEX];
        my_vertex.name=vertexName;
        my_vertex.edgeIds[MAX_EDGE_PER_VERTEX]=aray[MAX_EDGE_PER_VERTEX];
        for(int j=0; j<MAX_EDGE_PER_VERTEX; j++)
            {
                my_vertex.edgeIds[j]=INVALID_INDEX;
            }
        my_vertex.edgeCount=0;
        vertexList.push_back(my_vertex);
        }
    else{
        for (; it != vertexList.end();i++,++it){
            if (vertexList[i].name==vertexName)
                throw DuplicateVertexNameException();
    }
    GraphVertex my_vertex;
    int aray[MAX_EDGE_PER_VERTEX];
    my_vertex.name=vertexName;
    my_vertex.edgeIds[MAX_EDGE_PER_VERTEX]=aray[MAX_EDGE_PER_VERTEX];
    for(int j=0; j<MAX_EDGE_PER_VERTEX; j++)
        {
            my_vertex.edgeIds[j]=INVALID_INDEX;
        }
    my_vertex.edgeCount=0;
    vertexList.push_back(my_vertex);
    }  

    // TODO
}
void Graph::set_count(int size,int index){
    vertexList[index].edgeCount=size;
}
bool Graph::ConnectVertices(const std::string& fromVertexName,
                            const std::string& toVertexName,
                            int weight)
{


    std::vector<GraphVertex>::iterator it=vertexList.begin(); // iterative for vertexList
    bool beg_vertic=0,end_vertice=0; // bool for vertices whether they exists or not
    int i=0,j=0,vertex_1,vertex_2; 
    //  vertex_'s indexes for vertices 

        
        for (; i< vertexList.size();i++){
            if(fromVertexName==vertexList[i].name)
            {
                beg_vertic=1; // exists
                vertex_1=i; // location index
                break;    
            } 
    }
   

 
        for (; j< vertexList.size();j++){
            if(toVertexName==vertexList[j].name)
            {
                end_vertice=1; // exists 
                vertex_2=j;  // location index        
                break;
            }
            } 

    
    if (beg_vertic==0 || end_vertice==0)
        throw VertexNotFoundException();
    if (vertex_1==vertex_2)
        return false;

    else if(edgeList.empty()){
            int edge_1_c,edge_2_c;
            GraphEdge my_edge;
            my_edge.masked=false;
            my_edge.vertexId0=vertex_1;
            my_edge.vertexId1=vertex_2;
            my_edge.weight=weight;
            edgeList.push_back(my_edge);
            edge_1_c=vertexList[vertex_1].edgeCount;edge_1_c++;
            edge_2_c=vertexList[vertex_2].edgeCount;edge_2_c++;
            vertexList[vertex_1].edgeCount=edge_1_c;
            std::cout<<vertexList[vertex_1].edgeCount<<" "<<edge_1_c<<std::endl;
            vertexList[vertex_1].edgeIds[0]=vertex_2;
            vertexList[vertex_2].edgeIds[0]=vertex_1;
            return true;
        }
    else if(!edgeList.empty()){
        if (vertexList[vertex_1].edgeCount>=MAX_EDGE_PER_VERTEX || vertexList[vertex_2].edgeCount>= MAX_EDGE_PER_VERTEX)
            throw TooManyEdgeOnVertexExecption();

        for (int k=0; k< vertexList[vertex_1].edgeCount; k++){
            if(vertexList[vertex_1].edgeIds[k]==vertex_2)
                return false;
        }

        int edge_1_c,edge_2_c;
        GraphEdge my_edge;
        my_edge.masked=false;
        my_edge.vertexId0=vertex_1;
        my_edge.vertexId1=vertex_2;
        my_edge.weight=weight;
        edgeList.push_back(my_edge);
        edge_1_c=vertexList[vertex_1].edgeCount;edge_1_c++;
        edge_2_c=vertexList[vertex_2].edgeCount;edge_2_c++;
        set_count(edge_1_c,vertex_1);
        set_count(edge_2_c,vertex_2);
        for(int indis=0; indis<MAX_EDGE_PER_VERTEX; indis++){
            if (vertexList[vertex_1].edgeIds[indis]==INVALID_INDEX)
                {vertexList[vertex_1].edgeIds[indis]=vertex_2;
                
                break;
                }
            
        }
        for(int indis=0; indis<MAX_EDGE_PER_VERTEX; indis++){
            if(vertexList[vertex_2].edgeIds[indis]==INVALID_INDEX)
                {vertexList[vertex_2].edgeIds[indis]=vertex_1; 
                
                break; 
                }          
        }
        
         
        return true;
 
    
    }

    // TODO
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
                         const std::string& from,
                         const std::string& to) const
{


 
    // TODO
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{
    // TODO
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{
     bool v1=0,v2=0; // v1 and v2 bool for vertices whether they exists or not //
    int i=0,j=0, vertex_1,vertex_2; 
    std::vector<GraphVertex>::iterator it=vertexList.begin(); // it = iterator for vertexList //
    std::vector<GraphEdge>::iterator edge_it=edgeList.begin(); // edge_it = iterator for edgeList//
    
    for (;it != vertexList.end() ;++it,i++){
        if (vertexList[i].name==vertexNames[0].s0) 
            {   
                v1=1; vertex_1=i;  // vertex_1 = indis_of_vertex 1//
            }
        else if(vertexList[i].name==vertexNames[0].s1)
          {     v2=1; vertex_2 =i; // vertex_2 = indis_of_vertex 2//
          }     
    }

    if (v1==0 || v2== 0)
        throw VertexNotFoundException(); 

    for(; edge_it != edgeList.end() ;++edge_it,j++){
        if(edgeList[j].vertexId0==vertex_1 && edgeList[j].vertexId1==vertex_2)
            edgeList[j].masked=true;
    }    
    // TODO
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
    // TODO
}

void Graph::UnMaskAllEdges()
{
    // TODO
}

void Graph::MaskVertexEdges(const std::string& name)
{
    // TODO
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
    // TODO
}

void Graph::ModifyEdge(const std::string& vName0,
                       const std::string& vName1,
                       float newWeight)
{
    // TODO
}

void Graph::ModifyEdge(int vId0, int vId1,
                       float newWeight)
{
    // TODO
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
}

int Graph::TotalEdgeCount() const
{
    // TODO
}

std::string Graph::VertexName(int vertexId) const
{
    // TODO
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    // TODO
}