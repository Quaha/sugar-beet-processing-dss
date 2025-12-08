#include "json_schemas.hpp"

#include <variant>
#include <optional>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

static ParsingError make_error(const std::string& type, const std::string& message)
{
    json j;
    j["error_type"] = type;
    j["message"] = message;
    return ParsingError{ j.dump(2) };
}

std::variant<SimulationParams, ParsingError> SimulationParams::from_json(const std::string& json_str)
{
    json j;

    try
    {
        j = json::parse(json_str);
    }
    catch (const json::exception& e)
    {
        return make_error("PARSING", e.what());
    }

    auto require = [&](const char* key) -> std::optional<ParsingError>
        {
            if (!j.contains(key))
                return make_error("REQUIRED", key);
            return std::nullopt;
        };

    const char* required[] = {
        "t","n","alpha_min","alpha_max",
        "beta_1","beta_2",
        "concentrated","maturation","inorganic"
    };

    for (auto* k : required)
    {
        if (auto err = require(k))
            return *err;
    }

    int t, n;
    double alpha_min, alpha_max;
    double beta_1, beta_2;
    bool concentrated, maturation, inorganic;

    try
    {
        t = j.at("t").get<int>();
        n = j.at("n").get<int>();
        alpha_min = j.at("alpha_min").get<double>();
        alpha_max = j.at("alpha_max").get<double>();
        beta_1 = j.at("beta_1").get<double>();
        beta_2 = j.at("beta_2").get<double>();
        concentrated = j.at("concentrated").get<bool>();
        maturation = j.at("maturation").get<bool>();
        inorganic = j.at("inorganic").get<bool>();
    }
    catch (const json::exception& e)
    {
        return make_error("TYPE_MISMATCH", e.what());
    }

    std::optional<MaturationParams> maturation_params;

    if (maturation)
    {
        if (!j.contains("v"))
            return make_error("REQUIRED", "v");
        if (!j.contains("beta_max"))
            return make_error("REQUIRED", "beta_max");

        int v;
        double beta_max;

        try
        {
            v = j.at("v").get<int>();
            beta_max = j.at("beta_max").get<double>();
        }
        catch (const json::exception& e)
        {
            return make_error("TYPE_MISMATCH", e.what());
        }

        maturation_params = MaturationParams(v, beta_max);
    }

    if (t <= 0)
        return make_error("INTERVAL", "t must be a natural number");
    if (n <= 0)
        return make_error("INTERVAL", "n must be a natural number");

    if (alpha_min < 0.12 || alpha_min > 0.22)
        return make_error("INTERVAL", "alpha_min must be in [0.12; 0.22]");
    if (alpha_max < 0.12 || alpha_max > 0.22)
        return make_error("INTERVAL", "alpha_max must be in [0.12; 0.22]");
    if (alpha_min > alpha_max)
        return make_error("INTERVAL", "alpha_min must be <= alpha_max");

    if (beta_1 <= 0.85 || beta_1 >= 1.0)
        return make_error("INTERVAL", "beta_1 must be in (0.85; 1)");
    if (beta_2 <= 0.85 || beta_2 >= 1.0)
        return make_error("INTERVAL", "beta_2 must be in (0.85; 1)");
    if (beta_1 > beta_2)
        return make_error("INTERVAL", "beta_1 must be <= beta_2");

    if (maturation)
    {
        auto& mp = maturation_params.value();

        if (mp.getV() <= 0 || mp.getV() > n)
            return make_error("INTERVAL", "v must be in [1; n]");

        if (mp.getBetaMax() <= 1.0 || mp.getBetaMax() >= 1.15)
            return make_error("INTERVAL", "beta_max must be in (1; 1.15)");
    }

    return SimulationParams{
        t, n,
        alpha_min, alpha_max,
        beta_1, beta_2,
        concentrated,
        maturation,
        inorganic,
        maturation_params
    };
}

std::string Solution::to_json(
    const std::vector<std::string>& names, 
    const std::vector<std::vector<double>>& avg_step_ratio, 
    const std::vector<double>& avg_loss)
{
    json result;

    for (size_t s = 0; s < names.size(); ++s)
    {
        result[names[s]] = {
            // "avg_step_ratio" содержит данные, но для JS его нужно назвать "progress"
            {"progress", avg_step_ratio[s]}, 
            {"avg_loss", avg_loss[s]}
        };
    }

    return result.dump(2);
}