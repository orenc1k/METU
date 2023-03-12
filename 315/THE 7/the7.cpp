#include "the7.h"

// Implement your solution after this line

struct DistanceVertexIdPair
{
    int vId;
    int currentdistance;
    DistanceVertexIdPair(int vId, int currentdistance)
    {
        this->vId = vId;
        this->currentdistance = currentdistance;
    }

    bool operator< (const DistanceVertexIdPair& p) const
    {
        return currentdistance > p.currentdistance;
    }
};

struct GraphVertex
{
    std::vector<int> edgeIds;  
    int             edgeCount;                      
    int     name;                           
};

struct GraphEdge
{
    int     distance;     
    int     vertexId0;  
    int     vertexId1; 
};

class Graph
{
    public:
        std::vector<GraphVertex>    vertexList;
        std::vector<GraphEdge>      edgeList;
        
        void    InsertVertex(const int& vertexName);
        void    ConnectVertices(const int& fromVertexName, const int& toVertexName, int distance);
        int        ShortestPath(std::vector<int>& orderedVertexIdList, const int& from, const int& to);  
        
    };

void Graph::InsertVertex(const int& vertexName)
{   bool condition=false;
    for (unsigned int i=0;i<vertexList.size();i++){          
        if (vertexList[i].name==vertexName)
            {
                condition=true;
                break;
            }
    };

    if (!condition){
        GraphVertex my_vertex;   
        my_vertex.name=vertexName;
        my_vertex.edgeCount=0;
        vertexList.push_back(my_vertex);
    }

}

void Graph::ConnectVertices(const int& fromVertexName, const int& toVertexName, int distance)
{
   
    int v1_pos,v2_pos; 
    v1_pos=fromVertexName;   
    v2_pos=toVertexName;
    
    GraphVertex *first_point=&vertexList.at(v1_pos);  
    GraphVertex *second_point=&vertexList.at(v2_pos);    
    GraphEdge my_edge;     
    
        my_edge.vertexId0=v1_pos;
        my_edge.vertexId1=v2_pos;
        my_edge.distance=distance;
        edgeList.push_back(my_edge);
        first_point->edgeCount++;  
        second_point->edgeCount++;
        first_point->edgeIds.push_back(edgeList.size()-1);  
        second_point->edgeIds.push_back(edgeList.size()-1);
  
}

int Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
                         const int& from,
                         const int& to) 
{
    std::priority_queue<DistanceVertexIdPair,std::vector<DistanceVertexIdPair>,std::less<DistanceVertexIdPair> > priority_q;
    std::vector<int>distance;
    std::vector< std::vector<int>> list_of_paths;
    int v1_pos = from;
    int v2_pos = to;
    
    for (unsigned int i = 0; i<vertexList.size();i++) {
        std::vector<int> empty_path;
        list_of_paths.push_back(empty_path);
    }
    
    for(unsigned int i=0;i<vertexList.size();i++){
        distance.push_back(INT_MAX);
    }
    
    distance[v1_pos] = 0;
    list_of_paths[v1_pos].push_back(v1_pos);
    DistanceVertexIdPair new_pair(v1_pos,0);
    priority_q.push(new_pair);

    for (; !priority_q.empty();) {
        int index = priority_q.top().vId;
        priority_q.pop();
        const GraphVertex* v_pointer=&vertexList.at(index);

        for (int i = 0; i<v_pointer->edgeCount; i++) {
            int new_vertex_id;
            int temp_edge_id = v_pointer->edgeIds[i];
            const GraphEdge* e_pointer=&edgeList.at(temp_edge_id);

            if (index == e_pointer->vertexId0) {
                new_vertex_id = e_pointer->vertexId1;
            }
            else {
                new_vertex_id = e_pointer->vertexId0;
            }
            int edge_distance = e_pointer->distance; 
            
            if (distance[new_vertex_id]>(distance[index]+edge_distance)) {
                if (!list_of_paths[new_vertex_id].empty()) {
                    list_of_paths[new_vertex_id].clear();
                }
                for (unsigned i=0; i<list_of_paths[index].size();i++) {
                    list_of_paths[new_vertex_id].push_back(list_of_paths[index].at(i));
                }
                list_of_paths[new_vertex_id].push_back(new_vertex_id);
                distance[new_vertex_id] = distance[index]+edge_distance;

                DistanceVertexIdPair new_pair(new_vertex_id,distance[new_vertex_id]);
                priority_q.push(new_pair);
            }
            
        }
    }
    
    if (!list_of_paths[v2_pos].empty()) {
        for(unsigned int i = 0; i<list_of_paths[v2_pos].size();i++) {
            orderedVertexIdList.push_back(list_of_paths[v2_pos][i]);
        }
    }
    
    return distance.at(to);
}

