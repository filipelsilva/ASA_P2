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

		vector<vector<int>> commsCost;
		vector<vector<int>> flux;

		Program(int nP) {
			this->numProcesses = nP;
			this->source = nP;
			this->sink = nP + 1;
			this->processes = vector<Process*>(nP + 2);
			this->commsCost = vector<vector<int>>(nP + 2, vector<int>(nP, 0));
			this->flux = vector<vector<int>>(nP + 2, vector<int>(nP, 0));
		}

		int capacity(int id1, int id2);
		void DFS_Visit(Process* n);
		void clean();
};

int Program::capacity(int id1, int id2) {
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
		ret.commsCost[ret.source][z] = px;
		ret.commsCost[ret.sink][z] = py;
	}

	/* Adding Processor X and Y */
	ret.processes[z] = new Process(ret.source);
	ret.processes[z+1] = new Process(ret.sink);

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
	for (Process* p : program.processes)
		printf("%d\n", p->id);
	for (vector<int> vec : program.commsCost) {
		for (int i : vec) {
			printf("%d\t", i);
		}
		printf("\n");
	}
	program.clean();
	return 0;
}
