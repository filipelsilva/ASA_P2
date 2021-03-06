#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

enum colors { WHITE, GREY, BLACK, RED };

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
		vector<vector<int>> residual;

		Program(int nP) {
			this->numProcesses = nP;
			this->source = nP;
			this->sink = nP + 1;
			this->processes = vector<Process*>(nP + 2);
			this->residual = vector<vector<int>>(nP + 2, vector<int>(nP, 0));
		}

		int getResidual(int id1, int id2);
		void setResidual(int id1, int id2, int delta);
		vector<Process*> getPath(stack<Process*> visited);
		vector<Process*> DFS();
		int maxFlux(vector<Process*> path);
		int fordFulkerson();
		void clean();
};

int Program::getResidual(int id1, int id2) {
	if (id2 == this->source || id2 == this->sink)
		return residual[id2][id1];

	return residual[id1][id2];
}

void Program::setResidual(int id1, int id2, int delta) {
	if (id2 == this->source || id2 == this->sink)
		residual[id2][id1] += delta;
	else if (id1 == this->source || id1 == this->sink)
		residual[id1][id2] += delta;
	else {
		residual[id1][id2] += delta;
		residual[id2][id1] += delta;
	}
}

vector<Process*> Program::DFS() {
	stack<Process*> toVisit;
	vector<Process*> path, ret;
	toVisit.push(this->processes[this->source]);

	for (Process* p : this->processes)
		p->color = WHITE;

	while (!toVisit.empty()) {
		Process* node = toVisit.top();
		node->color = GREY;
		path.push_back(node);

		if (node == this->processes[this->sink]) {
			for (Process* p : path)
				if (p->color == GREY)
					ret.push_back(p);

			return ret;
		}

		for (Process* next : node->neighbours) {
			if (next->color == WHITE && getResidual(node->id, next->id) != 0) {
				toVisit.push(next);
				next->color = RED;
			}
		}

		if (toVisit.top() == node) {
			node->color = BLACK;
			toVisit.pop();
		}
	}

	return vector<Process*>();
}

int Program::maxFlux(vector<Process*> path) {
	int flux = getResidual(path[0]->id, path[1]->id);
	int tmp = 0;

	for (size_t i = 2; i < path.size(); i++) {
		tmp = getResidual(path[i-1]->id, path[i]->id);

		if (tmp < flux)
			flux = tmp;
	}

	for (size_t i = 1; i < path.size(); i++)
		this->setResidual(path[i-1]->id, path[i]->id, -flux);

	return flux;
}

int Program::fordFulkerson() {
	vector<Process*> augmentation;
	int flux = 0;

	while (true) {
		augmentation = DFS();

		if (augmentation.empty())
			return flux;
		else
			flux += maxFlux(augmentation);
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
		ret.residual[ret.source][z] = px;
		ret.residual[ret.sink][z] = py;
		ret.processes[ret.source]->neighbours.push_back(ret.processes[z]);
		ret.processes[z]->neighbours.push_back(ret.processes[ret.sink]);
	}

	int i, j, c;
	for (z = 0; z < k; z++) {
		scanf("%d %d %d", &i, &j, &c);
		ret.residual[i-1][j-1] = c;
		ret.residual[j-1][i-1] = c;
		ret.processes[i-1]->neighbours.push_back(ret.processes[j-1]);
		ret.processes[j-1]->neighbours.push_back(ret.processes[i-1]);
	}

	return ret;
}

int main(int argc, char *argv[]) {
	Program program = parseData();
	printf("%d\n", program.fordFulkerson());
	program.clean();
	return 0;
}
