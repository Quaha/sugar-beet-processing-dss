#include "thrifty_greedy_strategy.hpp"

#include <vector>

#include "matrix.hpp"

std::vector<int> ThriftyGreedyStrategy(const Matrix& matrix) {
	int n = matrix.size();
	std::vector<int> sequence(n, 0);

	int m = std::max(0, std::min(matrix.getV(), n));

	std::vector<bool> used(n, false);
	for (int i = 0; i < m; i++) {
		int best_id = -1;
		double best_value;

		for (int j = 0; j < n; j++) {
			if (used[j]) continue;
			if (best_id == -1 || matrix(j, i) < best_value) {
				best_value = matrix(j, i);
				best_id = j;
			}
		}

		used[best_id] = true;
		sequence[i] = best_id;
	}

	for (int i = m; i < n; i++) {
		int best_id = -1;
		double best_value;

		for (int j = 0; j < n; j++) {
			if (used[j]) continue;
			if (best_id == -1 || matrix(j, i) > best_value) {
				best_value = matrix(j, i);
				best_id = j;
			}
		}

		used[best_id] = true;
		sequence[i] = best_id;
	}

	return sequence;
}

