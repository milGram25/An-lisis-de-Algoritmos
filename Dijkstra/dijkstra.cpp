#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int destino;
    int peso;
};

void dijkstra(int inicio, const vector<vector<Edge>>& grafo) {
    int n = grafo.size();
    vector<int> distancia(n, numeric_limits<int>::max());
    vector<int> previo(n, -1); 
    distancia[inicio] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, inicio});

    while (!pq.empty()) {
        int dist_actual = pq.top().first;
        int nodo = pq.top().second;
        pq.pop();

        if (dist_actual > distancia[nodo]) continue;

        for (const Edge& e : grafo[nodo]) {
            int nuevo_dist = dist_actual + e.peso;
            if (nuevo_dist < distancia[e.destino]) {
                distancia[e.destino] = nuevo_dist;
                previo[e.destino] = nodo; // guardamos de donde venimos
                pq.push({nuevo_dist, e.destino});
            }
        }
    }

    cout << "Distancias minimas desde el nodo " << inicio << ":\n";
    for (int i = 0; i < n; i++) {
        if (distancia[i] == numeric_limits<int>::max()) {
            cout << "Nodo " << i << ": INFINITO\n";
        } else {
            cout << "Nodo " << i << ": " << distancia[i] << "  Camino: ";
            // reconstruir camino
            vector<int> camino;
            for (int v = i; v != -1; v = previo[v]) {
                camino.push_back(v);
            }
            for (int j = camino.size() - 1; j >= 0; j--) {
                cout << camino[j];
                if (j > 0) cout << " -> ";
            }
            cout << "\n";
        }
    }
}

int main() {
    int n, m;
    cout << "Ingrese el numero de nodos: ";
    cin >> n;
    cout << "Ingrese el numero de aristas: ";
    cin >> m;

    vector<vector<Edge>> grafo(n);

    cout << "Ingrese las aristas en el formato: origen destino peso\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        grafo[u].push_back({v, w});
    }

    int inicio;
    cout << "Ingrese el nodo inicial: ";
    cin >> inicio;

        for (int i = 0; i < n; i++) {
    for (const Edge& e : grafo[i]) {
        cout << i << " -> " << e.destino << " (peso: " << e.peso << ")\n";
    }
}

    dijkstra(inicio, grafo);

    return 0;
}
