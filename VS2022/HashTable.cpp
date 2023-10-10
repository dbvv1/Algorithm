#include <vector>
#include <algorithm>


class HashTable {
public:
	HashTable(size_t size = 8) : elems(size, std::make_pair(-1, -1)), count(0) {}

	void put(int key, int value) {
		// Check load factor
		if (static_cast<double>(count) / elems.size() > 0.7)
			resize(elems.size() * 2);

		int index = key % elems.size();
		while (elems[index].first != -1 && elems[index].first != key) {
			index = (index + 1) % elems.size(); // Linear probing
		}

		if (elems[index].first == -1)
			++count;

		elems[index] = std::make_pair(key, value);
	}

	int get(int key) {
		int index = key % elems.size();
		while (elems[index].first != -1 && elems[index].first != key)
			index = (index + 1) % elems.size();

		return (elems[index].first == -1 ? -1 : elems[index].second);
	}

private:
	std::vector<std::pair<int, int>> elems;
	size_t count;

	void resize(size_t newSize) {
		std::vector<std::pair<int, int>> oldElems = std::move(elems);
		count = 0;
		elems.resize(newSize, std::make_pair(-1, -1));

		for (const auto& kv : oldElems) {
			if (kv.first != -1) {
				put(kv.first, kv.second);
			}
		}
	}
};