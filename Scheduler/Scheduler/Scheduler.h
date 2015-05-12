#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <iostream>
#include <list>

#include <algorithm>
#include <functional>

#include <future>

#include "Resource.h"
#include "Strategies.h"

namespace scheduler
{
	typedef std::list<resource> resourceStream;
	typedef std::list<job> jobStream;

	template<typename JobRunningStrategy, typename AssignmentStrategy = strategies::assigner>
	class Scheduler
	{
	public:
		typedef typename JobRunningStrategy::type runner;
		typedef typename AssignmentStrategy::type assignment;

	private:
		resourceStream _resources;
		jobStream _jobs;

		std::list<std::future<void>> _futures;

		resourceStream::const_iterator assign(const job currentJob)
		{
			bool assigned = false;

			resourceStream::const_iterator resourceIterator = std::find_if(_resources.begin(),
				_resources.end(),
				std::bind2nd(assignment(), currentJob));

			if (resourceIterator != _resources.end())
			{
				std::cout << "job#" << currentJob.index << " assigned on node#" << resourceIterator->index << " for #" << currentJob.time_step << "units of time" << std::endl;
			}


			return resourceIterator;
		}

	public:
		Scheduler(const resourceStream &resources, const jobStream &jobs) :
			_resources(resources), _jobs(jobs)
		{ }

		~Scheduler()
		{ }


		void assign()
		{
			runner _runner;
			while (!_jobs.empty())
			{
				job currentJob = _jobs.front();
				_jobs.pop_front();

				resourceStream::const_iterator resourceIterator = assign(currentJob);
				while (resourceIterator == _resources.end())
				{
					_jobs.push_back(currentJob);
					currentJob = _jobs.front();
					_jobs.pop_front();
				}

				resource currentResource = *resourceIterator;
				_futures.push_back(_runner.run(currentJob, currentResource));
			}
		}

		void wait()
		{
			
			std::for_each(_futures.begin(),
						  _futures.end(),
						  std::mem_fun_ref(&std::future<void>::wait));
		}
	};
}

#endif
