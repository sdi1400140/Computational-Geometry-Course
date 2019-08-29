#include <fstream>
#include <iterator>

// CGAL headers
#include <CGAL/Cartesian.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/point_generators_2.h>


using namespace std;


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

class Compute{

  

public:
	
	void computeConvexHull(istream_iterator< Point_2 > ,istream_iterator< Point_2 > ,ostream_iterator< Point_2 >);


};

void
Compute::computeConvexHull(istream_iterator< Point_2 > begin ,istream_iterator< Point_2 >  end,ostream_iterator< Point_2 > output){
	// Time measurements
	// Compute Convex Hull
  CGAL::convex_hull_2( begin, end, output );
}


int main(int argc, char **argv)
{
  Compute mainWindow;
  ifstream file2("input1.txt");
  ofstream file("output.txt");
  istream_iterator< Point_2 >  input_begin( file2 );
  istream_iterator< Point_2 >  input_end;
  ostream_iterator< Point_2 >  output( file, "\n" );
  mainWindow.computeConvexHull( input_begin, input_end, output );
  file.close();
  file2.close();
  return 0;

}

