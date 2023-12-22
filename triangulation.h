#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <CGAL/Delaunay_triangulation_3.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <boost/program_options.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

namespace PO = boost::program_options;

class Triangulation {
 public:
  using K = CGAL::Exact_predicates_inexact_constructions_kernel;
  using Delaunay = CGAL::Delaunay_triangulation_3<K>;
  using Point = K::Point_3;

  explicit Triangulation(int argc = 1, char** argv = nullptr)
      : ac(argc), av(argv) {}
  ~Triangulation() = default;

  void checkOption(const PO::variables_map& vm, const std::string& option,
                   std::string& value, const PO::options_description& desc);
  void parseCommandLine();
  void readInputFile();
  void createTriangulation();

 private:
  int ac;
  char** av;
  std::string inputFile;
  std::string outputFile;
  std::vector<Point> pointCloud;
  std::map<Point, int> idPoints;
};

#endif  // TRIANGULATION_H