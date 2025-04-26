#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
	const AvailabilityMatrix& avail,
	const size_t d,
	const size_t m,
	DailySchedule& sched, 
	vector<size_t>& counts, 
	size_t currDay, 
	size_t currShift
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
	if(avail.size() == 0U){
			return false;
	}
	sched.clear();
	// Add your code below
	
	int k = avail[0].size();
	vector<size_t> counts(k, 0);

	//initialize sched (nxd) to correct size 
	int n = avail.size();
	for (int i = 0; i < n; i++) {
		sched.push_back(vector<Worker_T>(dailyNeed, INVALID_ID));
	}
	
	size_t currShift = 0; 
	size_t currDay = 0;
	return scheduleHelper(avail, dailyNeed, maxShifts, sched, counts, currDay, currShift);
	
}

bool scheduleHelper(
	const AvailabilityMatrix& avail,
	const size_t d,
	const size_t m,
	DailySchedule& sched, 
	vector<size_t>& counts, 
	size_t currDay, 
	size_t currShift
) 
{
	size_t n = avail.size();
	size_t k = avail[0].size();
	// solution found when all days are filled 
	if (currDay == n) return true;

	// all slots filled for current day - move to next day 
	if (currShift == d) {
		currShift = 0;
		return scheduleHelper(avail, d, m, sched, counts, currDay+1, currShift);
	}

	// try all workers for this shift 
	for (size_t w = 0; w < k; w++) {
		// make sure worker hasn't been assigned to this day's shift already 
		// check if worker is available for this shift 
		// check if worker working this shift will exceed their max 
		if ((avail[currDay][w] == 1) && (counts[w] < m) && (find(sched[currDay].begin(), sched[currDay].end(), w) == sched[currDay].end())) {
			//assign w to this shift 
			sched[currDay][currShift] = w; 
			// increase count of how many shifts this worker has worked 
			counts[w] += 1;

			if (scheduleHelper(avail, d, m, sched, counts ,currDay, currShift+1)) {
				return true;
			}
			// backtrack 
			counts[w] -= 1;
			sched[currDay][currShift] = INVALID_ID;
		}
		
	}
	return false;
}

