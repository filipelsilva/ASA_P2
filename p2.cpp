#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

enum colors { WHITE, GREY, BLACK };

class Node {
	public:
		int id;
		colors color = WHITE;
		vector<Node*> neighbours = vector<Node*>();

		Node(int id) {
			this->id = id;
		}
};

class Graph {
	public:
		int flux = 0;
		int numProcesses = -1;
		vector<Node*> nodes;
		vector<int> costsX;
		vector<int> costsY;
		vector<vector<int>> commsCost;
		vector<vector<int>> capacity;

		Graph(int nP) {
			this->numProcesses = nP;
			this->nodes = vector<Node*>(nP);
			this->costsX = vector<int>(nP, 0);
			this->costsY = vector<int>(nP, 0);
			this->commsCost = vector<vector<int>>(nP, vector<int>(nP, 0));
			this->capacity = vector<vector<int>>(nP, vector<int>(nP, 0));
		}

		int cost(int id1, int id2);
		void DFS_Visit(Node* n);
		void clean();
};

int Graph::cost(int id1, int id2) {
	if (id1 == -1) /* -1 is the X node */
		return costsX[id2];
	else if (id2 == -1)
		return costsX[id1];
	else if (id1 == -2) /* -2 is the Y node */
		return costsY[id2];
	else if (id2 == -2)
		return costsY[id1];
	else /* Otherwise, values between two processes */
		return commsCost[id1][id2];
}

void Graph::DFS_Visit(Node* n) {
	stack<Node*> toVisit;
	toVisit.push(n);

	while (!toVisit.empty()) {
		Node* node = toVisit.top();
		node->color = GREY;

		for (Node* next : node->neighbours)
			if (next->color == WHITE)
				toVisit.push(next);

		if (toVisit.top() == node) {
			node->color = BLACK;
			toVisit.pop();
		}
	}
}

void Graph::clean() {
	for (Node* n : this->nodes)
		delete n;
}

Graph parseData() {
	int z, n, k;
	scanf("%d %d", &n, &k);

	Graph ret = Graph(n);

	int px, py;
	for (z = 0; z < n; z++) {
		ret.nodes[z] = new Node(z);
		scanf("%d %d", &px, &py);
		ret.costsX[z] = px;
		ret.costsY[z] = py;
	}

	int i, j, c;
	for (z = 0; z < k; z++) {
		scanf("%d %d %d", &i, &j, &c);
		ret.commsCost[i-1][j-1] = c;
		ret.commsCost[j-1][i-1] = c;

		if (c != 0) {
			ret.nodes[i-1]->neighbours.push_back(ret.nodes[j-1]);
			ret.nodes[j-1]->neighbours.push_back(ret.nodes[i-1]);
		}
	}

	return ret;
}

int main(int argc, char *argv[]) {
	Graph process = parseData();
	process.clean();
	return 0;
}
