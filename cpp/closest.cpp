#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <cfloat>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
 * Closest Points
 *
 * Given n points on a plane, find the smallest distance between a
 * pair of two (different) points.
 */

struct point {
	long x;
	long y;
};

/*
 * computes distance between points represented by
 * 	(x1, y1)
 * 	and
 * 	(x2, y2)
 */
double
distance(long x1, long y1, long x2, long y2)
{
	return sqrt( ((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)) );
}

double
closest_distance_brute_force(vector<point>& p, long size)
{
  double min_dist = FLT_MAX;
  double dist;

  //write your code here
  for (int i=0; i<size; i++) {
	for (int j=i+1; j<size; j++) {
		dist = distance(p[i].x, p[i].y, p[j].x, p[j].y); 
		if (dist < min_dist) {
			min_dist = dist;
			//cout << "Points (" << p[i].x << ", " << p[i].y << "), (" << p[j].x << ", " << p[j].y << ") => [" << min_dist << "]" << endl;
		}
	}
  }
  return min_dist;
}

// brute force
double minimal_distance(vector<long> x, vector<long> y)
{
  double min_dist = FLT_MAX;
  double dist;

  //write your code here
  for (long i=0; i<x.size(); i++) {
	for (long j=i+1; j<x.size(); j++) {
		dist = distance(x[i], y[i], x[j], y[j]); 
		if (dist < min_dist) {
			min_dist = dist;
			//cout << "Points (" << x[i] << ", " << y[i] << "), (" << x[j] << ", " << y[j] << ") => [" << min_dist << "]" << endl;
		}
	}
  }
  return min_dist;
}

bool
compare_x(const point a, const point b)
{
	return (a.x < b.x);
}

bool
compare_y(const point a, const point b)
{
	return (a.y < b.y);
}

double
compute_min_split_distance(vector<point>& p_x,
						   long left,
						   long mid,
						   long right,
						   double bound)
{
	// build s_y - an array which has points sorted by y in decreasing order
	// and the x co-ordinates are x-mid + bound or x-mid - bound
	vector<point> s_y;

	long x_median = p_x[mid].x;
	//cout << "Mid_x: " << x_median << ", Bound: " << bound << endl;

	for (long i = left; i<=right; i++) {
		if (abs(p_x[i].x - x_median) < bound) {
			s_y.push_back(p_x[i]);
		}
	}

	// sort s_y by y co-ordinates.
	sort(s_y.begin(), s_y.end(), compare_y);

	//cout << "Sorted s_y:" << endl;
	//for (int i=0; i<s_y.size(); i++) {
	//	cout << s_y[i].x << " " << s_y[i].y << endl;
	//}
	double min_dist = bound;
	double dist;
	long  s_y_size = s_y.size();

	for (long i=0; i<s_y_size; i++) {
		for (long j=i+1; j<=min(i+7, s_y_size-1); j++) {
			dist = distance(s_y[i].x, s_y[i].y, s_y[j].x, s_y[j].y); 
			if (dist < min_dist) {
				min_dist = dist;
				//cout << "Points (" << s_y[i].x << ", " << s_y[i].y << "), (" << s_y[j].x << ", " << s_y[j].y << ") => [" << min_dist << "]" << endl;
			}
		}
	}
	return min_dist;
}

double
compute_closest_distance(vector<point>& p_x, long left, long right)
{
	long size = right-left+1;

	if (size <= 4) {
		return closest_distance_brute_force(p_x, size);
	}

	long half = left + (right-left)/2;
	//cout << "L: " << left << " R: " << right << " M: " << half << endl;

	// divide the array p_x into two parts - still sorted by x
	double left_min = compute_closest_distance(p_x, left, half);
	double right_min = compute_closest_distance(p_x, half+1, right);

	double min_dist = (left_min > right_min)? right_min : left_min;
	//cout << "LeftMin: " << left_min << " RightMin: " << right_min << endl;
	//cout << "L: " << left << " R: " << right << " M: " << half << ", d: " << min_dist << endl;

	return compute_min_split_distance(p_x, left, half, right, min_dist);
}

double
closest_distance(vector<point>& p_x, long size)
{
	// remove this later.
	//return closest_distance_brute_force(p_x, size);

	sort(p_x.begin(), p_x.end(), compare_x);

	// print sorted points
	//cout << "Sorted x:" << endl;
	//for (int i=0; i<size; i++) {
	//	cout << p_x[i].x << " " << p_x[i].y << endl;
	//}

	//cout << "Sorted y:" << endl;
	//for (int i=0; i<size; i++) {
	//	cout << p_y[i].x << " " << p_y[i].y << endl;
	//}
	return compute_closest_distance(p_x, 0, size-1);
}

int main(int argc, char **argv)
{
  long n;

  if (argc < 2) {
  	std::cin >> n;
  } else if (argc == 2) {
	n = atoi(argv[1]);
  } else {
	cout << "usage: ./closest <number of points>" << endl;
	exit(-1);
  }

  vector<long> x(n);
  vector<long> y(n);

  vector<point> p_x(n); // points sorted by x

  if (argc == 2) {
  	// generate the points randonly.
  	srand(time(0));
  	for (long i = 0; i < n; i++) {
  	  p_x[i].x = x[i] = rand() % (n*10000);
  	  p_x[i].y = y[i] = rand() % (n*10000);
  	}
  } else {
    // get from file.
  	for (long i = 0; i < n; i++) {
  	  std::cin >> x[i] >> y[i];
  	  p_x[i].x = x[i];
  	  p_x[i].y = y[i];
  	}
  }

  //cout << "Size: p_x [" << p_x.size() << "] x,y [" << x.size() << "]\n";
  //cout << "p_x" << endl;
  //for (int i=0; i<p_x.size(); i++) {
  //	cout << p_x[i].x << " " << p_x[i].y << endl;
  //}
  //
  //cout << "x:y" << endl;
  //for (int i=0; i<x.size(); i++) {
  //	cout << x[i] << " " << y[i] << endl;
  //}
  std::cout << std::fixed;
  //std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
  std::cout << std::setprecision(9) << closest_distance(p_x, p_x.size()) << "\n";
}
