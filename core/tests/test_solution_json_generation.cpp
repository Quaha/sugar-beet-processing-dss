#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "json_schemas.hpp"

using json = nlohmann::json;

namespace {

    void check_json_structure(const json& j, int n_steps)
    {
        std::vector<std::string> strategies = {
            "greedy","thrifty","greedy_thrifty","thrifty_greedy","median","optimal"
        };

        for (auto& s : strategies)
        {
            ASSERT_TRUE(j.contains(s));
            ASSERT_TRUE(j[s].contains("progress"));
            ASSERT_TRUE(j[s].contains("avg_loss"));

            ASSERT_EQ(j[s]["progress"].size(), n_steps);
            ASSERT_TRUE(j[s]["avg_loss"].is_number());
        }
    }

    TEST(SolutionJsonGeneration, CorrectStructure)
    {
        std::vector<std::string> names = { "greedy","thrifty","greedy_thrifty","thrifty_greedy","median","optimal" };
        std::vector<std::vector<double>> avg_step_ratio(6, std::vector<double>(5, 0.5));
        std::vector<double> avg_loss(6, 0.1);

        std::string json_str = Solution::to_json(names, avg_step_ratio, avg_loss);
        json j = json::parse(json_str);

        check_json_structure(j, 5);
    }

    TEST(SolutionJsonGeneration, CorrectValues)
    {
        std::vector<std::string> names = { "greedy","thrifty" };
        std::vector<std::vector<double>> avg_step_ratio = { {0.1,0.2},{0.3,0.4} };
        std::vector<double> avg_loss = { 0.05, 0.07 };

        std::string json_str = Solution::to_json(names, avg_step_ratio, avg_loss);
        json j = json::parse(json_str);

        EXPECT_EQ(j["greedy"]["progress"][0], 0.1);
        EXPECT_EQ(j["greedy"]["progress"][1], 0.2);
        EXPECT_DOUBLE_EQ(j["greedy"]["avg_loss"], 0.05);

        EXPECT_EQ(j["thrifty"]["progress"][0], 0.3);
        EXPECT_EQ(j["thrifty"]["progress"][1], 0.4);
        EXPECT_DOUBLE_EQ(j["thrifty"]["avg_loss"], 0.07);
    }

    TEST(SolutionJsonGeneration, EmptyVectors)
    {
        std::vector<std::string> names = { "greedy" };
        std::vector<std::vector<double>> avg_step_ratio(1);
        std::vector<double> avg_loss = { 0.0 };

        std::string json_str = Solution::to_json(names, avg_step_ratio, avg_loss);
        json j = json::parse(json_str);

        ASSERT_TRUE(j.contains("greedy"));
        ASSERT_TRUE(j["greedy"]["progress"].is_array());
        ASSERT_EQ(j["greedy"]["progress"].size(), 0);
        EXPECT_DOUBLE_EQ(j["greedy"]["avg_loss"], 0.0);
    }

    TEST(SolutionJsonGeneration, LargeVectors)
    {
        int N = 1000;
        std::vector<std::string> names = { "optimal" };
        std::vector<std::vector<double>> avg_step_ratio(1, std::vector<double>(N, 1.0));
        std::vector<double> avg_loss = { 0.0 };

        std::string json_str = Solution::to_json(names, avg_step_ratio, avg_loss);
        json j = json::parse(json_str);

        ASSERT_EQ(j["optimal"]["progress"].size(), N);
        for (auto val : j["optimal"]["progress"])
        {
            EXPECT_DOUBLE_EQ(val, 1.0);
        }
        EXPECT_DOUBLE_EQ(j["optimal"]["avg_loss"], 0.0);
    }

}