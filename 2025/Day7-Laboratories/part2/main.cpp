#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

static constexpr int EMPTY = 0;
static constexpr int SPLITTER = 1;
static constexpr int START = 2;

std::tuple<std::vector<std::vector<int>>, std::size_t, std::size_t>
parse_grid_and_find_s(const std::string &file_name) {
  std::ifstream in(file_name);
  if (!in)
    throw std::runtime_error("Failed to open file: " + file_name);

  std::vector<std::vector<int>> grid;
  std::size_t sr{0}, sc{0};
  bool found{false};

  std::string line;
  std::size_t r{0};

  while (std::getline(in, line)) {
    if (line.empty())
      continue;

    std::vector<int> row;

    for (std::size_t c{0}; c < line.size(); ++c) {
      char ch = line[c];
      if (ch == '.')
        row.push_back(EMPTY);
      else if (ch == '^')
        row.push_back(SPLITTER);
      else if (ch == 'S') {
        row.push_back(START);
        if (found)
          throw std::runtime_error("Multiple 'S' found");
        found = true;
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
  if (!found)
    throw std::runtime_error("No 'S' found");

  return {std::move(grid), sr, sc};
}

std::uint64_t count_splits_classical(const std::vector<std::vector<int>> &grid,
                                     std::size_t sr, std::size_t sc) {
  const std::size_t H{grid.size()};
  const std::size_t W{H ? grid[0].size() : 0};
  if (H == 0 || W == 0 || sr >= H || sc >= W)
    return 0;

  auto idx = [&](std::size_t r, std::size_t c) -> std::size_t {
    return r * W + c;
  };

  std::vector<unsigned char> visited(H * W, 0);
  std::deque<std::pair<std::size_t, std::size_t>> q;

  q.emplace_back(sr, sc);
  std::uint64_t splits{0};

  while (!q.empty()) {
    auto [r, c] = q.front();
    q.pop_front();

    if (r >= H || c >= W)
      continue;
    std::size_t id = idx(r, c);
    if (visited[id])
      continue;
    visited[id] = 1;

    if (grid[r][c] == SPLITTER) {
      ++splits;
      if (c > 0)
        q.emplace_back(r, c - 1);
      if (c + 1 < W)
        q.emplace_back(r, c + 1);
    } else {
      if (r + 1 < H)
        q.emplace_back(r + 1, c);
    }
  }

  return splits;
}

std::uint64_t count_timelines_quantum(const std::vector<std::vector<int>> &grid,
                                      std::size_t sr, std::size_t sc) {
  const std::size_t H{grid.size()};
  const std::size_t W{H ? grid[0].size() : 0};
  if (H == 0 || W == 0 || sr >= H || sc >= W)
    return 0;

  std::vector<std::uint64_t> curr(W, 0), next(W, 0);
  std::uint64_t total{0};

  curr[sc] = 1;

  for (std::size_t r = sr; r < H; ++r) {
    std::fill(next.begin(), next.end(), 0);

    for (std::size_t c = 0; c < W; ++c) {
      if (curr[c] == 0)
        continue;

      if (r == H - 1) {
        total += curr[c];
        continue;
      }

      if (grid[r + 1][c] == SPLITTER) {
        if (c > 0)
          next[c - 1] += curr[c];
        if (c + 1 < W)
          next[c + 1] += curr[c];
      } else {
        next[c] += curr[c];
      }
    }

    curr.swap(next);
  }

  return total;
}

int main() {
  try {
    auto [grid, sr, sc] = parse_grid_and_find_s("inputs.txt");

    std::cout << count_splits_classical(grid, sr, sc) << "\n";
    std::cout << count_timelines_quantum(grid, sr, sc) << "\n";

    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
