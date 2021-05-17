#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

#define SOURCE -1
#define SINK -2

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
		vector<Process*> processes;

		/* Costs of communication between/operation of processes */
		vector<int> costsX;
		vector<int> costsY;
		vector<vector<int>> commsCost;

		vector<int> fluxX;
		vector<int> fluxY;
		vector<vector<int>> flux;

		Program(int nP) {
			this->numProcesses = nP + 2;
			this->processes = vector<Process*>(nP + 2);
			this->costsX = vector<int>(nP, 0);
			this->costsY = vector<int>(nP, 0);
			this->commsCost = vector<vector<int>>(nP, vector<int>(nP, 0));
			this->fluxX = vector<int>(nP, 0);
			this->fluxY = vector<int>(nP, 0);
			this->flux = vector<vector<int>>(nP, vector<int>(nP, 0));
		}

		int capacity(int id1, int id2);
		void DFS_Visit(Process* n);
		void clean();
};

int Program::capacity(int id1, int id2) {
	if (id1 == SOURCE) /* -1 is the X node */
		return costsX[id2];
	else if (id2 == SOURCE)
		return costsX[id1];
	else if (id1 == SINK) /* SINK is the Y node */
		return costsY[id2];
	else if (id2 == SINK)
		return costsY[id1];
	else /* Otherwise, values between two processes */
		return commsCost[id1][id2];
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

	int px, py;
	for (z = 0; z < n; z++) {
		ret.processes[z] = new Process(z);
		scanf("%d %d", &px, &py);
		ret.costsX[z] = px;
		ret.costsY[z] = py;
	}

	/* Adding Processor X and Y */
	ret.processes[z] = new Process(SOURCE);
	ret.processes[z+1] = new Process(SINK);

	int i, j, c;
	for (z = 0; z < k; z++) {
		scanf("%d %d %d", &i, &j, &c);
		ret.commsCost[i-1][j-1] = c;
		ret.commsCost[j-1][i-1] = c;

		if (c != 0) {
			ret.processes[i-1]->neighbours.push_back(ret.processes[j-1]);
			ret.processes[j-1]->neighbours.push_back(ret.processes[i-1]);
		}
	}

	return ret;
}

int main(int argc, char *argv[]) {
	Program program = parseData();
	printf("%d\n", program.processes[program.numProcesses-1]->id);
	program.clean();
	return 0;
}
