#include <chrono>
#include <ctime>
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <unordered_map>
#include "CurrencyApp.hpp"


using namespace std;
using json = nlohmann::json;


void GetUserInput(const string& choice1, const string& choice2, float amount, unordered_map<string, float> ratio, time_t t) {


    try {
        auto value1 = ratio.at(choice1);
        auto value2 = ratio.at(choice2);


        string result;
        result += "According to the currency rate at:\n";
        result += ctime(&t);
        result += to_string(amount);
        result += " ";
        result += choice1;
        result += " = ";
        result += to_string(value2 / value1 * amount);
        result += " ";
        result += choice2;
//            for the string concatenation, avoid using "+" to have multiple allocations

        cout << result << '\n';

    } catch (out_of_range &) {
        cout << "Given currency is not available.\n";
        cout << "Available currency:\n";
        for (const auto &it : ratio)
            cout << it.first << ' ' << '\n';
    }
}

void Cleanup(CURL *curl, curl_slist *headers) {
    if (curl)
        curl_easy_cleanup(curl);
    if (headers)
        curl_slist_free_all(headers);
    curl_global_cleanup();
}

/*This is our callback function which will be executed by curl on perform.
here we will copy the data received to our struct
ptr : points to the data received by curl.
size : is the count of data items received.
nmemb : number of bytes
data : our pointer to hold the data.
*/
size_t curl_callback(void *ptr, size_t size, size_t nmemb, string *data) {
    data->append((char *) ptr, size * nmemb);
    return size * nmemb;
}


json GetRequest(const string& url) {
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    string response_string;
    struct curl_slist *headers = nullptr;
    if (!curl) {
        cout << "ERROR : Curl initialization\n"
             << endl;
        Cleanup(curl, headers);
        return "";
    }

    headers = curl_slist_append(headers, "User-Agent: libcurl-agent/1.0");
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Cache-Control: no-cache");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,10L);                //maximum time allowed for operation to finish, its in seconds
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);


    CURLcode status = curl_easy_perform(curl);
    if (status != 0) {
        cout << "Error: Request failed on URL : " << url << endl;
        cout << "Error Code: " << status << " Error Detail : " << curl_easy_strerror(status) << endl;
        Cleanup(curl, headers);
        return "";
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    curl_global_cleanup();

    json j = json::parse(response_string);
    return j;
}

time_t GetTime(json json) {
    return json.at("timestamp").get<time_t>();
}


unordered_map<string, float> GetRatio(json json) {
    return json.at("rates").get<unordered_map<string, float>>();
}

void Starting(const string &choice1, const string &choice2, float amount) {
    json j = GetRequest("http://data.fixer.io/api/latest?access_key=c1d257249e2b699e0a1a72963634b42d");
    GetUserInput(choice1, choice2, amount, GetRatio(j), GetTime(j));
}

int main(int argc, char *argv[]) {

    string c1 = argv[1];
    string c2 = argv[2];
    auto f = (float) strtod(argv[3], nullptr);

    Starting(c1, c2, f);
    return 0;
}







