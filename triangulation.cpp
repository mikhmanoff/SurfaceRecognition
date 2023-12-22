#include "triangulation.h"

void Triangulation::checkOption(const PO::variables_map& vm,
                                const std::string& option, std::string& value,
                                const PO::options_description& desc) {
  if (vm.count(option)) {
    value = vm[option].as<std::string>();
  } else {
    std::cerr << "ERROR: " << option << " file not specified." << std::endl;
    std::cerr << desc << std::endl;
    exit(1);
  }
}

void Triangulation::parseCommandLine() {
  PO::options_description desc("Allowed options");
  desc.add_options()("help,h", "produce help message")(
      "input,i", PO::value<std::string>(), "set input file")(
      "output,o", PO::value<std::string>(), "set output file");
  PO::variables_map vm;

  try {
    PO::store(PO::parse_command_line(ac, av, desc), vm);
    PO::notify(vm);
  } catch (const PO::error& e) {
    std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
    std::cerr << desc << std::endl;
    exit(1);
  }

  if (vm.count("help")) {
    std::cout << desc << std::endl;
    exit(0);
  }

  checkOption(vm, "input", inputFile, desc);
  readInputFile();

  checkOption(vm, "output", outputFile, desc);
}

void Triangulation::readInputFile() {
  std::ifstream fin(inputFile, std::ios_base::in);

  if (!fin.is_open()) {
    std::cerr << "Failed to open the file" << std::endl;
    exit(1);
  }

  std::string line;
  while (std::getline(fin, line)) {
    std::istringstream iss(line);
    int id;
    double x, y, z;
    char comma;
    if (iss >> id >> comma >> x >> comma >> y >> comma >> z) {
      Point point(x, y, z);
      pointCloud.emplace_back(point);
      idPoints[point] = id;
    }
  }

  fin.close();
}

void Triangulation::createTriangulation() {
  std::ofstream ofs(outputFile, std::ios::out);

  if (!ofs.is_open()) {
    std::cerr << "ERROR: Cannot open output file." << std::endl;
    exit(1);
  }

  Delaunay dt(pointCloud.begin(), pointCloud.end());

  ofs << std::fixed << std::setprecision(6);
  ofs << "*   N,            X             Y             Z\n";
  ofs << "*Nodes\n";
  int nodeIndex = 1;

  for (auto it = pointCloud.begin(); it != pointCloud.end(); ++it) {
    ofs << nodeIndex++ << "," << std::setw(15) << it->x() << ","
        << std::setw(15) << it->y() << "," << std::setw(15) << it->z() << "\n";
  }

  ofs << "\n*Elements\n";
  int elementIndex = 1;

  for (auto it = dt.finite_cells_begin(); it != dt.finite_cells_end(); ++it) {
    ofs << elementIndex++ << "," << std::setw(15)
        << idPoints[it->vertex(0)->point()] << "," << std::setw(15)
        << idPoints[it->vertex(1)->point()] << "," << std::setw(15)
        << idPoints[it->vertex(2)->point()] << "\n";
  }

  ofs.close();
}
