#ifndef __STRATEGIES_H
#define __STRATEGIES_H

#include <future>

#include "Resource.h"

namespace scheduler
{
	namespace strategies
	{
		struct simpleJobRunner
		{
			typedef simpleJobRunner type;

			void run(const job &currentJob, resource &currentResource)
			{
				currentResource.run(currentJob);
			}
		};

		struct asyncJobRunner
		{
		public:
			typedef asyncJobRunner type;


			asyncJobRunner()
			{ }

			std::future<void> run(const job &currentJob, resource &currentResource)
			{
				currentResource.set_in_use(true);
				std::future<void> future = std::async(std::launch::async, &resource::run, currentResource, currentJob);

				return future;
			}

		};

		struct assigner : std::binary_function < resource, job, bool>
		{
			typedef assigner type;
			bool operator() (resource &currentResource, const job &currentJob) const
			{
				return ((!currentResource.is_in_use()) && (currentJob.units_needed <= currentResource.units_available));
			}
		};
	}
}

#endif
