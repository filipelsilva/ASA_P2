#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

enum colors { WHITE, GREY, BLACK };

class Process {
	public:
		int id;
		colors color = WHITE;
		vector<Process*> neighbours = vector<Process*>();

		Process(int id) {
			this->id = id;
		}
};

class Program {
	public:
		int numProcesses = -1;
		int source = -1;
		int sink = -1;
		vector<Process*> processes;

		vector<vector<int>> weights;
		vector<vector<int>> flux;
		vector<vector<int>> residual;

		Program(int nP) {
			this->numProcesses = nP;
			this->source = nP;
			this->sink = nP + 1;
			this->processes = vector<Process*>(nP + 2);
			this->weights = vector<vector<int>>(nP + 2, vector<int>(nP, 0));
			this->flux = vector<vector<int>>(nP + 2, vector<int>(nP, 0));
			this->residual = vector<vector<int>>(nP + 2, vector<int>(nP, 0));
		}

		int getWeights(int id1, int id2);
		void DFS_Visit(Process* n);
		void fordFulkerson();
		void clean();
};

int Program::getWeights(int id1, int id2) {
	return weights[id1][id2];
}

int Program::getFlux(int id1, int id2) {
	return flux[id1][id2];
}

void Program::DFS_Visit(Process* n) {
	stack<Process*> toVisit;
	toVisit.push(n);

	while (!toVisit.empty()) {
		Process* node = toVisit.top();
		node->color = GREY;

		for (Process* next : node->neighbours)
			if (next->color == WHITE)
				toVisit.push(next);

		if (toVisit.top() == node) {
			node->color = BLACK;
			toVisit.pop();
		}
	}
}

void Program::clean() {
	for (Process* n : this->processes)
		delete n;
}

Program parseData() {
	int z, n, k;
	scanf("%d %d", &n, &k);

	Program ret = Program(n);

	/* Adding Processor X and Y */
	ret.processes[ret.source] = new Process(ret.source);
	ret.processes[ret.sink] = new Process(ret.sink);

	int px, py;
	for (z = 0; z < n; z++) {
		ret.processes[z] = new Process(z);
		scanf("%d %d", &px, &py);
		ret.weights[ret.source][z] = px;
		ret.weights[ret.sink][z] = py;
		ret.processes[ret.source]->neighbours.push_back(ret.processes[z]);
		ret.processes[z]->neighbours.push_back(ret.processes[ret.sink]);
	}

	int i, j, c;
	for (z = 0; z < k; z++) {
		scanf("%d %d %d", &i, &j, &c);
		ret.weights[i-1][j-1] = c;
		ret.weights[j-1][i-1] = c;

		if (c != 0) {
			ret.processes[i-1]->neighbours.push_back(ret.processes[j-1]);
			ret.processes[j-1]->neighbours.push_back(ret.processes[i-1]);
		}
	}

	return ret;
}

int main(int argc, char *argv[]) {
	Program program = parseData();
	for (Process* p : program.processes)
		printf("%d\n", p->id);
	for (vector<int> vec : program.weights) {
		for (int i : vec)
			printf("%d\t", i);
		printf("\n");
	}
	program.clean();
	return 0;
}
