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

		resourceStream::iterator assign(const job currentJob)
		{
			resourceStream::iterator resourceIterator = std::find_if(_resources.begin(),
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


		void start()
		{
			runner _runner;
			while (!_jobs.empty())
			{
				job currentJob = _jobs.front();
				_jobs.pop_front();

				resourceStream::iterator resourceIterator = assign(currentJob);
				std::cout << "Trying to find out a resource for job#" << currentJob.index << "#" << currentJob.units_needed << std::endl;
				while (resourceIterator == _resources.end())
				{
					std::this_thread::sleep_for(std::chrono::seconds(1));
					_jobs.push_back(currentJob);
					currentJob = _jobs.front();
					_jobs.pop_front();

					resourceIterator = assign(currentJob);
				}

				_futures.push_back(_runner.run(currentJob, resourceIterator));
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
