/*
 *  This file is part of SST/macroscale:
 *               The macroscale architecture simulator from the SST suite.
 *  Copyright (c) 2009 Sandia Corporation.
 *  This software is distributed under the BSD License.
 *  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
 *  the U.S. Government retains certain rights in this software.
 *  For more information, see the LICENSE file in the top
 *  SST/macroscale directory.
 */

#ifndef OTF2_TRACE_REPLAY_H_
#define OTF2_TRACE_REPLAY_H_

#include <otf2/otf2.h>
#include <string>

#include <sstmac/software/process/app.h>
#include <sumi-mpi/mpi_api.h>
#include <sprockit/sim_parameters.h>
#include <sprockit/keyword_registration.h>

#include "callqueue.h"
#include "structures.h"

RegisterKeywords(
    "otf2_timescale",
    "otf2_terminate_percent",
    "otf2_print_progress",
    "otf2_metafile",
    "otf2_print_mpi_calls",
    "otf2_print_trace_events",
    "otf2_print_time_deltas"
);

class OTF2TraceReplayApp;

SpktRegister("otf2_trace_replay_app", sstmac::sw::app, OTF2TraceReplayApp,
             "application for parsing and simulating OTF2 traces");

using namespace sstmac::hw;
using namespace std;

class OTF2TraceReplayApp : public sstmac::sw::app {
public:
    OTF2TraceReplayApp(sprockit::sim_parameters* params, sstmac::sw::software_id sid,
                          sstmac::sw::operating_system* os);

    sumi::mpi_api* GetMpi();
    CallQueue& GetCallQueue();
    bool PrintTraceEvents();
    bool PrintMpiCalls();
    bool PrintTimeDeltas();

    virtual void skeleton_main();

    void StartMpi(const sstmac::timestamp);
    void EndMpi(const sstmac::timestamp);

    int rank = -1;
    long total_events = 0;

    OTF2_ClockProperties otf2_clock_properties;
	vector<string> otf2_string_table;
	vector<OTF2_Region> otf2_regions;
	vector<OTF2_Callpath> otf2_callpaths;
	vector<OTF2_Group> otf2_groups;
	vector<OTF2_Comm> otf2_comms;
	unordered_map<OTF2_StringRef, int> otf2_mpi_call_map;

	~OTF2TraceReplayApp() throw()	{ }

private:
    OTF2_Reader* initialize_event_reader();
    void initiate_trace_replay(OTF2_Reader*);
    void verify_replay_success();

private:
    CallQueue call_queue_;

    sstmac::timestamp compute_time;

    bool initialized_ = false;
    sumi::mpi_api* mpi_;

    double timescale_;
    double terminate_percent_;
    bool print_progress_;
    bool print_mpi_calls_;
	bool print_trace_events_;
	bool print_time_deltas_;
    string metafile_;
};

#endif /* OTF2_TRACE_REPLAY_H_ */
