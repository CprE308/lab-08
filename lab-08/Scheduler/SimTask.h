/*
 * SimTask.h
 *
 *  Created on: Mar 9, 2016
 *      Author: vens
 */

#ifndef SIMTASK_H_
#define SIMTASK_H_

#include <string>

#include "Task/Task.h"
#include "libjson/json.h"
#include "libwavedrom/wavedrom.hpp"
#include "Task/Context.h"




class SimTask : public Task {
public:

	enum State
	{
		INIT,
		NOT_ARRIVED,
		READY,
		RUNNING,
		BLOCKED,
		FINISHED
	};

	SimTask(json_value * task, wavedrom::Group * wave_grp);
	virtual ~SimTask();

	unsigned long GetArrivalTime();

	bool operator < (const SimTask&);

	//void OnReady(unsigned long sys_time);
	//void OnBlock(unsigned long sys_time);
	void OnRunTick(unsigned long sys_time);
	bool IsFinished();

	// From Context
	/// This is called by the scheduler when this task will be given time on the processor
	virtual void SwapIn(unsigned long sys_time);
	/// This is called by the scheduler when this task is being taken out of the processor
	virtual void SwapOut(unsigned long sys_time);

	void OnStartTick(unsigned long sys_time);
	void OnSysTick(unsigned long sys_time);
	void OnEndTick(unsigned long sys_time);

private:
	int priority;
	unsigned long next_arrival_time;
	unsigned long deadline;
	unsigned long times[20];
	int times_index;
	int num_runs;
	Task * task;
	std::string name;

	enum State state;
	enum State last_state;

	bool remove_flag;

	wavedrom::Signal* wave;
};


#endif /* SIMTASK_H_ */
