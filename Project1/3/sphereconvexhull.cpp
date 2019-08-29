#include <fstream>
#include <iterator>

// CGAL headers
#include <CGAL/Cartesian.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/Projection_traits_yz_3.h>



using namespace std;


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Projection_traits_yz_3<K> Proj;
typedef Proj::Point_2 Point_2;
typedef K::Point_3 Point_3;





int main(int argc, char **argv)
{
  int nb_points = 10;
  double r = 25.60;
  cout << "Generating "<<nb_points<<" random points on the surface of "
        <<"a sphere of center 0 and radius "<<r<<endl;
  vector<Point_3> v;
  v.reserve (nb_points);
  CGAL::Random_points_on_sphere_3<Point_3> gen (r);
  for (int i = 0; i < nb_points; ++i)  v.push_back (*gen++);

  ofstream f("temp.txt");
  for (int i = 0; i < nb_points; ++i) {
    f<<v[i];
    f<<endl;
  }
  f.close();

  ifstream file("temp.txt");
  ofstream file2("output.txt");

  istream_iterator< Point_2 >  input_begin( file );
  istream_iterator< Point_2 >  input_end;
  ostream_iterator< Point_2 >  output( file2, "\n" );
  CGAL::convex_hull_2( input_begin, input_end, output,Proj());
  file2.close();
  file.close();
  return 0;

}