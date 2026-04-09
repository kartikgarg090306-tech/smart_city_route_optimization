#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cmath>
#include <chrono>

using namespace std;

#define INF 1000000000


/* =========================================================
                GRAPH CLASS
=========================================================*/

class Graph {

public:

    int V;
    vector<vector<int>> adj;

    Graph(int v){

        V=v;

        adj.resize(V,vector<int>(V));
    }

    void inputGraph(){

        cout<<"Enter adjacency matrix:\n";

        for(int i=0;i<V;i++)
            for(int j=0;j<V;j++)
                cin>>adj[i][j];
    }

    void display(){

        cout<<"\nGraph Matrix\n";

        for(int i=0;i<V;i++){

            for(int j=0;j<V;j++)
                cout<<adj[i][j]<<" ";

            cout<<endl;
        }
    }
};



/* =========================================================
                GREEDY ALGORITHMS
=========================================================*/


void dijkstra(){

    int V;

    cout<<"Enter number of vertices: ";
    cin>>V;

    Graph g(V);

    g.inputGraph();

    int src;

    cout<<"Enter source vertex: ";
    cin>>src;

    vector<int> dist(V,INF);

    vector<bool> visited(V,false);

    dist[src]=0;

    for(int count=0;count<V-1;count++){

        int u=-1;
        int minDist=INF;

        for(int i=0;i<V;i++)
            if(!visited[i] && dist[i]<minDist){
                minDist=dist[i];
                u=i;
            }

        if(u==-1) break;

        visited[u]=true;

        for(int v=0;v<V;v++)
            if(g.adj[u][v] && !visited[v] &&
               dist[u]+g.adj[u][v] < dist[v])
                dist[v]=dist[u]+g.adj[u][v];
    }

    cout<<"\nShortest Distances\n";

    for(int i=0;i<V;i++)
        cout<<"Vertex "<<i<<" -> "<<dist[i]<<endl;
}



void prim(){

    int V;

    cout<<"Enter number of vertices: ";
    cin>>V;

    Graph g(V);

    g.inputGraph();

    vector<int> key(V,INF),parent(V);

    vector<bool> mst(V,false);

    key[0]=0;

    parent[0]=-1;

    for(int count=0;count<V-1;count++){

        int u=-1;
        int minKey=INF;

        for(int i=0;i<V;i++)
            if(!mst[i] && key[i]<minKey){
                minKey=key[i];
                u=i;
            }

        mst[u]=true;

        for(int v=0;v<V;v++)
            if(g.adj[u][v] && !mst[v] && g.adj[u][v]<key[v]){

                parent[v]=u;

                key[v]=g.adj[u][v];
            }
    }

    cout<<"\nMinimum Spanning Tree\n";

    for(int i=1;i<V;i++)
        cout<<parent[i]<<" - "<<i<<" weight "<<g.adj[i][parent[i]]<<endl;
}



void activitySelection(){

    int n;

    cout<<"Enter number of activities: ";
    cin>>n;

    vector<int> start(n),finish(n);

    cout<<"Enter start times\n";

    for(int i=0;i<n;i++)
        cin>>start[i];

    cout<<"Enter finish times\n";

    for(int i=0;i<n;i++)
        cin>>finish[i];

    vector<pair<int,int>> act;

    for(int i=0;i<n;i++)
        act.push_back({finish[i],start[i]});

    sort(act.begin(),act.end());

    cout<<"\nSelected Activities\n";

    int lastFinish=-1;

    for(auto a:act){

        if(a.second>=lastFinish){

            cout<<"Start "<<a.second<<" Finish "<<a.first<<endl;

            lastFinish=a.first;
        }
    }
}



/* =========================================================
                DYNAMIC PROGRAMMING
=========================================================*/


void floydWarshall(){

    int V;

    cout<<"Enter vertices: ";
    cin>>V;

    vector<vector<int>> dist(V,vector<int>(V));

    cout<<"Enter adjacency matrix\n";

    for(int i=0;i<V;i++)
        for(int j=0;j<V;j++)
            cin>>dist[i][j];

    for(int k=0;k<V;k++)
        for(int i=0;i<V;i++)
            for(int j=0;j<V;j++)
                if(dist[i][k]+dist[k][j] < dist[i][j])
                    dist[i][j]=dist[i][k]+dist[k][j];

    cout<<"\nAll Pair Shortest Paths\n";

    for(int i=0;i<V;i++){

        for(int j=0;j<V;j++)
            cout<<dist[i][j]<<" ";

        cout<<endl;
    }
}



void bellmanFord(){

    int V,E;

    cout<<"Enter vertices and edges: ";
    cin>>V>>E;

    struct Edge{int u,v,w;};

    vector<Edge> edges(E);

    cout<<"Enter edges u v weight\n";

    for(int i=0;i<E;i++)
        cin>>edges[i].u>>edges[i].v>>edges[i].w;

    int src;

    cout<<"Enter source: ";
    cin>>src;

    vector<int> dist(V,INF);

    dist[src]=0;

    for(int i=1;i<V;i++)
        for(auto e:edges)
            if(dist[e.u]!=INF && dist[e.u]+e.w < dist[e.v])
                dist[e.v]=dist[e.u]+e.w;

    cout<<"\nShortest Distances\n";

    for(int i=0;i<V;i++)
        cout<<i<<" "<<dist[i]<<endl;
}



