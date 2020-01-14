#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace {
struct Date {
  Date(int day, int month, int year) : Day(day), Month(month), Year(year) {}
  int Day, Month, Year;
};

Date KthLatest(std::size_t k, std::vector<Date>& dates);

Date ThirdLatest(std::vector<Date>& dates) {
  // Two ways to solve the problem:
  // Let's call n the size of the input array
  //
  //   1- Quick implementation easily maintainable & understandable
  //        * sort input array O(n log n)
  //        * return k-th = 3rd largest element of the array
  //
  //   2- Less quick implementation easily maintainable & understandable
  //        * MaxHeap creation
  //        * extract MaxHeap k times (3 times)
  //        Time complexity O(n + k log(n))

  return KthLatest(3, dates);
}

std::string to_string(const Date& date) {
  return std::to_string(date.Day) + "/" + std::to_string(date.Month) + "/" + std::to_string(date.Year);
}

Date KthLatest(std::size_t k, std::vector<Date>& dates) {
  auto compare = [](const auto& date1, const auto& date2) {
    /*
    if (date1.Year < date2.Year) {
      return true;
    } else {
      if (date1.Month < date2.Month) {
        return true;
      } else {
        return date1.Day < date2.Day;
      }
    }
     */

    if (date1.Year < date2.Year) {
      return true;
    }

    if (date1.Year == date2.Year) {

      if (date1.Month < date2.Month) {
        return true;
      }

      if (date1.Month == date2.Month) {
        if (date1.Day < date2.Day) {
          return true;
        }
      }
    }

    return false;

  };

  if (k > dates.size()) {  // should not happen
    throw std::invalid_argument("cannot find the k-th greatest element of a n < k array list");
  }

  std::make_heap(std::begin(dates), std::end(dates), compare);

  //  std::cout << "\n\nafter heap : \n";
  //
  //  for(const auto& date: dates) {
  //    std::cout << to_string(date) << std::endl;
  //  }

  auto equal_date = [](const auto& date1, const auto& date2) {
    return (date1.Year == date2.Year && date1.Month == date2.Month && date1.Day == date2.Day);
  };

  for (size_t i = 0; i < k - 1; ++i) {
    std::pop_heap(std::begin(dates), std::end(dates), compare);

    Date temporary = dates.front();

    if (equal_date(temporary, dates.back())) {  // avoid duplicates
      k++;
    }

    dates.pop_back();

    //    std::cout << "\n\nafter pop [ " << i << " ] times : \n";
    //
    //    for(const auto& date: dates) {
    //      std::cout << to_string(date) << std::endl;
    //    }
  }

  return dates.front();
}

}  // namespace

using OnResult = std::function<void(const Date& expected, const Date& result)>;

bool test_case(std::vector<Date>& dates, const Date& expected, OnResult on_result = nullptr) {
  static std::size_t count = 0;
  std::cout << "\n\nTest Case #" << count++ << "  ";

  auto result = KthLatest(3, dates);

  if (on_result) {
    std::cout << std::endl;
    on_result(expected, result);
  }

  return to_string(expected) == to_string(result);
}

bool test_case1(OnResult on_result = nullptr) {
  std::vector<Date> dates;

  dates.emplace_back(14, 04, 2001);
  dates.emplace_back(29, 12, 2061);
  dates.emplace_back(21, 10, 2019);
  dates.emplace_back(07, 01, 1973);
  dates.emplace_back(19, 07, 2014);
  dates.emplace_back(11, 03, 1992);

  Date expected(19, 07, 2014);

  return test_case(dates, expected, on_result);
}

bool test_case2(OnResult on_result = nullptr) {
  std::vector<Date> dates;
  dates.emplace_back(14, 04, 2001);
  dates.emplace_back(29, 12, 2061);
  dates.emplace_back(21, 10, 2019);
  dates.emplace_back(07, 01, 1973);
  dates.emplace_back(19, 07, 2014);
  dates.emplace_back(11, 03, 1992);
  dates.emplace_back(21, 10, 2019);

  Date expected(19, 07, 2014);

  return test_case(dates, expected, on_result);
}

int main() {

  std::cout << std::boolalpha << test_case1([](const auto& expected, const auto& result) {
    std::cout << "expected   \t result \n";
    std::cout << to_string(expected) << " -- " << to_string(result) << std::endl;
  }) << std::endl;

  std::cout << std::boolalpha << test_case2([](const auto& expected, const auto& result) {
    std::cout << "expected   \t result \n";
    std::cout << to_string(expected) << " -- " << to_string(result) << std::endl;
  }) << std::endl;

  return EXIT_SUCCESS;
}