void clean_duplicates(std::vector<int>&path){
        
        for(unsigned int i=0;i<path.size();i++){
        int j=i;
        if(path[j]==path[j+1]){
            path.erase(path.begin()+(j+1));
            break;
        }
    }
}

void CanCatch(int n, std::vector<Road> roads, int s, int d, int x, int y, int l, int printPath) {
    // You can change these variables. These are here for demo only.
    std::vector<int> path;
    std::vector<int> path_1,path_2;
    
    int distance; int distance_1=0; int distance_2 =0;
    int dorm_distance,print_distance;
    Graph my_graph;
    for (unsigned int i=0; i<roads.size();i++){
        my_graph.InsertVertex(roads[i].buildings.first);
    }
    for (unsigned int i=0; i<roads.size();i++){
        my_graph.InsertVertex(roads[i].buildings.second);
    }

    for (unsigned int i=0;i<roads.size();i++){
        my_graph.ConnectVertices(roads[i].buildings.first,roads[i].buildings.second,roads[i].time);
    }

    
    dorm_distance=my_graph.ShortestPath(path_1,s,y);
    distance_1+=dorm_distance;
    distance_1+= my_graph.ShortestPath(path_1,y,x);
    clean_duplicates(path_1);
    distance_1+=my_graph.ShortestPath(path_1,x,d);
    clean_duplicates(path_1);

    print_distance=my_graph.ShortestPath(path_2,s,x);
    distance_2+=print_distance;
    distance_2+= my_graph.ShortestPath(path_2,x,y);
    clean_duplicates(path_2);
    distance_2+=my_graph.ShortestPath(path_2,y,d);
    clean_duplicates(path_2);

    if (distance_2<distance_1)
        distance=distance_2;
    else    
        distance=distance_1;

    if (distance<l){
        printf("YES BOTH %dMINUTES\n",distance);
        if(printPath==1){
            if(distance_2<=distance_1)
                PrintRange(path_2.begin(), path_2.end(), "->");
            else
                PrintRange(path_1.begin(), path_1.end(), "->");
        }
    }
    else if (distance>l){
        distance=0; distance_1=0; distance_2=0;
        path_1.clear(); path_2.clear();
        dorm_distance=my_graph.ShortestPath(path_1,s,y);
        distance_1+=dorm_distance;
        distance_1+= my_graph.ShortestPath(path_1,y,d);
        clean_duplicates(path_1);

        print_distance=my_graph.ShortestPath(path_2,s,x);
        distance_2+=print_distance;
        distance_2+= my_graph.ShortestPath(path_2,x,d);
        clean_duplicates(path_2);
        
        
        if (distance_2<=distance_1 && distance_2<=l)
            {   
                printf("YES PRINTER %dMINUTES\n",distance_2);
                if(printPath==1)
                    PrintRange(path_2.begin(), path_2.end(), "->");
            }
        else if (distance_1<=distance_2 && distance_1<=l)   
            {
                printf("YES DORM %dMINUTES\n",distance_1);
                if(printPath==1)
                    PrintRange(path_1.begin(), path_1.end(), "->");
            }
        else if (distance_1>l && distance_2>l)
        { distance+=my_graph.ShortestPath(path,s,d);
            if (distance<=l){
                 
                printf("YES DIRECTLY %dMINUTES\n",distance);
                if(printPath==1)
                    PrintRange(path.begin(), path.end(), "->");
            }
            else{
                printf("IMPOSSIBLE");
            }
    
        }    
        
        
    }
    // You can use the PrintRange function to print the path.
    // It helps you print elements of containers with iterators (e.g., std::vector).
    // Usage: PrintRange(path.begin(), path.end());
    
}