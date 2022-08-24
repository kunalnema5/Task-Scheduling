#include <iostream>
#include <vector>
using namespace std;

// Defining node of a graph
struct Node
{
    int data;
    Node *next;
    Node(int x)
    {
        data = x;
        next = NULL;
    }
};

// Defining Graph
struct graph
{
    int num_vertices; // number of vertices of graph
    Node **adj_list;  // adjacency list
    graph(int vertices)
    {
        num_vertices = vertices;
        adj_list = new Node *();
        for (int i = 0; i < vertices; i++)
            adj_list[i] = NULL;
    }
};

// Function to add edges in directed graph
void add_edge(graph *g, int s, int d)
{
    Node *new_node = new Node(d);
    new_node->next = g->adj_list[s];
    g->adj_list[s] = new_node;
}

// Function to calculate indegree of every node of graph
// Indegree : If m vertices have directed edges to a vertex A then vertex A has indegree m
void calc_indegree(graph *g, vector<int> &indegree)
{
    for (int i = 0; i < g->num_vertices; i++)
    {
        Node *traverse = g->adj_list[i];
        while (traverse != NULL)
        {
            indegree[traverse->data]++;
            traverse = traverse->next;
        }
    }
}

// Print all valid topological orders of the graphs
void all_topological_sort(graph *g, vector<int> &indegree, vector<int> &orders)
{
    // Flag will be used to check if any vertex is visited in this recursive call or not
    bool flag = false;

    for (int i = 0; i < g->num_vertices; i++)
    {
        // perform task whose all pre requisite tasks are completed
        if (indegree[i] == 0)
        {
            // include in valid orders
            orders.push_back(i);

            // To keep this node as visited, we assign it -1
            indegree[i] = -1;

            // Reduce indegree of all vertices adjacenct to visited node
            Node *traverse = g->adj_list[i];
            while (traverse != NULL)
            {
                indegree[traverse->data]--;
                traverse = traverse->next;
            }

            // recursive call for updated indegree
            all_topological_sort(g, indegree, orders);

            // Backtracking
            orders.pop_back();    // pop last pushed vertex
            indegree[i] = 0;      // again change its indegree to 0

            // change indegree array as initial
            traverse = g->adj_list[i];
            while (traverse != NULL)
            {
                indegree[traverse->data]++;
                traverse = traverse->next;
            }

            flag = true;
        }
    }

    // if no vertex is visited in this recursive call then no vertex is left with indegree 0
    // means all visited so print the order
    if (flag == false)
    {
        for (int i = 0; i < orders.size(); i++)
            cout << orders[i] << " ";
        cout << endl;
    }
}


// Display graph
void display_graph(graph *g)
{
    for (int i = 0; i < g->num_vertices; i++)
    {
        Node *traverse = g->adj_list[i];
        cout << i << ": ";
        while (traverse != NULL)
        {
            cout << traverse->data << " ";
            traverse = traverse->next;
        }
        cout << endl;
    }
}

int main()
{
    // Making the graph
    int vertices = 6;
    graph *g = new graph(vertices);
    add_edge(g, 5, 2);
    add_edge(g, 5, 0);
    add_edge(g, 4, 0);
    add_edge(g, 4, 1);
    add_edge(g, 2, 3);
    add_edge(g, 3, 1);

    /* Here every node represents a tasks to be performed which is dependent
     on the tasks prior to it 
     4 -> 0 represents that task 0 can only be perfomed after task 4 */

    cout << "Representation of graph in adjacency list: \n";
    display_graph(g);
    cout << endl;

    // Defining the indegree array
    vector<int> indegree(vertices, 0);
    calc_indegree(g, indegree);

    // Vector to store valid orders
    vector<int> valid_orders;

    // Calling function to print all valid sequences of tasks
    cout << "All valid sequences in which Tasks can performed are: \n";
    all_topological_sort(g, indegree, valid_orders);

}
