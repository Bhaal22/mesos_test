#ifndef __SIMULATOR_H
#define __SIMULATOR_H

#include <list>
#include "Scheduler.h"

class Simulator
{
private:
	scheduler::Scheduler::resourceStream generate_resources()
	{ 
		scheduler::Scheduler::resourceStream stream;

		stream.push_back(scheduler::resource(2, 3));
		stream.push_back(scheduler::resource(7, 1));
		stream.push_back(scheduler::resource(1, 23));
		stream.push_back(scheduler::resource(8, 5));
		stream.push_back(scheduler::resource(2, 8));

		return stream;
	}

	scheduler::Scheduler::jobStream generate_jobs()
	{ 
		scheduler::Scheduler::jobStream stream;

		stream.push_back(scheduler::job(1, 3, 4));
		stream.push_back(scheduler::job(2, 1, 4));
		stream.push_back(scheduler::job(3, 4, 7));
		stream.push_back(scheduler::job(4, 1, 3));
		stream.push_back(scheduler::job(5, 5, 4));
		stream.push_back(scheduler::job(6, 9, 3));


		return stream;
	}

public:
	Simulator()
	{ }

	~Simulator()
	{ }

	void start()
	{
		scheduler::Scheduler::resourceStream resourceStream = generate_resources();
		scheduler::Scheduler::jobStream jobStream = generate_jobs();


		scheduler::Scheduler sched(resourceStream, jobStream);
		

		sched.assign();
	}
};

#endif


