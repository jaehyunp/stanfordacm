#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <cstring>
#include <map>jj
size_t toId(char c) {
	return static_cast<size_t>(c - '0');
}
struct node {
	std::vector<node *> nodes;
	int id;

	node() {
		nodes.resize(26, nullptr);
		id = -1;
	}

	node *initOrNext(char c) {
		size_t id = toId(c);
		if (nodes[id] == nullptr) {
			nodes[id] = new node();
		}
		return nodes[id];
	}

};

struct trie {
	node *root = nullptr;
	void addWord(const std::string &str) {
		if (root == nullptr) {
			root = new node();
		}

		node *node = root;
		for (const auto &c: str) {
			node = node->initOrNext(c);
		}
	}
};
