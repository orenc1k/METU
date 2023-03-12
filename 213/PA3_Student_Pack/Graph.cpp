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
{   int m=0;

    for (int i=0;i<vertexList.size();i++){          // Check whether vertex is already exists;
        if (vertexList[i].name==vertexName)
                throw DuplicateVertexNameException();
    }

    GraphVertex my_vertex;    // if vertex is not exist add it  
    my_vertex.name=vertexName;
    my_vertex.edgeCount=m;
    vertexList.push_back(my_vertex);

    // TODO
}

bool Graph::ConnectVertices(const std::string& fromVertexName,
                            const std::string& toVertexName,
                            int weight)
{

    bool v1_exists=vertex_exist(fromVertexName),v2_exists=vertex_exist(toVertexName),edge_exists;
    
    int v1_pos,v2_pos;

    if(v1_exists==false || v2_exists==false)
        throw VertexNotFoundException();      /// check vertices exists or not

    v1_pos=vertex_index(fromVertexName);   /// find index of vertices
    v2_pos=vertex_index(toVertexName);

    if (v1_pos==v2_pos)  // if they are same vertex return false
        return false;

    edge_exists=edge_exist(v1_pos,v2_pos);  // check edge exists or not

    if (edge_exists==true) /// if edge exists return false
        return false;

    else{

        GraphVertex *first_point=&vertexList.at(v1_pos);  //// pointers for index of vertices
        GraphVertex *second_point=&vertexList.at(v2_pos);
        
        if (first_point->edgeCount<MAX_EDGE_PER_VERTEX && second_point->edgeCount<MAX_EDGE_PER_VERTEX)
        {    /// check number of edges less than max_edge_per vertex 
            /// if number of edges less than put the edge

            GraphEdge my_edge;     
            my_edge.masked=false;
            my_edge.vertexId0=v1_pos;
            my_edge.vertexId1=v2_pos;
            my_edge.weight=weight;
            edgeList.push_back(my_edge);
            first_point->edgeCount++;  /// count number of edges for vertices
            second_point->edgeCount++;
            first_point->edgeIds[first_point->edgeCount-1]=edgeList.size()-1;  /// tie the edge
            second_point->edgeIds[second_point->edgeCount-1]=edgeList.size()-1;
            return true;
        }
        else{
            throw TooManyEdgeOnVertexExecption(); /// if number of edges for one vertice exceed throw  
        }
    }   
       return true;    
    // TODO
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
                         const std::string& from,
                         const std::string& to) const
{

    
    std::vector<int> path_weight,pre_vertex;  // vectors for weight and pre vertex
    std::vector<bool> Tset;  // bool for vertex whether checked path or not    
    int v1_pos,v2_pos,temp_pos,index_pos; //vertex positions 
    bool v1_exists=vertex_exist(from),v2_exists=vertex_exist(to); //exists control

    
    if (v1_exists==false || v2_exists==false){
        throw VertexNotFoundException();    /// check vertices exists or not
    }

    v1_pos=(int)vertex_index_new(from);  // find indexes
    v2_pos=(int)vertex_index_new(to);
    
    for(int i = 0; i<vertexList.size(); i++)
    {
     path_weight.push_back(LARGE_NUMBER);    /// path_weight 
     Tset.push_back(false);                  //// Tset for if one vertices used for all path ways
     pre_vertex.push_back(-1);               /// previous vertex
    }   // set path and BOOL vectors
    path_weight[v1_pos]=0;
    pre_vertex[v1_pos]=v1_pos;
    temp_pos=v1_pos;  // temp_vertice for path checking 
    

    for (int i=0; i<vertexList.size();i++) // check all vertices
    {
        const GraphVertex* v_pointer=&vertexList.at(temp_pos); // pointer for vertice

        for (int j=0; j<v_pointer->edgeCount;j++) // edge control 
        {
            int index=v_pointer->edgeIds[j]; 
            const GraphEdge* e_pointer= &edgeList.at(index); // pointer for edges

            if(e_pointer->masked==false)
            {
                if(e_pointer->vertexId0==temp_pos)
                {   int new_weight;

                    new_weight=path_weight[temp_pos]+e_pointer->weight;
                    if(new_weight< path_weight[e_pointer->vertexId1])
                    {
                        path_weight[e_pointer->vertexId1]=new_weight;
                        pre_vertex[e_pointer->vertexId1]=temp_pos;
                    }

                }
                                           ////DJIKSTRA ALGORTIHM FOR SHORTEST PATH
            else
            {
                    int new_weight;
                    new_weight=path_weight[temp_pos]+e_pointer->weight;
                    if(new_weight< path_weight[e_pointer->vertexId0])
                    {
                        path_weight[e_pointer->vertexId0]=new_weight;
                        pre_vertex[e_pointer->vertexId0]=temp_pos;
                    }              

            }

            }

        }

        Tset[temp_pos]=true;

        for(int k=0; k<Tset.size();k++)
        {
            if(k==temp_pos)
                continue;

            if(path_weight[k]<path_weight[temp_pos]&& Tset[k]==false){
                temp_pos=k;
            }

            else if(path_weight[k]>0 && path_weight[k]<LARGE_NUMBER && Tset[k]==false)
            {   
                temp_pos=k;
            }
            
        }

    }    
   std::vector<int> reverse; 

    index_pos=v2_pos;
    reverse.push_back(v2_pos);

    for (; pre_vertex[index_pos]!=v1_pos;){  // FIND SHORTEST PATH

        reverse.push_back(pre_vertex[index_pos]);
        index_pos=pre_vertex[index_pos];

    }
    reverse.push_back(pre_vertex[index_pos]);

    if(path_weight[v2_pos]==LARGE_NUMBER){  // IF SHORTHEST PATH DOESNT EXIST RETURN FALSE
        return false;
    }
    
    for(int size=reverse.size(); size>0; size--){     
        orderedVertexIdList.push_back(reverse[size-1]); /// SHORTEST PATH VECTOR
    }     
    return true;    

    // TODO
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{

    int weight; bool v1_exists,v2_exists,path_exist;
    int count=0;
    
    UnMaskAllEdges();
    std::vector<int> new_list;
    
    if(ShortestPath(new_list,from,to))
    {
        orderedVertexIdList.push_back(new_list);      
        weight=find_max_edge_weight(new_list); /// HELPER FUNC FOR FINDING MAX WEIGHT EDGE
        remove_edge(new_list,weight);          /// HELPER FUNC FOR MASK THE EDGE OF MAX WEIGHT
        new_list.clear();
        count++;

        for(;count<numberOfShortestPaths;){ 

            if(ShortestPath(new_list,from,to)){ 
            orderedVertexIdList.push_back(new_list);
            weight=find_max_edge_weight(new_list); /// HELPER FUNC FOR FINDING MAX WEIGHT EDGE
            remove_edge(new_list,weight); /// HELPER FUNC FOR MASK THE EDGE OF MAX WEIGHT
            new_list.clear();
            count++;
            }
            else
                break;

        }    
      
    }

    UnMaskAllEdges();
    return orderedVertexIdList.size();
    // TODO
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{
    bool v1_exists,v2_exists;    
    int v1_pos,v2_pos;

        for (int j=0;j<vertexNames.size();j++)
        { 

        v1_exists=vertex_exist(vertexNames[j].s0); 
        v2_exists=vertex_exist(vertexNames[j].s1);     
        
        if (v1_exists==false || v2_exists== false) /// CHECK VERTICES EXISTS OR NOT
            throw VertexNotFoundException(); 

        v1_pos=vertex_index(vertexNames[j].s0);  /// IF THEY ARE IN FIND INDEXES
        v2_pos=vertex_index(vertexNames[j].s1);
        
            for (int i=0;i<edgeList.size();i++) 
            {
        
                if(edgeList.at(i).vertexId0==v1_pos && edgeList.at(i).vertexId1==v2_pos ||
                    edgeList.at(i).vertexId1==v1_pos && edgeList.at(i).vertexId0==v2_pos)  // FIND THE EDGE LOCATION
                    {
                        edgeList.at(i).masked=true; // MASK THE EDGE
                        break;
                    }

            }
       
        }

    
    // TODO
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
    bool v1_exists=vertex_exist(vertexNames[0].s0),v2_exists=vertex_exist(vertexNames[0].s1);    
    int v1_pos,v2_pos;

    if (v1_exists==false || v2_exists== false) /// CHECK VERTICES EXISTS OR NOT
        throw VertexNotFoundException(); 

    v1_pos=vertex_index(vertexNames[0].s0); /// IF THEY ARE IN FIND INDEXES
    v2_pos=vertex_index(vertexNames[0].s1);

    for (int i=0;i<edgeList.size();i++){

        if(edgeList.at(i).vertexId0==v1_pos && edgeList.at(i).vertexId1==v2_pos ||
           edgeList.at(i).vertexId1==v1_pos && edgeList.at(i).vertexId0==v2_pos)
           {
                edgeList.at(i).masked=false; // UNMASK THE EDGE
                break;
    }
    }
    
    // TODO
}

void Graph::UnMaskAllEdges()
{
    for(int i=0;i<edgeList.size();i++){  // UNMASK ALL EDGES
        edgeList.at(i).masked=false;
    }
    // TODO
}

void Graph::MaskVertexEdges(const std::string& name)
{

bool vertex_exists=vertex_exist(name);
int vertex_pos;

    if (vertex_exists==false)
        throw VertexNotFoundException();  // IF VERTEX DOESNT EXIST THROW

    vertex_pos=vertex_index(name);  // IF IT IS IN FIND INDEX

    for(int i=0;i<edgeList.size();i++){

        if(edgeList.at(i).vertexId0==vertex_pos||
           edgeList.at(i).vertexId1==vertex_pos )  // FIND ALL OF ITS EDGES
           edgeList.at(i).masked=true;  /// MASK ALL OF THEM
    }
    // TODO
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
bool vertex_exists=vertex_exist(name);
int vertex_pos;
    if (vertex_exists==false) // IF VERTEX DOESNT EXIST THROW
        throw VertexNotFoundException();

    vertex_pos=vertex_index(name); // IF IT IS IN FIND INDEX

    for(int i=0;i<edgeList.size();i++){

        if(edgeList.at(i).vertexId0==vertex_pos|| // FIND ALL OF ITS EDGES
           edgeList.at(i).vertexId1==vertex_pos )
           edgeList.at(i).masked=false; /// UNMASK ALL OF THEM
    }
    // TODO
}

void Graph::ModifyEdge(const std::string& vName0,
                       const std::string& vName1,
                       float newWeight)
{
    bool v1_exists=vertex_exist(vName0),v2_exists=vertex_exist(vName1);
    int v1_pos,v2_pos;

    if(v1_exists==false || v2_exists== false )
        throw VertexNotFoundException(); // IF VERTEX DOESNT EXIST THROW

    v1_pos=vertex_index(vName0);
    v2_pos=vertex_index(vName1);  // IF THEY ARE IN FIND INDEXES

    for (int i=0; i<edgeList.size();i++){

        if(edgeList.at(i).vertexId0==v1_pos && edgeList.at(i).vertexId1==v2_pos||
           edgeList.at(i).vertexId1==v1_pos && edgeList.at(i).vertexId0==v2_pos) // FIND THE EDGE
           edgeList.at(i).weight=newWeight; // CHANGE THE WEIGHT
    }
    // TODO
}

void Graph::ModifyEdge(int vId0, int vId1,
                       float newWeight)
{
    for (int i=0; i<edgeList.size();i++){
        if (edgeList.at(i).vertexId0==vId0 && edgeList.at(i).vertexId1==vId1) // FIND THE EDGE
            edgeList.at(i).weight=newWeight;  // MODIFY THE WEIGHT
    }
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
    int total_vertex =0;
    

    for (; total_vertex<vertexList.size();total_vertex++){

    }
    return total_vertex;
    // TODO
}

int Graph::TotalEdgeCount() const
{
    int total_edge=0;

    for (;total_edge<edgeList.size(); total_edge++){

    }

    return total_edge;
    // TODO
}

std::string Graph::VertexName(int vertexId) const
{
    for(int i=0; i<vertexList.size();i++)
       { if(i==vertexId)
            {
            std::cout<<"doru"<<std::endl;
            return vertexList[i].name;
            
            }
       }
       std::cout<<"bos string"<<std::endl;
    return "";
    // TODO
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    bool vertex_exists;
    int total_weight=0;

    for (int i=0; i< orderedVertexIdList.size()-1;i++){
        if (orderedVertexIdList.at(i)>vertexList.size()||
            orderedVertexIdList.at(i)<0)
            throw VertexNotFoundException();
        else{
            for (int j=0;j<edgeList.size();j++){
                GraphEdge* pointer=&edgeList.at(j);
                if(pointer->vertexId0==orderedVertexIdList.at(i)&& pointer->vertexId1==orderedVertexIdList.at(i+1) ||
                pointer->vertexId1==orderedVertexIdList.at(i)&&pointer->vertexId0==orderedVertexIdList.at(i+1))
                {
                    total_weight+=pointer->weight;
                    break;
                }
            }
        }    
    }
    return total_weight;
    // TODO
}