#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

class Process {
	public:
		int numProcesses = -1;
		vector<int> cpuX = vector<int>();
		vector<int> cpuY = vector<int>();
		vector<vector<int>> commsCost;

		Process(int nP) {
			this->numProcesses = nP;
			commsCost = vector<vector<int>>(nP, vector<int>(nP));
		}
};

Process parseData() {
	int n, k;
	scanf("%d %d", &n, &k);

	Process ret = Process(n);

	int px, py;
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &px, &py);
		ret.cpuX.push_back(px);
		ret.cpuY.push_back(py);
	}

	int i, j, c;
	for (int z = 0; z < k; z++) {
		scanf("%d %d %d", &i, &j, &c);
		ret.commsCost[i-1][j-1] = c;
		ret.commsCost[j-1][i-1] = c;
	}

	return ret;
}

int main(int argc, char *argv[]) {
	Process process = parseData();

	//for (int i = 0; i < globalN; i++) {
	//	for (int j = 0; j < globalN; j++) {
	//		printf("%d\t", process.commsCost[i][j]);
	//	}
	//	printf("\n");
	//}
	return 0;
}
