#include <fstream>
#include <iterator>
#include <ctime>


// CGAL headers
#include <CGAL/Cartesian.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/Projection_traits_yz_3.h>
#include <CGAL/ch_graham_andrew.h>
#include <CGAL/ch_melkman.h>





using namespace std;


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Projection_traits_yz_3<K> Proj;
typedef Proj::Point_2 Point_2;
typedef K::Point_3 Point_3;





int main(int argc, char **argv)
{
  int nb_points = 10000000;
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
  ofstream file2("B2output.txt");

  istream_iterator< Point_2 >  input_begin( file );
  istream_iterator< Point_2 >  input_end;
  ostream_iterator< Point_2 >  output( file2, "\n" );
  cout<<"Running convex_2"<<endl;
  clock_t start = clock();
  CGAL::convex_hull_2( input_begin, input_end, output, Proj());
  clock_t final = clock();
  double elapsed_secs = double(final - start) / CLOCKS_PER_SEC;
  cout<<"Time of B2:"<<elapsed_secs<<" seconds"<<endl;

  file2.close();
  file.close();


  ifstream file3("temp.txt");
  ofstream file4("GHAndrewoutput.txt");

  istream_iterator< Point_2 >  begin( file3 );
  istream_iterator< Point_2 >  end;
  ostream_iterator< Point_2 >  out( file4, "\n" );
  cout<<"Running Graham-Andrew"<<endl;
  start = clock();
  CGAL::ch_graham_andrew( begin, end, out, Proj());
  final = clock();
  elapsed_secs = double(final - start) / CLOCKS_PER_SEC;
  cout<<"Time of Graham-Andrew:"<<elapsed_secs<<" seconds"<<endl;

  file4.close();
  file3.close();

  ifstream file5("temp.txt");
  ofstream file6("Melkmanoutput.txt");

  istream_iterator< Point_2 >  beg( file5 );
  istream_iterator< Point_2 >  en;
  ostream_iterator< Point_2 >  out1( file6, "\n" );
  cout<<"Running Melkman"<<endl;
  start = clock();
  CGAL::ch_melkman( beg, en, out1, Proj());
  final = clock();
  elapsed_secs = double(final - start) / CLOCKS_PER_SEC;
  cout<<"Time of Melkman:"<<elapsed_secs<<" seconds"<<endl;

  file6.close();
  file5.close();




  return 0;

}