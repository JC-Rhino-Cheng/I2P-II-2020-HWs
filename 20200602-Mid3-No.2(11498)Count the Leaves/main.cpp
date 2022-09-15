#include <iostream>
#include <set>
using namespace std;

int main() {
	int num_of_pairs;

	while (cin >> num_of_pairs) {
		if (num_of_pairs == 0)break;
		
		set<int>all_nodes, parents;
		while (num_of_pairs--) {
			int parent, child; cin >> parent >> child;

			all_nodes.insert(parent); all_nodes.insert(child);
			parents.insert(parent);
		}
		int root_idx; cin >> root_idx;//沒屁用的東西

		cout << all_nodes.size() - parents.size() << endl;
	}

	system("pause");
}