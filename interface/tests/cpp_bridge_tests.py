import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent.parent))
from cpp_bridge import process_json

def test_valid_input_no_maturation():
    data = {
        "t": 10,
        "n": 5,
        "alpha_min": 0.12,
        "alpha_max": 0.2,
        "beta_1": 0.86,
        "beta_2": 0.99,
        "concentrated": True,
        "maturation": False,
        "inorganic": False
    }
    result = process_json(data)
    strategies = ["greedy","thrifty","greedy_thrifty","thrifty_greedy","median","optimal"]
    for s in strategies:
        assert s in result
        assert "avg_step_ratio" in result[s]
        assert "avg_loss" in result[s]
        assert len(result[s]["avg_step_ratio"]) == data["n"]
        assert isinstance(result[s]["avg_loss"], float)

def test_valid_input_with_maturation():
    data = {
        "t": 10,
        "n": 5,
        "alpha_min": 0.12,
        "alpha_max": 0.2,
        "beta_1": 0.86,
        "beta_2": 0.99,
        "concentrated": True,
        "maturation": True,
        "inorganic": False,
        "v": 3,
        "beta_max": 1.05
    }
    result = process_json(data)
    for s in result:
        assert "avg_step_ratio" in result[s]
        assert "avg_loss" in result[s]

def test_missing_required_field():
    data = {
        # "t" missing
        "n": 5,
        "alpha_min": 0.12,
        "alpha_max": 0.2,
        "beta_1": 0.86,
        "beta_2": 0.99,
        "concentrated": True,
        "maturation": False,
        "inorganic": False
    }
    result = process_json(data)
    assert "error_type" in result
    assert "t" in result["message"]

def test_type_mismatch():
    data = {
        "t": "not_an_int",
        "n": 5,
        "alpha_min": 0.12,
        "alpha_max": 0.2,
        "beta_1": 0.86,
        "beta_2": 0.99,
        "concentrated": True,
        "maturation": False,
        "inorganic": False
    }
    result = process_json(data)
    assert "TYPE_MISMATCH" in result.get("error_type", "")

def test_alpha_out_of_range():
    data = {
        "t": 10,
        "n": 5,
        "alpha_min": 0.1,  # too low
        "alpha_max": 0.25, # too high
        "beta_1": 0.86,
        "beta_2": 0.99,
        "concentrated": True,
        "maturation": False,
        "inorganic": False
    }
    result = process_json(data)
    assert "alpha_min" in result["message"] or "alpha_max" in result["message"]

def test_maturation_params_out_of_range():
    data = {
        "t": 10,
        "n": 5,
        "alpha_min": 0.12,
        "alpha_max": 0.2,
        "beta_1": 0.86,
        "beta_2": 0.99,
        "concentrated": True,
        "maturation": True,
        "inorganic": False,
        "v": 6,       # > n
        "beta_max": 2 # > 1.15
    }
    result = process_json(data)
    assert "v must be in" in result["message"] or "beta_max must be" in result["message"]
