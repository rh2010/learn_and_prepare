#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;

/*
 * Implement a job scheduling algorithm given the weights (priority) and the
 * lengths of the jobs.
 *
 * Read in the job information from a file, do the scheduling and come up with
 * a greedy schedule and find out the weighted completion time of the schedule.
 */
struct job {
	double w;
	double l;
};

//comparator class
/*
 * A comparator class to compare two given jobs by the ratio of weight/length
 */
class
job_comparator {
	public:
	bool operator()(const job& j1, const job& j2)
	{
		return j1.w/j1.l < j2.w/j2.l;
	}
};

/*
 * A comparator class to compare two given jobs by the difference in
 * weight-length
 * and if the difference is equal then with weight alone.
 */
class
job_comparator_by_difference {
	public:
	bool operator()(const job& j1, const job& j2)
	{
		double diff1, diff2;
		diff1 = j1.w - j1.l;
		diff2 = j2.w - j2.l;

		//cout << "J1 : w: " << j1.w << ", l: " << j1.l << ", diff: " << diff1 << endl;
		//cout << "J2 : w: " << j2.w << ", l: " << j2.l << ", diff: " << diff2 << endl;

		if (diff1 == diff2) {
			return j1.w < j2.w;
		}
		return diff1 < diff2;
	}
};

int
main(int argc, char **argv)
{
	long size;
	char *file_name;
	double w, l;

	if (argc != 2) {
		cout << "usage: ./jobs <file_name>\n";
		exit(-1);
	}

	file_name = argv[1];

	// open the file
	ifstream jobs_file(file_name);

	// get total jobs
	jobs_file >> size;

	// get the vector for storing info for jobs.
	vector<job> jobs(size);

	// priority queue for storing the jobs.
	priority_queue<job, vector<job>, job_comparator> pq;

	int i=0;
	// fill in the weights and respective lengths
	while (jobs_file >> w >> l) {
		jobs[i].w = w;
		jobs[i].l = l;

		//cout << "Adding w: " << w << ", l: " << l << endl;
		// add the job to the priority queue
		pq.push(jobs[i]);
		i++;
		//cout << "PQ Top: w: " << (pq.top()).w << ", l: " << (pq.top()).l << endl << endl;
	}
	//cout << "Done reading from file: " << file_name << endl;
	cout << "Read " << i << " jobs from file " << file_name << endl;

	double ct=0;
	double weighted_ct=0;

	while (!pq.empty()) {
		w = (pq.top()).w;
		l = (pq.top()).l;

		// completion time for current job
		ct += l;
		cout << "ct: " << ct << ", weighted_ct: " << w*ct << endl;

		// weighted completion time for current job
		weighted_ct = weighted_ct + (w*ct);

		// remove the top element from the pq
		// process the next job.
		pq.pop();
	}
	//cout << "Completion Time: " << ct << endl;
	cout << "Result: " << static_cast<long>(weighted_ct) << endl;

	return (0);
}
