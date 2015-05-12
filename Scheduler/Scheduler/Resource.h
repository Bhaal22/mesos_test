#ifndef __RESOURCE_H
#define __RESOURCE_H

#include <chrono>
#include <thread>

namespace scheduler
{
	struct resource
	{
		int index;
		int units_available;

		resource(int index, int units_available)
			: index(index), units_available(units_available)
		{ }
	};

	struct job
	{
		int index;
		int units_needed;
		int time_step;

		job(int index, int units_needed, int time_step)
			: index(index), units_needed(units_needed), time_step(time_step)
		{}

		void compute()
		{
			std::this_thread::sleep_for(std::chrono::seconds(units_needed));
		}
	};
}

#endif
