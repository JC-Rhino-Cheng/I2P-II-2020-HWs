#include <algorithm>//min、max會用到
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <climits>//INT_MAX會用到
using namespace std;

class Segment {
public:
	int left, right;
	Segment(int left = 0, int right = 0) : left(left), right(right) {}
};

struct Cmp {
	bool operator()(const Segment &lhs, const Segment &rhs) const {
		const auto lhs_normalised_len = (lhs.right - lhs.left) / 2;
		const auto rhs_normalised_len = (rhs.right - rhs.left) / 2;

		if (lhs_normalised_len != rhs_normalised_len) return lhs_normalised_len > rhs_normalised_len;
		else return lhs.left < rhs.left;
		
	}
};


int main() {
	int num_of_seats, num_of_students, safe_distance;
	cin >> num_of_seats >> num_of_students >> safe_distance;

	int D = INT_MAX;
	vector<int> pos_of_each_pupil; pos_of_each_pupil.resize(num_of_students + 1, -1);//紀錄每個人各自占用哪個座位。如果不在場(即不占用座位)，儲存-1。resize如果之後空間會變大的話，就會用到-1這個參數把他們全部設定好。
	set<int>relative_seat_status;//座位相對使用情況。ex: 現有六個座位: 沒占用(座位編號1)、沒占用(座位編號2)、A人占用、沒占用、B占用、C占用。則儲存: !!!!座位的編號，而非人的編號!!!!: 3、5、6。因為是儲存座位的編號，所以可以使用set，交給set這個container來幫我們排序
	set<Segment, Cmp> seg;

	relative_seat_status.insert(0);//這兩行，處理左右牆
	relative_seat_status.insert(num_of_seats + 1);
	seg.insert(Segment(0, num_of_seats + 1));//設定初始seg
	
	for (int i = 0; i < 2 * num_of_students; i++) {
		string cmd; int idx;
		cin >> cmd >> idx;

		if (cmd == "i") {
			const auto &insert_seg = seg.cbegin();//把set目前找到的最好的seg拿出來，我會把這個學生安放在這個seg的中間。//我已經用Cmp讓set可以自動幫我把最好的seg放在開頭
			int left, mid, right;
			left = insert_seg->left; right = insert_seg->right;
			mid = (left + right) / 2;

			//開始維護三個容器
			pos_of_each_pupil[idx] = mid;//維護pos_of_each_pupil
			relative_seat_status.insert(mid);//維護relative_seat_status
			//以下維護seg
			seg.erase(insert_seg);
			seg.insert(Segment(left, mid));
			seg.insert(Segment(mid, right));

			//維護D
			if (left != 0) D = min(D, mid - left);
			else if (right != num_of_seats + 1)D = min(D, right - mid);
		}
		else if (cmd == "o") {
			const auto pos_idx = pos_of_each_pupil[idx];//把這個人目前所在的位置的編號找出來
			auto pos_it = relative_seat_status.find(pos_idx);
			const auto left_pos_idx = *(--pos_it);//把這個人左邊的第一個有被占用的位置編號找出來//注意: *(--pos_it)才是對的!*(pos_it--)是錯的!!!!!!
			const auto right_pos_idx = *(++(++pos_it));//把這個人右邊的第一個有被占用的位置編號找出來//因為我在找左邊的it的時候，把他左移了，所以現在需要右移兩次

			//開始維護三個容器
			pos_of_each_pupil[idx] = -1;//維護pos_of_each_pupil
			relative_seat_status.erase(pos_idx);//維護relative_seat_status
			//以下維護seg
			seg.erase(Segment(left_pos_idx, pos_idx));
			seg.erase(Segment(pos_idx, right_pos_idx));
			seg.insert(Segment(left_pos_idx, right_pos_idx));
		}
		
	}

	if (D >= safe_distance)cout << "YES" << endl;
	else cout << "NO" << endl;

	if (D == INT_MAX)cout << "INF" << endl;
	else cout << D << endl;

	system("pause");
}