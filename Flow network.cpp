#include<bits/stdc++.h>
using namespace std;

void printPath(vector<int>& path)
{
    int n = path.size();
    for (int i=0;i<n;i++) {
        cout<<path[i];
        if(i < n-1)
            cout<<" -> ";
    }
    cout<<endl;
}

int isNotVisited(int x, vector<int>& path)
{
    int n = path.size();
    for (int i=0;i<n;i++)
        if (path[i] == x)
            return 0;
    return 1;
}

void findPaths(int graph[20][20], int src, int dest, int n)
{

    vector<vector<int> > g;
    g.resize(n);

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(graph[i][j]!=0)
                g[i].push_back(j);
        }
    }

    queue<vector<int> > q;
    vector<int> path;
    path.push_back(src);
    q.push(path);

    while (!q.empty()) {
        path = q.front();
        q.pop();
        int last = path[path.size() - 1];

        if (last == dest)
            printPath(path);

        for (int i = 0; i < g[last].size(); i++) {
            if (isNotVisited(g[last][i], path)) {
                vector<int> newpath(path);
                newpath.push_back(g[last][i]);
                q.push(newpath);
            }
        }
    }
}

bool bfs(int rGraph[20][20], int s, int t, int parent[],int n)
{
    bool visited[n];
    memset(visited, 0, sizeof(visited));

    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v=0; v<n; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return (visited[t] == true);
}

int fordFulkerson(int graph[20][20], int s, int t, int n)
{
    int u, v;
    int rGraph[20][20];
    for (u = 0; u < n; u++)
        for (v = 0; v < n; v++)
             rGraph[u][v] = graph[u][v];

    int parent[n];

    int max_flow = 0;

    while (bfs(rGraph, s, t, parent, n))
    {
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

void dfs(int rGraph[20][20], int s, bool visited[], int n)
{
    visited[s] = true;
    for (int i = 0; i < n; i++)
       if (rGraph[s][i] && !visited[i])
           dfs(rGraph, i, visited, n);
}

void minCut(int graph[20][20], int s, int t, int n)
{
    int u, v;
    int rGraph[20][20];
    for (u = 0; u < n; u++)
        for (v = 0; v < n; v++)
             rGraph[u][v] = graph[u][v];

    int parent[n];

    while (bfs(rGraph, s, t, parent, n))
    {
        int path_flow = INT_MAX;
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
    }

    bool visited[n];
    memset(visited, false, sizeof(visited));
    dfs(rGraph, s, visited, n);

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
         if (visited[i] && !visited[j] && graph[i][j])
              cout << i << " - " << j << endl;

    return;
}

int main() {

    int ch;
    int n;
    int src, dest;
    cout<<"Enter number of nodes : ";
    cin>>n;
    int graph[20][20];

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            graph[i][j] = 0;
        }
    }

    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(i!=j) {
                cout<<"Edge/Capacity from "<<i<<" to "<<j<<" : ";
                cin>>graph[i][j];
            }
        }
    }
    cout<<"\n========================\n";
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cout<<graph[i][j]<<"  ";
        }
        cout<<"\n";
    }
    cout<<"========================\n";

    while(1) {

        cout<<"\n                   MENU";
        cout<<"\n================================================";
        cout<<"\n 1. Print all paths from source to destination";
        cout<<"\n 2. Max flow from source to sink";
        cout<<"\n 3. Min s-t cut";
        cout<<"\n 4. Exit";
        cout<<"\n================================================";
        cout<<"\n";
        cout<<"\nEnter Option : ";
        cin>>ch;

        switch(ch) {

        case 1 :    cout<<"Enter source node index : ";
                    cin>>src;
                    cout<<"Enter destination node index : ";
                    cin>>dest;
                    cout<<"Paths from source("<<src<<") to destination("<<dest<<") : ";
                    cout<<endl;
                    findPaths(graph, src, dest, n);
                    break;

        case 2 :    cout<<"Enter source node index : ";
                    cin>>src;
                    cout<<"Enter destination node index : ";
                    cin>>dest;
                    cout<<"Maximum Flow from source("<<src<<") to destination("<<dest<<") : "<<fordFulkerson(graph, src, dest, n)<<endl;
                    break;

        case 3 :    cout<<"Enter source node index : ";
                    cin>>src;
                    cout<<"Enter destination node index : ";
                    cin>>dest;
                    cout<<"Min s-t cut(s) from source("<<src<<") to destination("<<dest<<") : "<<endl;
                    minCut(graph, src, dest, n);
                    break;

        case 4 :    cout<<"Exiting...\n";
                    exit(0);

        default :   cout<<"Invalid Selection!";

        }

    }

    return 0;
}
