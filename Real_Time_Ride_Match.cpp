#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <limits>

using namespace std;

// =======================
// DRIVER
// =======================

struct Driver{
    int id;
    double x, y;
    Driver(int i, double px, double py) {
        id = i; 
        x = px;
        y = py;
    }
};

// ========================
// KD TREE
// ========================

struct KDNode{
    Driver driver;
    KDNode* left;
    KDNode* right;
    KDNode(Driver d) : driver(d) {
        left = nullptr;
        right = nullptr;
    }
};

class KDTree {
    private:
    KDNode* insertHelper(KDNode* root, Driver driver, int depth) {
        if(!root)
          return new KDNode(driver);
        int axis = depth % 2;
        if((axis == 0 && driver.x < root->driver.x) || (axis == 1 && driver.y < root->driver.y))
          root->left = insertHelper(root->left, driver, depth + 1);
        else
          root->right = insertHelper(root->right, driver, depth + 1);
        return root;      
    }
    double distance(double x1, double y1, double x2, double y2) {
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }
    void nearestHelper(KDNode* root, double x, double y, Driver& best, double& bestDist, int depth) {
        if(!root)
          return;
        double current = distance(x, y, root->driver.x, root->driver.y);
        if(current < bestDist){
            bestDist = current;
            best = root->driver;
        }  
        int axis = depth % 2;
        KDNode* nearSide;
        KDNode* farSide;
        if((axis == 0 && x < root->driver.x) || (axis == 1 && y < root->driver.y)){
            nearSide = root->left;
            farSide = root->right;
        }
        else {
            nearSide = root->right;
            farSide = root->left;
        }
        nearestHelper(nearSide, x, y, best, bestDist, depth + 1);
        double planeDistance = (axis == 0) ? abs(x - root->driver.x) : abs(y - root->driver.y);
        if(planeDistance < bestDist) {
            nearestHelper(farSide, x, y, best, bestDist, depth + 1);
        }
    }
    public:
    KDNode* root;
    KDTree(){
        root = nullptr;
    }
    void insert(Driver driver) {
        root = insertHelper(root, driver, 0);
    }
    Driver nearestDriver(double x, double y) {
        Driver best(-1, 0, 0);
        double bestDist = numeric_limits<double>::max();
        nearestHelper(root, x, y, best, bestDist, 0);
        return best;
    }
};

// =========================
// GRAPH + DIJKSTRA
// =========================

class Graph {
    private:
    int V;
    vector<vector<pair<int,int>>> adj;
    public:
    Graph(int n) {
        V = n;
        adj.resize(V);
    }
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    int shortestPath(int source, int destination) {
        vector<int> dist(V, INT_MAX);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
        dist[source] = 0;
        pq.push({0, source});
        while(!pq.empty()) {
            auto current = pq.top();
            pq.pop();
            int node = current.second;
            int cost = current.first;
            if(cost > dist[node])
              continue;
            for(auto edge : adj[node]) {
                int next = edge.first;
                int weight = edge.second;
                if(dist[next] > dist[node] + weight) {
                    dist[next] = dist[node] + weight;
                    pq.push({dist[next], next});
                } 
            }  
        }
        return dist[destination];
    }
};

// =============================
// SURGE PRICING
// =============================

class SurgePricing {
    private:
    priority_queue<double, vector<double>, greater<double>> surgeFactors;
    public:
    void addZone(double factor) {
        surgeFactors.push(factor);
    }
    double currentSurge() {
        if(surgeFactors.empty())
          return 1.0;
          return surgeFactors.top();
    }
};

// ================================
// MAIN
// ================================

int main() {
    cout << "===== REAL TIME RIDE MATCHING =====\n\n";

    vector<Driver> drivers = {{1, 2, 3}, {2, 8, 4}, {3, 5, 7}, {4, 1, 9}, {5, 9, 2}};
    KDTree tree;
    for(auto d : drivers)
      tree.insert(d);

    double riderX = 4;
    double riderY = 5;
    Driver nearest = tree.nearestDriver(riderX, riderY);
    cout << "Rider Location: ("
         << riderX
         << ", "
         << riderY
         << ")\n";
    cout << "Matched Driver ID: "
         << nearest.id
         << "\n\n";

    Graph city(6);
    city.addEdge(0,1,4);
    city.addEdge(0,2,2);
    city.addEdge(1,3,5);
    city.addEdge(2,3,8);
    city.addEdge(2,4,10);
    city.addEdge(3,5,6);
    city.addEdge(4,5,3);
    int routeDistance = city.shortestPath(0, 5);
    cout << "Shortest Route Distance: "
         << routeDistance
         << "\n\n";

    SurgePricing surge;
    surge.addZone(1.8);
    surge.addZone(1.5);
    surge.addZone(2.2);
    double baseFare = 100;
    double finalFare = baseFare * surge.currentSurge();
    cout << "Base Fare: "
         << baseFare
         << "\n";
    cout << "Surge Multiplier: "
         << surge.currentSurge()
         << "x\n";
    cout << "Final Fare: "
         << finalFare
         << "\n";
    return 0;                             
}