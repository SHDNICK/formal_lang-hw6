#include <iostream>
#include <string>
#include <set>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;


class situation {
public:
	pair< char, string > tr;
	int i;
	int pt;

	situation(pair< char, string > tr, int i, int pt) : tr(tr), i(i), pt(pt) {}
	bool operator < (const situation& r) const{
		if (i < r.i) {
			return true;
		}
		else if (i == r.i && pt < r.pt) {
			return true;
		}
		else if (i == r.i && pt == r.pt && tr < r.tr) {
			return true;
		}
		else {
			return false;
		}
	}
};


class analyzer {
public:
	vector< set< situation >  > D;
	string word;
	vector< pair< char, string > > P = { {'R', "S"}, { 'S', "Sa" }, { 'S', "C" }, { 'C', "Dd" }, { 'D', "cD" }, { 'S', "SSb" }, {'D', ""} };

	analyzer(const string& word) : word(word) {
		D.resize(word.size() + 1);
	}

	void Predict(int j) {
		vector< situation > add;

		for (auto s : D[j]) {
			for (auto r : P) {
				if (s.tr.second[s.pt] == r.first) {
					add.push_back(situation(r, j, 0));
				}
			}
		}
		for (auto s : add) {
			D[j].insert(s);
		}
		return;
	}

	void Scan(int j) {
		for (auto s : D[j]) {
			if (s.tr.second[s.pt] == word[j]) {
				D[j + 1].insert(situation(s.tr, s.i, s.pt + 1));
			}
		}
		return;
	}

	void Complete(int j) {
		vector< situation > add;

		for (auto r : D[j]) {
			if (r.pt != r.tr.second.size()) continue;
			for (auto s : D[r.i]) {
				if (s.tr.second[s.pt] == r.tr.first) {
					add.push_back(situation(s.tr, s.i, s.pt + 1));
				}
			}
		}

		for (auto s : add) {
			D[j].insert(s);
		}

		return;
	}

	bool Check() {
		D[0].insert(situation(P[0], 0, 0));
		int change = -1;
		while (D[0].size() != change) {
			change = D[0].size();
			Predict(0);
			Complete(0);
		}
		cout << "------------------" << endl;
		cout << "D" << 0 << ":" << endl;
		for (auto s : D[0])
			cout << s.tr.first << " " << s.tr.second << " " << s.pt << " " << s.i << endl;
		for (int j = 1; j <= word.size(); ++j) {
			Scan(j - 1);
			int change = -1;
			while (D[j].size() != change) {
				change = D[j].size();
				Predict(j);
				Complete(j);
			}
			cout << "------------------" << endl;
			cout << "D" << j <<  ":" << endl;
			for (auto s : D[j])
				cout << s.tr.first << " " << s.tr.second << " " << s.pt << " " << s.i << endl;
		}
		if (D[word.size()].count(situation(P[0], 0, 1)) != 0) {
			return true;
		}
		else return false;
	}

};


int main() {
	string word_in_L = "";
	string word_not_in_L = "";

	cout << "EXAMPLES:" << endl;
	cout << word_in_L << endl;
	if (analyzer(word_in_L).Check()) {
		cout << "RESULT: Yes" << endl;
		cout << "_______________________________________________________________________" << endl;
	}
	else {
		cout << "RESULT: No" << endl;
		cout << "_______________________________________________________________________" << endl;
	}

	cout << word_not_in_L << endl;
	if (analyzer(word_not_in_L).Check()) {
		cout << "RESULT: Yes" << endl;
		cout << "_______________________________________________________________________" << endl;
	}
	else {
		cout << "RESULT: No" << endl;
		cout << "_______________________________________________________________________" << endl;
	}



	int n;
	cin >> n;

	string word;
	for (int i = 0; i < n; i++) {
		cin >> word;
		if (analyzer(word).Check()) {
			cout << "RESULT: Yes" << endl;
			cout << "_______________________________________________________________________";
		}
		else {
			cout << "RESULT: No" << endl;
			cout << "_______________________________________________________________________";
		}
	}

	system("pause");
}
