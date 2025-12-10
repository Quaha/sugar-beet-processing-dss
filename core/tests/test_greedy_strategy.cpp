#include <gtest/gtest.h>

#include "greedy_strategy.hpp"
#include "optimal_strategy.hpp"

#include <vector>

#include "matrix.hpp"
#include "json_schemas.hpp"

TEST(GreedyStrategy, CanUseStrategy) {
    TestableMatrix tm(5);
    Matrix m = tm;

    EXPECT_NO_THROW(GreedyStrategy(m));
}

TEST(GreedyStrategy, StrategyCorrectnessM0x0) {
    TestableMatrix tm(0);
    Matrix m = tm;

    std::vector<int> expected;

    EXPECT_EQ(GreedyStrategy(m), expected);
}

TEST(GreedyStrategy, StrategyCorrectnessM1x1) {
    TestableMatrix tm(1);
    tm(0, 0) = 1.0;
    Matrix m = tm;

    std::vector<int> expected = { 0 };

    EXPECT_EQ(GreedyStrategy(m), expected);
}

TEST(GreedyStrategy, StrategyCorrectnessM2x2) {
    TestableMatrix tm(2);
    tm(0, 0) = 4.0; tm(0, 1) = 8.0;
    tm(1, 0) = 2.0; tm(1, 1) = 1.0;
    Matrix m = tm;

    std::vector<int> expected = { 0, 1};

    EXPECT_EQ(GreedyStrategy(m), expected );
}

TEST(GreedyStrategy, StrategyCorrectnessM3x3) {
    TestableMatrix tm(3);
    tm(0, 0) = 1.0; tm(0, 1) = 2.0; tm(0, 2) = 4.0;
    tm(1, 0) = 2.0; tm(1, 1) = 3.0; tm(1, 2) = 4.0;
    tm(2, 0) = 1.0; tm(2, 1) = 1.0; tm(2, 2) = 3.0;
    Matrix m = tm;

    std::vector<int> expected = { 1, 0, 2 };

    EXPECT_EQ(GreedyStrategy(m), expected);
}

TEST(GreedyStrategy, StrategyCorrectnessM4x4) {
    TestableMatrix tm(4);
    tm(0, 0) = 1.0; tm(0, 1) = 2.0; tm(0, 2) = 9.0; tm(0, 3) = 1.0;
    tm(1, 0) = 2.0; tm(1, 1) = 1.0; tm(1, 2) = 4.0; tm(1, 3) = 3.0;
    tm(2, 0) = 6.0; tm(2, 1) = 7.0; tm(2, 2) = 2.0; tm(2, 3) = 9.0;
    tm(3, 0) = 3.0; tm(3, 1) = 1.5; tm(3, 2) = 3.0; tm(3, 3) = 4.0;
    Matrix m = tm;

    std::vector<int> expected = { 2, 0, 1, 3 };

    EXPECT_EQ(GreedyStrategy(m), expected);
}

//TEST(GreedyStrategy, StrategyAvgLossSum100) {
//
//    SimulationParams params(
//        1, 1, 0.12, 0.22,
//        0.86, 0.89, false, false, false, std::nullopt);
//
//    std::vector<std::string> names = {
//        "greedy",
//        "optimal"
//    };
//
//    int S = names.size();
//
//    // avg_step_ratio[s][i] Ч средний % выбранного значени€ от максимума на шаге i
//    std::vector<std::vector<double>> avg_step_ratio(S, std::vector<double>(params.getN(), 0.0));
//
//    // avg_loss[s] Ч средн€€ потер€ относительно optimal
//    std::vector<double> avg_loss(S, 0.0);
//
//    Matrix m(params.getN());
//
//    for (int test_case = 0; test_case < params.getT(); ++test_case) {
//
//        if (params.hasMaturation()) {
//            m.fillMatrix(params.getAlphaMin(), params.getAlphaMax(), params.getBeta1(), params.getBeta2(),
//                params.isConcentrated(), params.hasMaturation(), params.isInorganic(),
//                params.getMaturationParams().value().getV(), params.getMaturationParams().value().getBetaMax());
//        }
//        else {
//            m.fillMatrix(params.getAlphaMin(), params.getAlphaMax(), params.getBeta1(), params.getBeta2(),
//                params.isConcentrated(), params.hasMaturation(), params.isInorganic(), 1, 1.0);
//        }
//
//        std::vector<std::vector<int>> seqs;
//
//        seqs.push_back(GreedyStrategy(m));
//        seqs.push_back(OptimalStrategy(m));
//
//        double optimal_score = m.getStrategyScore(seqs.back());
//
//        for (int s = 0; s < S; ++s) {
//            const auto& seq = seqs[s];
//
//            for (int i = 0; i < params.getN(); ++i) {
//                double val = m(seq[i], i);
//                avg_step_ratio[s][i] += val;
//            }
//
//            double score = m.getStrategyScore(seq);
//            avg_loss[s] += (optimal_score - score) / optimal_score;
//        }
//    }
//
//    for (int s = 0; s < S; ++s) {
//        for (int i = 0; i < params.getN(); ++i) {
//            avg_step_ratio[s][i] /= params.getT();
//        }
//        avg_loss[s] /= params.getT();
//    }
//
//    double sum_optimal = 0.0;
//
//    for (int i = 0; i < params.getN(); i++) {
//        sum_optimal += avg_step_ratio[S - 1][i];
//    }
//
//    for (int s = 0; s < S; ++s) {
//        for (int i = 0; i < params.getN(); ++i) {
//            avg_step_ratio[s][i] /= sum_optimal;
//        }
//    }
//
//    double sum = 0.0;
//    for (int i = 0; i < params.getN(); i++) {
//        sum += avg_step_ratio[0][i];
//    }
//
//    EXPECT_LE(sum, 1.0);
//}