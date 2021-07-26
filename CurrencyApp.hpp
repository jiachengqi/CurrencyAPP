#include <chrono>
#include <ctime>
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <unordered_map>

using namespace std;
using json = nlohmann::json;


void GetUserInput(const string &, const string &, float, unordered_map<string, float>, time_t);

json GetRequest(const string &);

time_t GetTime(json);

unordered_map<string, float> GetRatio(json json);
