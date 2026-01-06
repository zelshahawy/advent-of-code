#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

static constexpr int EMPTY = 0;
static constexpr int SPLITTER = 1;
static constexpr int START = 2;

std::tuple<std::vector<std::vector<int>>, int, int>
parse_grid_and_find_s(std::string file_name) {
  std::ifstream in(file_name);
  if (!in)
    throw std::runtime_error("Failed to open inputs.txt" + file_name);

  std::vector<std::vector<int>> grid;
  int sr = -1, sc = -1;

  std::string line;
  int r = 0;

  while (std::getline(in, line)) {
    if (line.empty())
      continue;

    std::vector<int> row;
    row.reserve(line.size());

    for (int c = 0; c < (int)line.size(); ++c) {
      char ch = line[c];
      if (ch == '.')
        row.push_back(EMPTY);
      else if (ch == '^')
        row.push_back(SPLITTER);
      else if (ch == 'S') {
        row.push_back(START);
        if (sr != -1)
          throw std::runtime_error("Multiple 'S' found");
        sr = r;
        sc = c;
      } else {
        throw std::runtime_error(std::string("Unexpected char: ") + ch);
      }
    }

    if (!grid.empty() && row.size() != grid[0].size())
      throw std::runtime_error("Non-rectangular grid");

    grid.push_back(std::move(row));
    ++r;
  }

  if (grid.empty())
    throw std::runtime_error("Empty input");
  if (sr == -1)
    throw std::runtime_error("No 'S' found");

  return {std::move(grid), sr, sc};
}

int find_splittings_sum(std::vector<std::vector<int>> &grid,
                        std::pair<int, int> s) {
  const int H = grid.size();
  const int W = H ? grid[0].size() : 0;

  auto in_bounds = [&](int r, int c) -> bool {
    return 0 <= r && r < H && 0 <= c && c < W;
  };

  auto key = [&](int r, int c) -> long long {
    return (static_cast<long long>(r) << 32) ^ static_cast<unsigned int>(c);
  };

  int sum = 0;
  std::deque<std::pair<int, int>> q{};
  std::unordered_set<long long> visited{};

  if (in_bounds(s.first, s.second))
    q.emplace_back(s.first, s.second);

  while (!q.empty()) {
    auto curr = q.front();
    q.pop_front();

    int r = curr.first, c = curr.second;
    if (!in_bounds(r, c))
      continue;

    long long k = key(r, c);
    if (visited.find(k) != visited.end())
      continue;
    visited.insert(k);

    if (grid[r][c] == SPLITTER) {
      ++sum;
      if (in_bounds(r, c - 1))
        q.emplace_back(r, c - 1);
      if (in_bounds(r, c + 1))
        q.emplace_back(r, c + 1);
    } else {
      if (in_bounds(r + 1, c))
        q.emplace_back(r + 1, c);
    }
  }

  return sum;
}

int main() {
  try {
    auto [grid, sr, sc] = parse_grid_and_find_s("inputs.txt");
    int ans = find_splittings_sum(grid, {sr, sc});
    std::cout << ans << "\n";
    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
