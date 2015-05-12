#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <iostream>
#include <list>

#include <algorithm>
#include <functional>

#include "Resource.h"

namespace scheduler
{
	struct assigner : std::binary_function < resource, job, bool >
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

		bool assign(const job currentJob)
		{
			bool assigned = false;

			resourceStream::const_iterator resourceIterator = std::find_if(_resources.begin(),
				_resources.end(),
				std::bind2nd(assigner(), currentJob));

			if (resourceIterator != _resources.end())
			{
				assigned = true;

				std::cout << "job#" << currentJob.index << " assigned on node#" << resourceIterator->index << " for #" << currentJob.time_step << "units of time" << std::endl;

				_resources.erase(resourceIterator);
			}


			return assigned;
		}

	public:
		Scheduler(const resourceStream &resources, const jobStream &jobs) :
			_resources(resources), _jobs(jobs)
		{ }

		~Scheduler()
		{ }


		void assign()
		{
			while (!_jobs.empty())
			{
				job currentJob = _jobs.front();
				_jobs.pop_front();


				while (!assign(currentJob))
				{
					_jobs.push_back(currentJob);
					currentJob = _jobs.front();
					_jobs.pop_front();
				}

				currentJob.compute();
			}
		}
	};
}

#endif
