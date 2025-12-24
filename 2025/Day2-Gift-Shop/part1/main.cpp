#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

std::vector<long long> generate_invalid_from_range(long long low,
                                                   long long high) {
  std::vector<long long> result{};
  long long k{1};

  while (true) {
    long long smallest_x = std::pow(10, k - 1);
    std::string s = std::to_string(smallest_x);
    long long smallest_invalid = std::stoll(s + s);

    if (smallest_invalid > high)
      break;
    for (long long i = std::pow(10, k - 1); i < std::pow(10, k); ++i) {
      std::string half_string = std::to_string(i);
      long long n = std::stoll(half_string + half_string);
      if (n > high)
        break;
      if (n >= low)
        result.push_back(n);
    }
    k++;
  }

  return result;
}

std::vector<std::pair<long long, long long>>
read_ranges_from_file(const std::string &path) {
  std::ifstream in(path);
  if (!in) {
    throw std::runtime_error("Could not open file: " + path);
  }
  std::string all, line;
  while (std::getline(in, line)) {
    if (!all.empty())
      all.push_back(',');
    all += line;
  }

  std::vector<std::pair<long long, long long>> ranges;
  std::stringstream ss(all);
  std::string token;

  while (std::getline(ss, token, ',')) {
    if (token.empty())
      continue;

    // token is like "9100-11052"
    std::size_t dash = token.find('-');
    if (dash == std::string::npos) {
      throw std::runtime_error("Bad token (missing '-'): " + token);
    }

    long long low = std::stoll(token.substr(0, dash));
    long long high = std::stoll(token.substr(dash + 1));

    ranges.emplace_back(low, high);
  }

  return ranges;
}

int main() {
  const std::string path = "input.txt";
  std::vector<long long> invalid_numbers;
  try {
    auto ranges = read_ranges_from_file(path);
    for (const auto &range : ranges) {
      long long low = range.first;
      long long high = range.second;
      auto invalid_numbers_from_range = generate_invalid_from_range(low, high);
      invalid_numbers.insert(invalid_numbers.end(),
                             invalid_numbers_from_range.begin(),
                             invalid_numbers_from_range.end());
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  long long sum =
      std::accumulate(invalid_numbers.begin(), invalid_numbers.end(), 0LL);
  std::cout << sum << std::endl;
  return 0;
}
