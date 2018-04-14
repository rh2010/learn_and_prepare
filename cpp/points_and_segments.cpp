#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

/*
 * Organizing a Lottery
 *
 * You are given a set of points on a line and a set of segments on a line. The goal is to compute, for
 * each point, the number of segments that contain this point.
 *
 * Three solutions are implemented.
 * 	1. Naive
 * 	2. Using line-sweep algo - using priority queue (Min Heap)
 * 	3. sorting
 */

struct segment {
	long long start;
	long long end;
};

struct point {
	long long index;
	long long value;
};

/*
 * type:
 * 	0 - segment start
 * 	1 - point
 * 	2 - segment end
 */
struct element {
	int type;

	union {
		point p;
		long long start;
		long long end;
	}u;
};

bool
compare_segments(const segment s1, const segment s2)
{
	if (s1.start == s2.start) {
		return (s1.end < s2.end);
	}
	return (s1.start < s2.start);
}

bool
compare_points(const point p1, const point p2)
{
	return (p1.value < p2.value);
}

// comparator class for less segment
class
min_seg {
	public:
	//overload()
	bool operator()(const segment& s1, const segment& s2)
	{
		return (s1.end > s2.end);
	}
};

const char*
element_type(const element e)
{
	switch (e.type) {
		case 0: // start
			return "Start";
			break;
		case 1: // point
			return "Point";
			break;
		case 2: // end
			return "End";
			break;
	}
}

long long
element_data(const element e)
{
	long long data;

	switch (e.type) {
		case 0: // start
			data = e.u.start;
			break;
		case 1: // point
			data = e.u.p.value;
			break;
		case 2: // end
			data = e.u.end;
			break;
	}
	return data;
}

bool
compare_elements(const element e1, const element e2)
{
	long long e1_data = element_data(e1);
	long long e2_data = element_data(e2);

	if (e1_data == e2_data) {
		return (e1.type < e2.type);
	}

	return (e1_data < e2_data);
}

void
fast_count_segments2(vector<segment>& segments, vector<point> points, vector<long long>& cnt)
{
  long long i, j;
  long long seg_size = segments.size();
  long long num_points = points.size();

  vector<element> data_list(num_points + (2 * seg_size));

  //cout << "Building vector" << endl;
  // build the vector
  for (i=0; i<num_points; i++) {
    //cout << " [" << j <<"] " << points[i].value << " Point : " << points[i].index << endl;
	data_list[i].type = 1;
	data_list[i].u.p.value = points[i].value;
	data_list[i].u.p.index = points[i].index;
  }
  for (j=0; j<seg_size; j++) {
    //cout << " [" << (2*i) << "] " << segments[i].start << " Start" << endl;
	data_list[i].type = 0;
	data_list[i].u.start = segments[j].start;
	i++;

    //cout << " [" << ((2*i) + 1) <<"] " << segments[i].end << " End" << endl;
	data_list[i].type = 2;
	data_list[i].u.end = segments[j].end;
	i++;
  }

  // sort the vector
  sort(data_list.begin(), data_list.end(), compare_elements);

  // print sorted vector
  //cout << "Sorted Vector: " << endl;
  //for (i=0; i<data_list.size(); i++) {
  //  cout << element_data(data_list[i]) << " " << element_type(data_list[i]) << endl;
  //}

  long long segment_count = 0;

  // process data list
  long long point_count = 0;
  for (i=0; (i<data_list.size()) && (point_count < num_points); i++) {
	switch(data_list[i].type) {
		case 0: // start
			segment_count++;
			break;
		case 1: // point
			cnt[data_list[i].u.p.index] = segment_count;
			break;
		case 2: // end
			segment_count--;
			break;
	}
  }
}

