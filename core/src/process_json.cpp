#include "process_json.hpp"

#include <iostream>
#include <algorithm>
#include <nlohmann/json.hpp>

#include "json_schemas.hpp"
#include "matrix.hpp"
#include "greedy_strategy.hpp"
#include "thrifty_strategy.hpp"
#include "greedy_thrifty_strategy.hpp"
#include "thrifty_greedy_strategy.hpp"
#include "median_strategy.hpp"
#include "optimal_strategy.hpp"

using json = nlohmann::json;

static std::string json_result;

DLL_API const char* ProcessJSON(const char* json_input) {

    auto parsing_result = SimulationParams::from_json(json_input);
    if (std::holds_alternative<ParsingError>(parsing_result))
    {
        return std::get<ParsingError>(parsing_result).message.c_str();
    }
    auto params = std::get<SimulationParams>(parsing_result);

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
    std::vector<std::vector<double>> avg_step_ratio(S, std::vector<double>(params.getN(), 0.0));

    // avg_loss[s] Ч средн€€ потер€ относительно optimal
    std::vector<double> avg_loss(S, 0.0);

    Matrix m(params.getN());

    for (int test_case = 0; test_case < params.getT(); ++test_case) {

        if (params.hasMaturation()) {
            m.fillMatrix(params.getAlphaMin(), params.getAlphaMax(), params.getBeta1(), params.getBeta2(),
                params.isConcentrated(), params.hasMaturation(), params.isInorganic(), 
                params.getMaturationParams().value().getV(), params.getMaturationParams().value().getBetaMax());
        } else {
            m.fillMatrix(params.getAlphaMin(), params.getAlphaMax(), params.getBeta1(), params.getBeta2(), 
                params.isConcentrated(), params.hasMaturation(), params.isInorganic(), 1, 1.0);
        }

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

            for (int i = 0; i < params.getN(); ++i) {
                double val = m(seq[i], i);
                avg_step_ratio[s][i] += val;
            }

            double score = m.getStrategyScore(seq);
            avg_loss[s] += (optimal_score - score) / optimal_score;
        }
    }

    for (int s = 0; s < S; ++s) {
        for (int i = 0; i < params.getN(); ++i) {
            avg_step_ratio[s][i] /= params.getT();
        }
        avg_loss[s] /= params.getT();
    }

    double sum_optimal = 0.0;

    for (int i = 0; i < params.getN(); i++) {
        sum_optimal += avg_step_ratio[S - 1][i];
    }

    for (int s = 0; s < S; ++s) {
        for (int i = 0; i < params.getN(); ++i) {
            avg_step_ratio[s][i] /= sum_optimal;
        }
    }

    json_result = Solution::to_json(names, avg_step_ratio, avg_loss);

    return json_result.c_str();
}