#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

struct BinaryTree {
	BinaryTree() : LeftBranch(NULL), RightBranch(NULL) {
		item.first = '*';
		item.second = 0;
	}
	std::pair<char, int> item;
	BinaryTree *LeftBranch;
	BinaryTree *RightBranch;
};

class Huff {
public:
	Huff() { string = ""; }
	Huff(std::string str) : string(str) {}
	~Huff() {}
	void Print_str() {
		std::cout << string << std::endl;
	}

	//основной алгоритм
	void Huffman() {
		BinaryTree *i;
		BinaryTree *j;
		BinaryTree temp;
		H = Frequency(string);
		if (H.size() == 1) {
			i = new BinaryTree;
			*i = ExtractMin(H);
			temp.item.second = i->item.second;
			temp.LeftBranch = i;
			H.push_back(temp);
		}
		else {
			int count = H.size();
			for (size_t k = count + 1; k <= (2 * count - 1); ++k) {
				i = new BinaryTree;
				j = new BinaryTree;
				*i = ExtractMin(H);
				*j = ExtractMin(H);
				temp.item.second = i->item.second + j->item.second;
				temp.LeftBranch = i;
				temp.RightBranch = j;
				H.push_back(temp);
			}
		}
		MakeTable(&H[0]);
		std::cout << m.size() << " " << size_encode() << std::endl;
		print_table();
		encode();
	}

	

private:
	// вычисление частот
	std::vector<BinaryTree> Frequency(std::string input_str) {
		BinaryTree pair_H;
		std::vector<BinaryTree> HH;
		std::string alphabit = "abcdefghijklmnopqrstuvwxyz";
		std::vector<int> freq(alphabit.size());
		for (size_t i = 0; i < alphabit.size(); ++i) {
			for (auto& ch : input_str) {
				if (ch == alphabit[i]) {
					freq[i] += 1;
				}
			}
		}
		for (size_t i = 0; i < freq.size(); ++i) {
			if (freq[i] != 0) {
				pair_H.item.first = alphabit[i];
				pair_H.item.second = freq[i];
				HH.push_back(pair_H);
			}
		}
		return HH;
	}

	// извлекает из очереди элемент минимальным приоритетом
	BinaryTree ExtractMin(std::vector<BinaryTree> &HH) {
		BinaryTree ch = *std::min_element(HH.begin(), HH.end(),
			[](const BinaryTree& lhs, const BinaryTree& rhs) {
			return lhs.item.second < rhs.item.second; });
		int i = 0;
		for (auto& item : HH) {
			if (item.item.first == ch.item.first && item.item.second == ch.item.second) {
				HH.erase(HH.begin() + i);
				break;
			}
			i++;
		}
		return ch;
	}


	void MakeTable(BinaryTree *Tree)
	{
		if (Tree->LeftBranch == NULL || Tree->RightBranch == NULL) {
			m[Tree->item.first] = str;
			str.pop_back();
		}
		if (Tree->LeftBranch != NULL) {
			str += '0';
			MakeTable(Tree->LeftBranch);
		}
		if (Tree->RightBranch != NULL) {
			str += '1';
			MakeTable(Tree->RightBranch);
		}
	}
	void print_table() {
		for (auto & i : m) {
			std::cout << i.first << ": " << i.second << std::endl;
		}
	}
	void count_word() {

	}
	int size_encode() {
		std::string temp_str;
		for (auto & i : string) {
			temp_str += m[i];
		}
		return temp_str.size();
	}

	void encode() {
		for (auto & i : string) {
			std::cout << m[i];
		}
		std::cout << std::endl;
	}

	std::string str;
	std::string string;
	std::vector<BinaryTree> H;
	std::map <char,std::string> m;
};


int main() {
	std::string str;
	std::cin >> str;
	Huff huff(str);
	huff.Huffman();
	return 0;
}