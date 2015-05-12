#ifndef __RESOURCE_H
#define __RESOURCE_H

#include <chrono>
#include <thread>

namespace scheduler
{
	struct job
	{
		int index;
		int units_needed;
		int time_step;

		job(int index, int units_needed, int time_step)
			: index(index), units_needed(units_needed), time_step(time_step)
		{}

		void compute() const
		{
			std::cout << "Starting job#" << index << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(units_needed));
			std::cout << "job#" << index << " finished" << std::endl;

		}
	};

	struct resource
	{
	public:
		int index;
		int units_available;
	private:
		bool used;
		std::shared_ptr<std::mutex> _mutex;
	public:


		resource(int index, int units_available)
			: index(index), units_available(units_available), used(false), _mutex(new std::mutex())
		{ 
		}

		resource(const resource &res)
			: index(res.index), units_available(res.units_available), used(res.used), _mutex(res._mutex)
		{ }

		bool is_in_use()
		{
			std::lock_guard<std::mutex> lock(*_mutex);
			return this->used;
		}

		void set_in_use(bool use)
		{
			std::lock_guard<std::mutex> lock(*_mutex);
			this->used = use;
		}

		void run(const job &currentJob)
		{
			currentJob.compute();
			set_in_use(false);
		}
	};
}

#endif
