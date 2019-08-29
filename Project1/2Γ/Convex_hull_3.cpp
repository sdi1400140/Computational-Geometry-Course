#include <fstream>
#include <iterator>

// CGAL headers
#include <CGAL/Cartesian.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/intersections.h>



using namespace std;


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;
typedef K::Line_2 Line_2;
typedef K::Intersect_2 Intersect_2;

class Compute{

  

public:
	
	void computeConvexHull(istream_iterator< Point_2 > ,istream_iterator< Point_2 > ,ostream_iterator< Point_2 >);
  void intercompute(Line_2,Segment_2);


};

void
Compute::computeConvexHull(istream_iterator< Point_2 > begin ,istream_iterator< Point_2 >  end,ostream_iterator< Point_2 > output){
	// Time measurements
	// Compute Convex Hull
  CGAL::convex_hull_2( begin, end, output );
}

void Compute::intercompute(Line_2 lin,Segment_2 seg){
    CGAL::cpp11::result_of<Intersect_2(Segment_2, Line_2)>::type
    result = intersection(seg, lin);
    if (result) {
      if (const Segment_2* s = boost::get<Segment_2>(&*result)) {
        cout<<"Segment:"<<endl;
        cout << *s <<endl;
      }else {
        const Point_2* p = boost::get<Point_2 >(&*result);
        cout<<"Point:"<<endl;
        cout << *p <<endl;
      }
    }
}

int main(int argc, char **argv)
{
  Compute mainWindow;
  char line[30];
  int a,b;
  Point_2 p1x,p2x;
  ifstream file2("input1.txt");
  ofstream f("temp.txt");
  if(file2){
      while(file2.getline(line,30)){
        if(strcmp(line,"Points")==0){
          char* pch;
          file2.getline(line,30);
          pch=strtok(line," ");
          a=atoi(pch);
          pch=strtok(NULL,"\n");
          b=atoi(pch);
          Point_2 p1(a,b);
          p1x=p1;
          file2.getline(line,30);
          pch=strtok(line," ");
          a=atoi(pch);
          pch=strtok(NULL,"\n");
          b=atoi(pch);
          Point_2 p2(a,b);
          p2x=p2;
          break;
        }
        else{
          f.write(line,strlen(line));
          f<<endl;
        }
      }
  }
  f.close();
  file2.close();

  ifstream file4("temp.txt");
  ofstream file("output.txt");
  istream_iterator< Point_2 >  input_begin( file4 );
  istream_iterator< Point_2 >  input_end;
  ostream_iterator< Point_2 >  output( file, "\n" );
  mainWindow.computeConvexHull( input_begin, input_end, output );
  file.close();
  file4.close();
  Line_2 lin(p1x,p2x);
  ifstream file3("output.txt");
  if(file3){
    int flag=0;
    Point_2 first;
    Point_2 last;
    while(file3.getline(line,30)){
          char* pch;
          pch=strtok(line," ");
          a=atoi(pch);
          pch=strtok(NULL,"\n");
          b=atoi(pch);
          if(flag==0){
            Point_2 p1(a,b);
            first=p1;
            last=p1;
            flag=1;
          }
          else if(flag==1){
            Point_2 p1(a,b);
            Segment_2 seg(p1,last);
            mainWindow.intercompute(lin,seg);   
            last=p1;
          }
   }
    Segment_2 seg(first,last);
    mainWindow.intercompute(lin,seg);
  }
  file3.close();
  return 0;

}

