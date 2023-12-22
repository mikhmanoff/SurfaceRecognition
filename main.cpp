#include "triangulation.h"

int main(int argc, char** argv) {
  try {
    Triangulation triangulation(argc, argv);

    triangulation.parseCommandLine();
    triangulation.createTriangulation();
    return 0;
  } catch (const std::exception& e) {
    std::cerr << "An exception occurred: " << e.what() << std::endl;
    return 1;
  }
}