void
fast_count_segments(vector<segment>& segments, vector<point> points, vector<long long>& cnt)
{
  long long i, j;
  long long seg_size = segments.size();
  long long num_points = points.size();

  // sort the vectors
  sort(segments.begin(), segments.end(), compare_segments);
  sort(points.begin(), points.end(), compare_points);

  // print segments
  //cout << "Sorted Segments: " << endl;
  //for (i=0; i<seg_size; i++) {
  //  cout << "\t" << segments[i].start << " " << segments[i].end << endl;
  //}
  //cout << endl;
  //// print points
  //cout << "Sorted points: " << endl;
  //for (i=0; i<num_points; i++) {
  //  cout << "\t" << points[i].value << " ";
  //}
  //cout << endl;

  // min heap
  priority_queue<segment, vector<segment>, min_seg> min_heap;


  i = 0; // segments
  j = 0; // points

  while (j < num_points) {

	if ( i >= seg_size) {
		// all segments are processed
		//
		// no new segments are being added
		//
		// just process the points
		// process the min_heap first
		while (!min_heap.empty() && (min_heap.top()).end < points[j].value) {
			// if a previous segment ends before this point
			// remove it from the min_heap.
			min_heap.pop();
		}

		// the current point is present in all the segments in the min_heap.
		cnt[points[j].index] = min_heap.size();

		// Special case:
		// if the next point starts at the same place
		// then process the point with the next segment
		if ( (j+1 < num_points) && (points[j].value == points[j+1].value)) {
			j++;
			continue;
		}

		while (!min_heap.empty() && (min_heap.top()).end == points[j].value) {
			// if a previous segment ends at this point
			// remove it from the min_heap.
			min_heap.pop();
		}

		j++; // next point

	} else {
		if (segments[i].start < points[j].value) { // segment starts before point

			// process the min_heap first
			while (!min_heap.empty() && (min_heap.top()).end <= segments[i].start ) {
				// if a previous segment ends before this segment
				// remove it from the min_heap.
				min_heap.pop();
			}

			// add the segment to the min_heap
			min_heap.push(segments[i]);

			i++; // next segment

		} else if (segments[i].start > points[j].value) { // point is before segment start

			// process the min_heap first
			while (!min_heap.empty() && (min_heap.top()).end < points[j].value) {
				// if a previous segment ends before this point
				// remove it from the min_heap.
				min_heap.pop();
			}

			// the current point is present in all the segments in the min_heap.
			cnt[points[j].index] = min_heap.size();

			// Special case:
			// if the next point starts at the same place
			// then process the point with the next segment
			if ( (j+1 < num_points) && (points[j].value == points[j+1].value)) {
				j++;
				continue;
			}

			while (!min_heap.empty() && (min_heap.top()).end == points[j].value) {
				// if a previous segment ends at this point
				// remove it from the min_heap.
				min_heap.pop();
			}

			j++; // next point

		} else { // point and segment start overlap

			// process the min_heap first
			while (!min_heap.empty() && (min_heap.top()).end < points[j].value) {
				// if a previous segment ends before this point/segment
				// remove it from the min_heap.
				min_heap.pop();
			}

			// add the segment to the min_heap
			min_heap.push(segments[i]);
			i++; // next segment

			// Special case:
			// if the next segment starts at the same place
			// then process the point with the next segment
			if ( (i < seg_size) && (segments[i].start == points[j].value)) {
				continue;
			}

			// the current point is present in all the segments in the min_heap.
			cnt[points[j].index] = min_heap.size();

			// Special case:
			// if the next point starts at the same place
			// then process the point with the next segment
			if ( (j+1 < num_points) && (points[j].value == points[j+1].value)) {
				j++;
				continue;
			}

			while (!min_heap.empty() && (min_heap.top()).end == points[j].value) {
				// if a previous segment ends at this point
				// remove it from the min_heap.
				min_heap.pop();
			}

			j++; // next point
		}
	}

  } // end of while

  // drain the heap
  while (!min_heap.empty()) {
	min_heap.pop();
  }
}

void
naive_count_segments(vector<long long> starts, vector<long long> ends, vector<point> points, vector<long long>& cnt)
{
  for (long long i = 0; i < points.size(); i++) {
    for (long long j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i].value && points[i].value <= ends[j];
    }
  }
}

bool
check_results(const vector<long long>& cnt1, const vector<long long>& cnt2)
{
	assert(cnt1.size() == cnt2.size());

	for (long long i=0; i < cnt1.size(); i++) {
		if (cnt1[i] != cnt2[i]) {
			return false;
		}
	}
	return true;
}

