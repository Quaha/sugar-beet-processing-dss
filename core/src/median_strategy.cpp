#include "median_strategy.hpp"

#include <algorithm>
#include <vector>
#include <utility>

#include "matrix.hpp"

std::vector<int> MedianStrategy(const Matrix& matrix) {
	int n = matrix.size();
	std::vector<int> sequence(n, 0);

	std::vector<bool> used(n, false);
	for (int i = 0; i < n; i++) {
		std::vector<std::pair<double, int>> unused_data;
		unused_data.reserve(n - i);

		for (int j = 0; j < n; j++) {
			if (used[j]) continue;
			unused_data.push_back(std::make_pair(matrix(j, i), j));
		}

		int m = (n - i) / 2;
		std::nth_element(unused_data.begin(), unused_data.begin() + m, unused_data.end());

		auto [best_value, best_id] = unused_data[m];

		used[best_id] = true;
		sequence[i] = best_id;
	}

	return sequence;
}

