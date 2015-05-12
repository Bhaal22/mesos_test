#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <cstdio>
#include <list>

#include "Resource.h"

namespace scheduler
{
	class Scheduler
	{
	public:
		typedef std::list<resource> resourceStream;
		typedef std::list<job> jobStream;

	private:
		resourceStream _resources;
		jobStream _jobs;


	public:
		Scheduler(const resourceStream &resources, const jobStream &jobs) : 
			_resources(resources), _jobs(jobs)
		{ }

		~Scheduler()
		{ }


		void assign()
		{

		}
	};
}

#endif
