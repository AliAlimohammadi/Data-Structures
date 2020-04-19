#include <iostream>
#include <list>
#include <string>

using namespace std;

// This class represents a directed graph
// using adjacency list representation
class Graph
{
    private:
        int V;  // No. of vertices
        
        // Pointer to an array containing adjacency lists
        list<int> *adj;
        
        // A recursive function used by DFS
        void DFSVisit(int v, bool visited[])
        {
            // Mark the current node as visited and print it
            visited[v] = true;
            cout << v << " ";
            
            // Recur for all the vertices adjacent to this vertex
            list<int>::iterator i;
            for (i = adj[v].begin(); i != adj[v].end(); i++)
                if (!visited[*i])
                    DFSVisit(*i, visited);
        }
    
    public:
        Graph(int V)    // Constructor
        {
            this->V = V;
            adj = new list<int>[V];
        }
        
        // function to add an edge to graph
        void addEdge(int v, int w)
        {
            adj[v].push_back(w);    // Add w to v’s list
        }
        
        // prints BFS traversal from a given source s
        void BFS(int s)
        {
            // Mark all the vertices as not visited
            bool *visited = new bool[V];
            for (int i = 0; i < V; i++)
                visited[i] = false;
            
            // Create a queue for BFS
            list<int> queue;
            
            // Mark the current node as visited and enqueue it
            visited[s] = true;
            queue.push_back(s);
            
            // 'i' will be used to get all
            // adjacent vertices of a vertex
            list<int>::iterator i;
            
            while(!queue.empty())
            {
                // Dequeue a vertex from queue and print it
                s = queue.front();
                cout << s << " ";
                queue.pop_front();
                // Get all adjacent vertices of the dequeued
                // vertex s. If a adjacent has not been visited,
                // then mark it visited and enqueue it
                for (i = adj[s].begin(); i != adj[s].end(); i++)
                {
                    if (!visited[*i])
                    {
                        visited[*i] = true;
                        queue.push_back(*i);
                    }
                }
            }
            cout << endl;
        }
        
        // DFS traversal of the vertices reachable from v
        // It uses recursive DFSVisit function
        void DFS(int v)
        {
            // Mark all the vertices as not visited
            bool *visited = new bool[V];
            for (int i = 0; i < V; i++)
                visited[i] = false;
            
            // Call the recursive helper function
            // to print DFS traversal
            DFSVisit(v, visited);
            cout << endl;
        }
};

int main()
{
    cout << "Graph BFS & DFS Demonstration\t\tgithub.com/AliAlimohammadi\n\nEnter the number of vertices: ";
    int V;
    cin >> V;
    Graph graph(V);
    cout << "GRAPH>>> ";
    string command;
    cin >> command;
    while (command != "exit")
    {
        if (command == "add" || command == "addEdge")
        {
            int v, w;
            cin >> v >> w;
            graph.addEdge(v, w);
        }
        else if (command == "bfs")
        {
            int s;
            cin >> s;
            graph.BFS(s);
        }
        else if (command == "dfs")
        {
            int v;
            cin >> v;
            graph.DFS(v);
        }
        
        cout << "GRAPH>>> ";
        cin >> command;
    }
    
    return 0;
}