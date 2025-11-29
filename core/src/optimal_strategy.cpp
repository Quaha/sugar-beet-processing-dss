#include "optimal_strategy.hpp"

#include <vector>
#include <numeric>

#include "matrix.hpp"

std::vector<int> OptimalStrategy(const Matrix& matrix) {
    int n = matrix.size();
    int m = matrix.size();
    std::vector<int> sequence(n, 0);

    double maxValue = -std::numeric_limits<double>::infinity();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; j++) {
            maxValue = std::max(maxValue, matrix(i, j));
        }
    }

    std::vector<double> u(n + 1), v(m + 1);
    std::vector<int> p(m + 1), way(m + 1);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        std::vector<double> minv(m + 1, std::numeric_limits<double>::infinity());
        std::vector<bool> used(m + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], j1;
            double delta = std::numeric_limits<double>::infinity();
            for (int j = 1; j <= m; ++j) {
                if (!used[j]) {
                    double cur = (maxValue - matrix(i0 - 1, j - 1)) - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur, way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j], j1 = j;
                    }
                }
            }
            for (int j = 0; j <= m; ++j) {
                if (used[j]) {
                    u[p[j]] += delta, v[j] -= delta;
                }
                else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    std::copy(p.begin() + 1, p.end(), sequence.begin());
    for (auto& v : sequence) {
        v--;
    }

    return sequence;
}

