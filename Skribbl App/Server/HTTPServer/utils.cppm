export module utils;
import <unordered_map>;
import <string>;
import <vector>;

// See https://stackoverflow.com/a/57346888/12388382
export std::vector<std::string> split(const std::string& str, const std::string& delim);


export std::unordered_map<std::string, std::string> parseUrlArgs(const std::string& urlArgs);
