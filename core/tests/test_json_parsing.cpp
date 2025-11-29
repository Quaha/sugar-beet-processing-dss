#include <gtest/gtest.h>
#include "json_schemas.hpp"

namespace {

    bool is_error(const std::variant<SimulationParams, ParsingError>& v)
    {
        return std::holds_alternative<ParsingError>(v);
    }

    std::string get_error(const std::variant<SimulationParams, ParsingError>& v)
    {
        return std::get<ParsingError>(v).message;
    }

    TEST(SimulationParamsParsing, ValidInputNoMaturation)
    {
        std::string js = R"({
        "t": 50,
        "n": 15,
        "alpha_min": 0.12,
        "alpha_max": 0.22,
        "beta_1": 0.86,
        "beta_2": 0.99,
        "concentrated": true,
        "maturation": false,
        "inorganic": false
    })";

        auto res = SimulationParams::from_json(js);
        ASSERT_FALSE(is_error(res));

        const auto& p = std::get<SimulationParams>(res);
        EXPECT_EQ(p.getT(), 50);
        EXPECT_EQ(p.getN(), 15);
        EXPECT_DOUBLE_EQ(p.getAlphaMin(), 0.12);
        EXPECT_DOUBLE_EQ(p.getAlphaMax(), 0.22);
        EXPECT_DOUBLE_EQ(p.getBeta1(), 0.86);
        EXPECT_DOUBLE_EQ(p.getBeta2(), 0.99);
        EXPECT_TRUE(p.isConcentrated());
        EXPECT_FALSE(p.hasMaturation());
        EXPECT_FALSE(p.isInorganic());
        EXPECT_FALSE(p.getMaturationParams().has_value());
    }

    TEST(SimulationParamsParsing, ValidInputWithMaturation)
    {
        std::string js = R"({
        "t": 50,
        "n": 10,
        "alpha_min": 0.12,
        "alpha_max": 0.20,
        "beta_1": 0.86,
        "beta_2": 0.90,
        "concentrated": false,
        "maturation": true,
        "inorganic": true,
        "v": 5,
        "beta_max": 1.05
    })";

        auto res = SimulationParams::from_json(js);
        ASSERT_FALSE(is_error(res));

        const auto& p = std::get<SimulationParams>(res);
        ASSERT_TRUE(p.getMaturationParams().has_value());
        EXPECT_EQ(p.getMaturationParams()->getV(), 5);
        EXPECT_DOUBLE_EQ(p.getMaturationParams()->getBetaMax(), 1.05);
    }

    TEST(SimulationParamsParsing, MissingRequiredField)
    {
        std::string js = R"({
        "n": 15,
        "alpha_min": 0.12,
        "alpha_max": 0.20,
        "beta_1": 0.86,
        "beta_2": 0.90,
        "concentrated": true,
        "maturation": false,
        "inorganic": true
    })";

        auto res = SimulationParams::from_json(js);
        ASSERT_TRUE(is_error(res));

        EXPECT_NE(get_error(res).find("REQUIRED"), std::string::npos);
        EXPECT_NE(get_error(res).find("t"), std::string::npos);
    }

    TEST(SimulationParamsParsing, TypeMismatch)
    {
        std::string js = R"({
        "t": "abc",
        "n": 10,
        "alpha_min": 0.12,
        "alpha_max": 0.20,
        "beta_1": 0.86,
        "beta_2": 0.90,
        "concentrated": false,
        "maturation": false,
        "inorganic": false
    })";

        auto res = SimulationParams::from_json(js);
        ASSERT_TRUE(is_error(res));
        EXPECT_NE(get_error(res).find("TYPE_MISMATCH"), std::string::npos);
    }

    TEST(SimulationParamsParsing, AlphaMinOutOfRange)
    {
        std::string js = R"({
        "t": 50,
        "n": 15,
        "alpha_min": 0.1,
        "alpha_max": 0.15,
        "beta_1": 0.86,
        "beta_2": 0.99,
        "concentrated": true,
        "maturation": false,
        "inorganic": false
    })";

        auto res = SimulationParams::from_json(js);
        ASSERT_TRUE(is_error(res));
        EXPECT_NE(get_error(res).find("INTERVAL"), std::string::npos);
        EXPECT_NE(get_error(res).find("alpha_min"), std::string::npos);
    }

    TEST(SimulationParamsParsing, AlphaMaxOutOfRange)
    {
        std::string js = R"({
        "t": 50,
        "n": 15,
        "alpha_min": 0.15,
        "alpha_max": 0.5,
        "beta_1": 0.86,
        "beta_2": 0.99,
        "concentrated": true,
        "maturation": false,
        "inorganic": false
    })";

        auto res = SimulationParams::from_json(js);
        ASSERT_TRUE(is_error(res));
        EXPECT_NE(get_error(res).find("INTERVAL"), std::string::npos);
        EXPECT_NE(get_error(res).find("alpha_max"), std::string::npos);
    }

    TEST(SimulationParamsParsing, BetaIntervalError)
    {
        std::string js = R"({
        "t": 50,
        "n": 15,
        "alpha_min": 0.12,
        "alpha_max": 0.15,
        "beta_1": 0.80,
        "beta_2": 0.90,
        "concentrated": true,
        "maturation": false,
        "inorganic": true
    })";

        auto res = SimulationParams::from_json(js);
        ASSERT_TRUE(is_error(res));
        EXPECT_NE(get_error(res).find("INTERVAL"), std::string::npos);
        EXPECT_NE(get_error(res).find("beta_1"), std::string::npos);
    }

    TEST(SimulationParamsParsing, Beta1GreaterThanBeta2)
    {
        std::string js = R"({
        "t": 50,
        "n": 15,
        "alpha_min": 0.12,
        "alpha_max": 0.15,
        "beta_1": 0.95,
        "beta_2": 0.90,
        "concentrated": true,
        "maturation": false,
        "inorganic": true
    })";

        auto res = SimulationParams::from_json(js);
        ASSERT_TRUE(is_error(res));
        EXPECT_NE(get_error(res).find("INTERVAL"), std::string::npos);
        EXPECT_NE(get_error(res).find("beta_1 must be <="), std::string::npos);
    }

    TEST(SimulationParamsParsing, MissingMaturationParamsWhenRequired)
    {
        std::string js = R"({
        "t": 50,
        "n": 10,
        "alpha_min": 0.12,
        "alpha_max": 0.15,
        "beta_1": 0.86,
        "beta_2": 0.90,
        "concentrated": false,
        "maturation": true,
        "inorganic": false
    })";

        auto res = SimulationParams::from_json(js);
        ASSERT_TRUE(is_error(res));
        EXPECT_NE(get_error(res).find("REQUIRED"), std::string::npos);
        EXPECT_NE(get_error(res).find("v"), std::string::npos);
    }

    TEST(SimulationParamsParsing, MaturationVOutOfRange)
    {
        std::string js = R"({
        "t": 50,
        "n": 10,
        "alpha_min": 0.12,
        "alpha_max": 0.15,
        "beta_1": 0.86,
        "beta_2": 0.90,
        "concentrated": false,
        "maturation": true,
        "inorganic": false,
        "v": 20,
        "beta_max": 1.1
    })";

        auto res = SimulationParams::from_json(js);
        ASSERT_TRUE(is_error(res));
        EXPECT_NE(get_error(res).find("INTERVAL"), std::string::npos);
        EXPECT_NE(get_error(res).find("v must be in [1; n]"), std::string::npos);
    }

    TEST(SimulationParamsParsing, MaturationBetaMaxOutOfRange)
    {
        std::string js = R"({
        "t": 50,
        "n": 10,
        "alpha_min": 0.12,
        "alpha_max": 0.15,
        "beta_1": 0.86,
        "beta_2": 0.90,
        "concentrated": false,
        "maturation": true,
        "inorganic": false,
        "v": 5,
        "beta_max": 2.0
    })";

        auto res = SimulationParams::from_json(js);
        ASSERT_TRUE(is_error(res));
        EXPECT_NE(get_error(res).find("INTERVAL"), std::string::npos);
        EXPECT_NE(get_error(res).find("beta_max must be in"), std::string::npos);
    }

    TEST(SimulationParamsParsing, BrokenJson)
    {
        std::string js = R"( { invalid json )";

        auto res = SimulationParams::from_json(js);
        ASSERT_TRUE(is_error(res));
        EXPECT_NE(get_error(res).find("PARSING"), std::string::npos);
    }

}