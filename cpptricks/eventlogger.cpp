/*
 * eventlogger.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: rong
 */
#include <vector>

// For testing functions
#include <chrono>
#include <thread>
#include <random>
#include <iostream>
#include <mutex>

using std::vector;
using std::cout;
using std::endl;

class EventLogger {
	vector<unsigned long long> _perseconds{vector<unsigned long long>(3600, 0)}; // 1 hours = 3600s; second is the minimal couting unit; can be extend to last n-secondsor month
	unsigned _cursor{0};
	unsigned long long _last_min_count{0};
	unsigned long long _last_hour_count{0};
public:
	void update(unsigned long long n) { // update with the last second count n
		unsigned next_cursor = ++_cursor % 3600;
		unsigned long long outdated = _perseconds[next_cursor];
		_last_hour_count += n;
		_last_hour_count -= outdated;
		_last_min_count += n;
		_last_min_count -= _perseconds[(_cursor-61) % 3600];
		_perseconds[_cursor] = n;
	}

	unsigned long long lastSecondCount() const {
		return _perseconds[_cursor % 3600];
	}

	unsigned long long lastMinuteCount() const {
		return _last_min_count;
	}

	unsigned long long lastHourCount() const {
		return _last_hour_count;
	}

};

// std::mutex os_mutex;

void random_update(EventLogger* logger, unsigned duration = 3600) {
	for (unsigned i = 0; i<duration; ++i) {
		std::chrono::milliseconds sec( 2000 );
		std::this_thread::sleep_for( sec );
		auto seed(std::chrono::system_clock::now().time_since_epoch().count());
		std::minstd_rand0 generator(seed);
		// cout << "Random number: " << n << endl;
		logger->update(generator());
		/*
		os_mutex.lock();
		cout << "Last second count: " << logger->lastSecondCount() << endl;
				cout << "Last minute count: " << logger->lastMinuteCount() << endl;
				cout << "Last hour count: " << logger->lastHourCount() << endl;
		cout << "-----------Done-----------" << endl;
		os_mutex.unlock();
		 */
	}
}

void monitor(const EventLogger* logger, unsigned duration = 3600) {
	for (unsigned i = 0; i<duration; ++i) {
		std::chrono::milliseconds sec( 2000 );
		std::this_thread::sleep_for( sec );
		// os_mutex.lock();
		cout << "Time passed (s): \t" << i+1 << endl;
		cout << "Last second count: \t" << logger->lastSecondCount() << endl;
		cout << "Last minute count: \t" << logger->lastMinuteCount() << endl;
		cout << "Last hour count:  \t"<< logger->lastHourCount() << endl;
		cout << "-------------------------" << endl;
		// os_mutex.unlock();
	}
}


int main () {
	EventLogger logger;
	std::thread updater{std::bind(random_update, &logger, 65)}; // never pass real object to bind; passing pointer
	monitor(&logger, 65);
	updater.join();
	return 0;
}