/* =========================================================
                TRAVELLING SALESMAN
=========================================================*/


int tspDP(vector<vector<int>>& dist,int mask,int pos,
          vector<vector<int>>& dp,int n){

    if(mask==(1<<n)-1)
        return dist[pos][0];

    if(dp[mask][pos]!=-1)
        return dp[mask][pos];

    int ans=INF;

    for(int city=0;city<n;city++){

        if(!(mask&(1<<city))){

            int newAns =
            dist[pos][city] +
            tspDP(dist,mask|1<<city,city,dp,n);

            ans=min(ans,newAns);
        }
    }

    return dp[mask][pos]=ans;
}



void travellingSalesman(){

    int n;

    cout<<"Enter cities: ";
    cin>>n;

    vector<vector<int>> dist(n,vector<int>(n));

    cout<<"Enter cost matrix\n";

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>dist[i][j];

    vector<vector<int>> dp(1<<n,vector<int>(n,-1));

    cout<<"Minimum Tour Cost: "
        <<tspDP(dist,1,0,dp,n)<<endl;
}



/* =========================================================
                BACKTRACKING
=========================================================*/


bool isSafe(vector<vector<int>>& board,int row,int col,int n){

    for(int i=0;i<col;i++)
        if(board[row][i])
            return false;

    for(int i=row,j=col;i>=0&&j>=0;i--,j--)
        if(board[i][j])
            return false;

    for(int i=row,j=col;i<n&&j>=0;i++,j--)
        if(board[i][j])
            return false;

    return true;
}



bool solveNQ(vector<vector<int>>& board,int col,int n){

    if(col>=n)
        return true;

    for(int i=0;i<n;i++){

        if(isSafe(board,i,col,n)){

            board[i][col]=1;

            if(solveNQ(board,col+1,n))
                return true;

            board[i][col]=0;
        }
    }

    return false;
}



void nQueens(){

    int n;

    cout<<"Enter N: ";
    cin>>n;

    vector<vector<int>> board(n,vector<int>(n,0));

    if(!solveNQ(board,0,n)){

        cout<<"No Solution\n";
        return;
    }

    cout<<"\nBoard\n";

    for(auto r:board){

        for(int x:r)
            cout<<x<<" ";

        cout<<endl;
    }
}



/* =========================================================
                SUBSET SUM
=========================================================*/


void subsetSumUtil(vector<int>& set,int target,
                   int index,int sum){

    if(sum==target){

        cout<<"Subset Found\n";
        return;
    }

    if(index==set.size() || sum>target)
        return;

    subsetSumUtil(set,target,index+1,sum+set[index]);

    subsetSumUtil(set,target,index+1,sum);
}



void subsetSum(){

    int n,target;

    cout<<"Enter number of elements: ";
    cin>>n;

    vector<int> set(n);

    cout<<"Enter elements\n";

    for(int i=0;i<n;i++)
        cin>>set[i];

    cout<<"Enter target\n";
    cin>>target;

    subsetSumUtil(set,target,0,0);
}



/* =========================================================
                GRAPH ANALYSIS
=========================================================*/


string detectGraphType(int V,int E){

    double density=(double)E/(V*(V-1));

    if(density<0.25)
        return "Sparse";

    else if(density<0.75)
        return "Moderate";

    else
        return "Dense";
}



void recommendAlgorithm(int V,int E){

    string type=detectGraphType(V,E);

    cout<<"\nGraph Type: "<<type<<endl;

    if(type=="Sparse")
        cout<<"Recommended Algorithm: Dijkstra\n";

    else if(type=="Moderate")
        cout<<"Recommended Algorithm: Bellman Ford\n";

    else
        cout<<"Recommended Algorithm: Floyd Warshall\n";
}



/* =========================================================
                COMPARISON SYSTEM
=========================================================*/


void compareAlgorithms(){

    int V,E;

    cout<<"Enter vertices: ";
    cin>>V;

    cout<<"Enter edges: ";
    cin>>E;

    cout<<"\n===== COMPLEXITIES =====\n";

    cout<<"Dijkstra        O((V+E)logV)\n";
    cout<<"Prim            O(ElogV)\n";
    cout<<"FloydWarshall   O(V^3)\n";
    cout<<"BellmanFord     O(VE)\n";
    cout<<"TSP             O(n^2 * 2^n)\n";
    cout<<"NQueens         O(N!)\n";
    cout<<"SubsetSum       O(2^n)\n";

    double dijkstraTime=(V+E)*log(V+1);

    double primTime=E*log(V+1);

    double floydTime=V*V*V;

    double bellmanTime=V*E;

    cout<<"\nEstimated Work Units\n";

    cout<<"Dijkstra "<<dijkstraTime<<endl;

    cout<<"Prim "<<primTime<<endl;

    cout<<"FloydWarshall "<<floydTime<<endl;

    cout<<"BellmanFord "<<bellmanTime<<endl;

    recommendAlgorithm(V,E);
}



