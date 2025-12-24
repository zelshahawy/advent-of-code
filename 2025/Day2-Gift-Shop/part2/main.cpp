#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

static long long pow10_int(int e) {
  long long p = 1;
  while (e-- > 0)
    p *= 10;
  return p;
}

std::vector<long long> generate_invalid_from_range(long long low,
                                                   long long high) {
  if (low > high)
    std::swap(low, high);

  std::unordered_set<long long> seen;
  long long k = 1;

  while (true) {
    long long start = pow10_int((int)k - 1);
    long long end = pow10_int((int)k);

    std::string s = std::to_string(start);

    bool any_for_this_k = false;

    for (int r = 2;; r++) {
      std::string smallest_rep;
      smallest_rep.reserve(s.size() * (size_t)r);
      for (int t = 0; t < r; t++)
        smallest_rep += s;

      long long smallest_invalid;
      try {
        smallest_invalid = std::stoll(smallest_rep);
      } catch (...) {
        break;
      }

      if (smallest_invalid > high)
        break;

      any_for_this_k = true;

      for (long long i = start; i < end; ++i) {
        std::string half = std::to_string(i);

        std::string rep;
        for (int t = 0; t < r; t++)
          rep += half;

        long long n;
        try {
          n = std::stoll(rep);
        } catch (...) {
          break;
        }

        if (n > high)
          break;
        if (n >= low)
          seen.insert(n);
      }
    }

    if (!any_for_this_k)
      break;
    k++;
  }

  return std::vector<long long>(seen.begin(), seen.end());
}

std::vector<std::pair<long long, long long>>
read_ranges_from_file(const std::string &path) {
  std::ifstream in(path);
  if (!in)
    throw std::runtime_error("Could not open file: " + path);

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
    std::size_t dash = token.find('-');
    if (dash == std::string::npos)
      throw std::runtime_error("Bad token (missing '-'): " + token);

    long long low = std::stoll(token.substr(0, dash));
    long long high = std::stoll(token.substr(dash + 1));
    ranges.emplace_back(low, high);
  }

  return ranges;
}

int main() {
  const std::string path = "input.txt";
  std::unordered_set<long long> invalid_numbers;

  try {
    auto ranges = read_ranges_from_file(path);
    for (const auto &range : ranges) {
      auto nums = generate_invalid_from_range(range.first, range.second);
      for (long long v : nums)
        invalid_numbers.insert(v);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  long long sum = 0;
  for (long long v : invalid_numbers)
    sum += v;
  std::cout << sum << "\n";
  return 0;
}

