
#ifndef _AI_H_
#define _AI_H_

#include "Rubic.h"
#include "AsciiOutput.h"
#include "TurnSequence.h"
#include "TurnSequences.h"
#include <map>

void animate(const Turnable &turns, Rubic &cube, AsciiOutput &output,
	     int sleep_time, bool reverse = false, bool mirror = false);
// defined in main

// these need the algorithms to be loaded in memory with correct names
void finish_phase(Rubic &cube, AsciiOutput &output, int sleep_time,
		  const std::map<string, TurnSequence> &memory,
		  const std::map<string, TurnSequences> &memory2);
void finish(Rubic &cube, AsciiOutput &output, int sleep_time,
	    const std::map<string, TurnSequence> &memory,
	    const std::map<string, TurnSequences> &memory2);

#endif
