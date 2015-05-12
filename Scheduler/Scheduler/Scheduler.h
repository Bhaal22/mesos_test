#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <cstdio>
#include <list>

#include <algorithm>
#include <functional>

#include "Resource.h"

namespace scheduler
{
	struct assigner : std::binary_function<resource, job, bool>
	{
		bool operator() (const resource &currentResource, const job &currentJob) const
		{
			return true;
		}
	};

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
			job currentJob = _jobs.front();
			_jobs.pop_front();


			//_resources.remove_if()
			resourceStream::const_iterator res = std::find_if(_resources.begin(),
															  _resources.end(),
															  std::bind2nd(assigner(), currentJob));

			if (res != _resources.end())
			{

			}
			else
			{
				//job cannot be run currently
				//pass to next job
			}
		}
	};
}

#endif
