#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

void parseData() {
	int n, k;
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++)
		scanf("%d %d", &px, &py);

	for (int i = 0; i < k; i++) {
		scanf("%d %d", &i, &j, &c);
	}
}

int main(int argc, char *argv[]) {
	parseData();
	return 0;
}
