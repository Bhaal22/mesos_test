#ifndef __RESOURCE_H
#define __RESOURCE_H

namespace scheduler
{
	struct resource
	{
		int index;
		int units_available;
	};

	struct job
	{
		int index;
		int units_needed;
		int time_step;
	};
}

#endif