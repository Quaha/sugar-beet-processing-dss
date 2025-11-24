#include "process_json.hpp"

#include <iostream>
#include <algorithm>

#include "matrix.hpp"
#include "greedy_strategy.hpp"
#include "thrifty_strategy.hpp"
#include "greedy_thrifty_strategy.hpp"
#include "thrifty_greedy_strategy.hpp"
#include "median_strategy.hpp"
#include "optimal_strategy.hpp"

DLL_API const char* ProcessJSON(const char* json_input) {

    int T = 50;
    int n = 15;

    double alpha_min = 0.12;
    double alpha_max = 0.22;

    double beta_1 = 0.86;
    double beta_2 = 0.99;

    bool concentrated = true;
    bool maturation = true;
    bool inorganic = true;

    int v = n / 2;
    double beta_max = 1.1;

    // CODE WITH JSON PROCESSING WOULD BE HERE (INPUT)

    std::vector<std::string> names = {
        "greedy",
        "thrifty",
        "greedy_thrifty",
        "thrifty_greedy",
        "median",
        "optimal"
    };

    int S = names.size();

    // avg_step_ratio[s][i] Ч средний % выбранного значени€ от максимума на шаге i
    std::vector<std::vector<double>> avg_step_ratio(S, std::vector<double>(n, 0.0));

    // avg_loss[s] Ч средн€€ потер€ относительно optimal
    std::vector<double> avg_loss(S, 0.0);

    Matrix m(n);

    for (int test_case = 0; test_case < T; ++test_case) {

        m.fillMatrix(alpha_min, alpha_max, beta_1, beta_2, concentrated, maturation, inorganic, v, beta_max);

        std::vector<std::vector<int>> seqs;

        seqs.push_back(GreedyStrategy(m));
        seqs.push_back(ThriftyStrategy(m));
        seqs.push_back(GreedyThriftyStrategy(m));
        seqs.push_back(ThriftyGreedyStrategy(m));
        seqs.push_back(MedianStrategy(m));
        seqs.push_back(OptimalStrategy(m));

        double optimal_score = m.getStrategyScore(seqs.back());

        for (int s = 0; s < S; ++s) {
            const auto& seq = seqs[s];

            for (int i = 0; i < n; ++i) {
                double val = m(seq[i], i);
                avg_step_ratio[s][i] += val;
            }

            double score = m.getStrategyScore(seq);
            avg_loss[s] += (optimal_score - score);
        }
    }

    for (int s = 0; s < S; ++s) {
        for (int i = 0; i < n; ++i) {
            avg_step_ratio[s][i] /= T;
        }
        avg_loss[s] /= T;
    }

    // CODE WITH JSON PROCESSING WOULD BE HERE (OUTPUT)

    return json_input;
}