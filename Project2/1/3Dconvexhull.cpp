#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_3.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/point_generators_3.h>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
typedef CGAL::Polyhedron_3<K>                     Polyhedron_3;
typedef K::Point_3                                Point_3;
typedef K::Segment_3                              Segment_3;
typedef K::Triangle_3                             Triangle_3;

int main(int argc, char* argv[])
{
  vector<Point_3> points;
  Point_3 p;
  int n;

  if(argc>1){
    if(strcmp(argv[1],"-generate")==0){
      n=atoi(argv[2]);
    }
    int nb_points = n;
    double r = 200;
    vector<Point_3> v;
    v.reserve (nb_points);
    CGAL::Random_points_in_sphere_3<Point_3> gen (r);
    for (int i = 0; i < nb_points; ++i)  v.push_back (*gen++);

    ofstream f("input.txt");
    for (int i = 0; i < nb_points; ++i) {
      f<<v[i];
      f<<endl;
    }

    f.close();
    ifstream in( "input.txt");
    while(in >> p){
      points.push_back(p);
    }
  }
  else{
 
    while(cin >> p){
      points.push_back(p);
    }
  }
    CGAL::Object obj;
    // compute convex hull of non-collinear points
    clock_t start = clock();
    CGAL::convex_hull_3(points.begin(), points.end(), obj);
    clock_t final = clock();
    double elapsed_secs = double(final - start) / CLOCKS_PER_SEC;
    cout<<"Time of computation of CH: "<<elapsed_secs<<" seconds"<<endl;
    if(const Point_3* p = CGAL::object_cast<Point_3>(&obj)){
      std::cout << "Point " << *p << std::endl;
    }
    else if(const Segment_3* s = CGAL::object_cast<Segment_3>(&obj)){
      std::cout << "Segment " << *s << std::endl;
    }
    else if(const Triangle_3* t = CGAL::object_cast<Triangle_3>(&obj)){
      std::cout << "Triangle " << *t << std::endl;
    }
    else  if(const Polyhedron_3* poly = CGAL::object_cast<Polyhedron_3>(&obj)){
      std::cout << "Polyhedron\n " << *poly << std::endl;
    std::cout << "The convex hull contains " << poly->size_of_vertices() << " vertices" << std::endl;
    std::cout << "The convex hull contains " << poly->size_of_halfedges() << " edges" << std::endl;
    std::cout << "The convex hull contains " << poly->size_of_facets() << " facets" << std::endl;

    }
    else {
      std::cout << "something else"<< std::endl;
    }
  return 0;
}
  