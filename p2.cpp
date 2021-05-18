#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

enum colors { WHITE, GREY, BLACK, RED };

class Process {
	public:
		int id;
		colors color = WHITE;
		Process* father;
		vector<Process*> neighbours = vector<Process*>();

		Process(int id) {
			this->father = this;
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
		vector<vector<int>> residual;

		Program(int nP) {
			this->numProcesses = nP;
			this->source = nP;
			this->sink = nP + 1;
			this->processes = vector<Process*>(nP + 2);
			this->weights = vector<vector<int>>(nP + 2, vector<int>(nP, 0));
			this->residual = vector<vector<int>>(nP + 2, vector<int>(nP, 0));
		}

		int getWeights(int id1, int id2);
		int getResidual(int id1, int id2);
		vector<Process*> DFS();
		//int maxFlux(vector<Process*> path);
		int fordFulkerson();
		void clean();
};

int Program::getWeights(int id1, int id2) {
	if (id2 == this->source || id2 == this->sink)
		return weights[id2][id1];

	return weights[id1][id2];
}

int Program::getResidual(int id1, int id2) {
	if (id2 == this->source || id2 == this->sink)
		return weights[id2][id1];

	return residual[id1][id2];
}

vector<Process*> Program::DFS() {
	stack<Process*> toVisit;
	vector<Process*> path;
	toVisit.push(this->processes[this->source]);

	//for (Process* p : this->processes)
	//	p->color = WHITE;

	while (!toVisit.empty()) {
		Process* node = toVisit.top();
		path.push_back(node);

		if (node == this->processes[this->sink]) {
			/*
			for (Process* p : path)
				printf("%d\t", p->id);
			printf("\n");
			*/
			return path;
		}
		//printf("Vizinhos de %d\n", node->id);
		for (Process* next : node->neighbours) {
			//printf("\t%d\n", next->id);
			if (getResidual(node->id, next->id) && next->father != node) {
				toVisit.push(next);
				next->father = node;
			}
		}

		if (toVisit.top() == node) {
			node->color = BLACK;
			toVisit.pop();
		}
	}
	return vector<Process*>();
}

/*
int Program::maxFlux(vector<Process*> path) {
	int flux = getResidual(path[1]->id, path[0]->id);
	int tmp = 0;

	for (int i = 2; i < path.size(); i++) {
		tmp = getResidual(path[i]->id, path[i-1]->id);

		if (tmp < flux)
			flux = tmp;
	}

	return flux;
}
*/
int Program::fordFulkerson() {
	vector<Process*> augmentation;
	int flux = 0;

	while (true) {
		augmentation = DFS();

		if (augmentation.empty())
			return flux;
		else {
			flux += 1;//maxFlux(augmentation);
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
		ret.residual[ret.source][z] = px;
		ret.residual[ret.sink][z] = py;
		ret.processes[ret.source]->neighbours.push_back(ret.processes[z]);
		ret.processes[z]->neighbours.push_back(ret.processes[ret.sink]);
	}

	int i, j, c;
	for (z = 0; z < k; z++) {
		scanf("%d %d %d", &i, &j, &c);
		ret.weights[i-1][j-1] = c;
		ret.weights[j-1][i-1] = c;
		ret.processes[i-1]->neighbours.push_back(ret.processes[j-1]);
		ret.processes[j-1]->neighbours.push_back(ret.processes[i-1]);
	}

	return ret;
}

int main(int argc, char *argv[]) {
	Program program = parseData();
	/*for (Process* p : program.processes) {
		printf("Vizinhos de %d\n", p->id + 1);
		for (Process* pp : p->neighbours)
			printf("%d\t", pp->id + 1);
		printf("\n");
	}*/
	/*for (vector<int> vec : program.weights) {
		for (int i : vec)
			printf("%d\t", i);
		printf("\n");
	}*/
	program.DFS();
	//printf("%d\n", program.fordFulkerson());
	program.clean();
	return 0;
}