int main(int argc, char **argv)
{
  long long n, m;

  if (argc < 2) {
  	std::cin >> n >> m;
  } else if (argc == 3) {
	n = atoi(argv[1]); // segments
	m = atoi(argv[2]); // points
  } else {
	cout << "usage: ./segments <num of segments> <number of points>" << endl;
  }

  vector<long long> starts(n), ends(n);
  vector<segment> segments(n);
  vector<point> points(m);

  if (argc == 3) {
	// fill in randomly
	srand(time(0));
	srand48(time(0));
  	for (long long i = 0; i < starts.size(); i++) {
  	  starts[i]  = mrand48();
	  ends[i] = starts[i] + (rand() % (10000));
	  segments[i].start = starts[i];
	  segments[i].end = ends[i];
  	}
  	for (long long i = 0; i < points.size(); i++) {
  	  points[i].value = mrand48();
	  points[i].index = i;
  	}
  } else {
  	for (long long i = 0; i < starts.size(); i++) {
  	  std::cin >> starts[i] >> ends[i];
	  segments[i].start = starts[i];
	  segments[i].end = ends[i];
  	}
  	for (long long i = 0; i < points.size(); i++) {
  	  std::cin >> points[i].value;
	  points[i].index = i;
  	}
  }

  //naive versions
  //cout << "Naive: ";
  //vector<long long> cnt1(points.size());
  //naive_count_segments(starts, ends, points, cnt1);
  //for (long long i = 0; i < cnt1.size(); i++) {
  //  std::cout << cnt1[i] << ' ';
  //}
  //cout << endl;

  //fast_count_segments
  //cout << "Efficient: ";
  vector<long long> cnt2(points.size());
  fast_count_segments(segments, points, cnt2);
  for (long long i = 0; i < cnt2.size(); i++) {
    std::cout << cnt2[i] << ' ';
  }
  cout << endl;

  //cout << "Optimal2: ";
  //vector<long long> cnt3(points.size());
  //fast_count_segments2(segments, points, cnt3);
  //for (long long i = 0; i < cnt3.size(); i++) {
  //  std::cout << cnt3[i] << ' ';
  //}
  //cout << endl;

  //for (long long i = 0; i < cnt2.size(); i++) {
  /*
  if (check_results(cnt1, cnt3)) {
    cout << "Pass" << endl;

  	cout << "Naive: ";
  	for (long long i = 0; i < cnt1.size(); i++) {
  	  std::cout << cnt1[i] << ' ';
  	}
  	cout << endl;

  	cout << "Optimal2: ";
  	for (long long i = 0; i < cnt3.size(); i++) {
  	  std::cout << cnt3[i] << ' ';
  	}
  	cout << endl;
  } else {
    cout << "Fail" << endl;

  	cout << "Naive: ";
  	for (long long i = 0; i < cnt1.size(); i++) {
  	  std::cout << cnt1[i] << ' ';
  	}
  	cout << endl;

  	cout << "Optimal2: ";
  	for (long long i = 0; i < cnt3.size(); i++) {
  	  std::cout << cnt3[i] << ' ';
  	}
  	cout << endl;

  }

  if (check_results(cnt3, cnt2)) {
    cout << "Pass" << endl;

  	cout << "Optimal: ";
  	for (long long i = 0; i < cnt2.size(); i++) {
  	  std::cout << cnt2[i] << ' ';
  	}
  	cout << endl;

  	cout << "Optimal2: ";
  	for (long long i = 0; i < cnt3.size(); i++) {
  	  std::cout << cnt3[i] << ' ';
  	}
  	cout << endl;
  } else {
    cout << "Fail" << endl;

  	cout << "Optimal: ";
  	for (long long i = 0; i < cnt2.size(); i++) {
  	  std::cout << cnt2[i] << ' ';
  	}
  	cout << endl;

  	cout << "Optimal2: ";
  	for (long long i = 0; i < cnt3.size(); i++) {
  	  std::cout << cnt3[i] << ' ';
  	}
  	cout << endl;
  }
  */
}