/* =========================================================
                THEORY MODULE
=========================================================*/


void explainAlgorithms(){

    cout<<"\nGREEDY\n";
    cout<<"Locally optimal choices!!!\n";
    cout<<"A Greedy algorithm makes the best local choice at each step to try to reach a global optimum.\n";
    cout<<"Once a decision is made, it cannot be changed later.\n";
    cout<<"It works well for problems where local optimal choices lead to global optimal solutions.\n";
    cout<<"Greedy algorithms are usually simple and efficient.\n";
    cout<<"Examples: Dijkstra’s Algorithm, Prim’s Algorithm, Activity Selection.\n";
    cout<<"Typical time complexity: around O(E log V) or O(n log n) depending on the problem.\n";
    
    cout<<"\nDYNAMIC PROGRAMMING\n";
    cout<<"Stores overlapping subproblems!!!\n";
    cout<<"Dynamic Programming solves problems by breaking them into smaller overlapping subproblems.\n";
    cout<<"The results of subproblems are stored and reused to avoid repeated calculations.\n";
    cout<<"It is useful when a problem has optimal substructure and overlapping subproblems.\n";
    cout<<"DP improves efficiency compared to brute-force methods\n";
    cout<<"Examples: Floyd–Warshall, Bellman–Ford, Travelling Salesman Problem (TSP).\n";
    cout<<"Typical time complexity: can range from O(V³) to O(n²·2ⁿ) depending on the algorithm.\n";

    cout<<"\nBACKTRACKING\n";
    cout<<"Explores all possibilities!!!\n";
    cout<<"Backtracking is a technique that tries all possible solutions by exploring one option at a time.\n";
    cout<<"If a partial solution does not satisfy constraints, the algorithm backtracks and tries another path.\n";
    cout<<"It is commonly used for constraint satisfaction and combinatorial problems.\n";
    cout<<"Backtracking guarantees finding a correct solution but can be computationally expensive.\n";
    cout<<"Examples: N-Queens, Subset Sum, Hamiltonian Cycle.\n";
    cout<<"Typical time complexity: usually exponential, such as O(2ⁿ) or O(n!).\n";
}


void showSmartCityMap() {

cout<<"\n================ SMART CITY ROAD NETWORK ================\n\n";

cout<<"                         (Airport)\n";
cout<<"                            A\n";
cout<<"                           / \\\n";
cout<<"                          /   \\\n";
cout<<"                        B ----- C\n";
cout<<"                       / \\     / \\\n";
cout<<"                      /   \\   /   \\\n";
cout<<"                    D ----- E ----- F\n";
cout<<"                   / \\     / \\     / \\\n";
cout<<"                  /   \\   /   \\   /   \\\n";
cout<<"                G ----- H ----- I ----- J\n";
cout<<"                 \\     / \\     / \\     /\n";
cout<<"                  \\   /   \\   /   \\   /\n";
cout<<"                K ----- L ----- M ----- N\n";
cout<<"                 /     / \\     / \\     \\\n";
cout<<"                /     /   \\   /   \\     \\\n";
cout<<"              O ----- P ----- Q ----- R\n";
cout<<"               \\     /       \\       /\n";
cout<<"                \\   /         \\     /\n";
cout<<"                  S ----------- T\n";
cout<<"                       |\n";
cout<<"                       |\n";
cout<<"                     (Central Hub)\n";
cout<<"                        U\n";
cout<<"                       / \\\n";
cout<<"                      V   W\n";

cout<<"\nNodes = Intersections\n";
cout<<"Edges = Roads\n";
cout<<"=========================================================\n";
}


/* =========================================================
                MAIN MENU
=========================================================*/


int main(){
    
    
    showSmartCityMap();

    while(true){

        cout<<"\n===== SMART CITY ROUTE OPTIMIZATION =====\n";

        cout<<"1 Greedy Algorithms\n";
        cout<<"2 Dynamic Programming\n";
        cout<<"3 Backtracking\n";
        cout<<"4 Compare Algorithms\n";
        cout<<"5 Algorithm Theory\n";
        cout<<"6 Exit\n";

        int choice;
        cin>>choice;

        if(choice==1){

            int c;

            cout<<"\n1 Dijkstra\n2 Prim\n3 Activity Selection\n";

            cin>>c;

            if(c==1) dijkstra();
            else if(c==2) prim();
            else if(c==3) activitySelection();
        }

        else if(choice==2){

            int c;

            cout<<"\n1 Floyd Warshall\n2 Bellman Ford\n3 Travelling Salesman\n";

            cin>>c;

            if(c==1) floydWarshall();
            else if(c==2) bellmanFord();
            else if(c==3) travellingSalesman();
        }

        else if(choice==3){

            int c;

            cout<<"\n1 N Queens\n2 Subset Sum\n";

            cin>>c;

            if(c==1) nQueens();
            else if(c==2) subsetSum();
        }

        else if(choice==4)
            compareAlgorithms();

        else if(choice==5)
            explainAlgorithms();

        else if(choice==6)
            break;
    }
}