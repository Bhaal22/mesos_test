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

		return stream;
	}

	scheduler::Scheduler::jobStream generate_jobs()
	{ 
		scheduler::Scheduler::jobStream stream;

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


