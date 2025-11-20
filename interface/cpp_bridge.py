import ctypes
from ctypes import c_char_p

import json
from pathlib import Path

DLL_PATH = Path(__file__).parent / "server_library.dll"
_lib = ctypes.CDLL(str(DLL_PATH))

_lib.ProcessJSON.argtypes = [c_char_p]
_lib.ProcessJSON.restype = c_char_p

def process_json(input_data: dict) -> dict:
    """
    Sends data to the C++ DLL, receives the processed JSON back.

    :param input_data: Python dictionary to send to C++
    :return: Python dictionary with processed data
    """
    
    input_str = json.dumps(input_data)
    result_ptr = _lib.ProcessJSON(input_str.encode('utf-8'))
    return json.loads(result_ptr.decode('utf-8'))
