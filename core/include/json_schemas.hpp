#pragma once

#include <string>
#include <optional>
#include <vector>
#include <variant>

struct ParsingError
{
    std::string message;
};

class SimulationParams final
{
public:
    class MaturationParams final
    {
    private:
        int v;
        double beta_max;

    public:
        MaturationParams(int v_, double beta_max_) : v(v_), beta_max(beta_max_) { }

        int getV() const { return v; }
        double getBetaMax() const { return beta_max; }
    };

    int getT() const { return t; }
    int getN() const { return n; }
    double getAlphaMin() const { return alpha_min; }
    double getAlphaMax() const { return alpha_max; }
    double getBeta1() const { return beta_1; }
    double getBeta2() const { return beta_2; }
    bool isConcentrated() const { return concentrated; }
    bool hasMaturation() const { return maturation; }
    bool isInorganic() const { return inorganic; }
    std::optional<MaturationParams> getMaturationParams() const { return maturation_params; }

    static std::variant<SimulationParams, ParsingError> from_json(const std::string& json_str);

private:
    int t;
    int n;
    double alpha_min;
    double alpha_max;
    double beta_1;
    double beta_2;
    bool concentrated;
    bool maturation;
    bool inorganic;
    std::optional<MaturationParams> maturation_params;

    SimulationParams(
        int t_, int n_, double alpha_min_, double alpha_max_,
        double beta_1_, double beta_2_, bool concentrated_, bool maturation_,
        bool inorganic_, const std::optional<MaturationParams>& maturation_params_)
        : t(t_), n(n_), alpha_min(alpha_min_), alpha_max(alpha_max_),
        beta_1(beta_1_), beta_2(beta_2_), concentrated(concentrated_),
        maturation(maturation_), inorganic(inorganic_), maturation_params(maturation_params_)
    {}
};

class Solution
{
public:
    static std::string to_json(
        const std::vector<std::string>& names,
        const std::vector<std::vector<double>>& avg_step_ratio,
        const std::vector<double>& avg_loss);
};