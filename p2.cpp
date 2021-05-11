#include <cstdio>
#include <vector>

using namespace std;

class Process {
	public:
		int numProcesses = -1;
		vector<int> cpuX = vector<int>();
		vector<int> cpuY = vector<int>();
		vector<vector<int>> commsCost;

		Process(int nP) {
			this->numProcesses = nP;
			commsCost = vector<vector<int>>(nP, vector<int>(nP, 0));
		}
};

Process parseData() {
	int z, n, k;
	scanf("%d %d", &n, &k);

	Process ret = Process(n);

	int px, py;
	for (z = 0; z < n; z++) {
		scanf("%d %d", &px, &py);
		ret.cpuX.push_back(px);
		ret.cpuY.push_back(py);
	}

	int i, j, c;
	for (z = 0; z < k; z++) {
		scanf("%d %d %d", &i, &j, &c);
		ret.commsCost[i-1][j-1] = c;
		ret.commsCost[j-1][i-1] = c;
	}

	return ret;
}

int main(int argc, char *argv[]) {
	Process process = parseData();
	return 0;
}
