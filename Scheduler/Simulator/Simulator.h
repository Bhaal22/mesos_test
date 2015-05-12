#ifndef __SIMULATOR_H
#define __SIMULATOR_H

#include <list>
#include "Scheduler.h"
#include "Strategies.h"

class Simulator
{
private:
	scheduler::resourceStream generate_resources()
	{ 
		scheduler::resourceStream stream;

		stream.push_back(scheduler::resource(2, 3));
		stream.push_back(scheduler::resource(7, 1));
		stream.push_back(scheduler::resource(1, 23));
		stream.push_back(scheduler::resource(8, 5));
		stream.push_back(scheduler::resource(2, 8));

		return stream;
	}

	scheduler::jobStream generate_jobs()
	{ 
		scheduler::jobStream stream;

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
		scheduler::resourceStream resourceStream = generate_resources();
		scheduler::jobStream jobStream = generate_jobs();


		scheduler::Scheduler<scheduler::strategies::asyncJobRunner> sched(resourceStream, jobStream);
		
		sched.start();
		sched.wait();
	}
};

#endif


