//
// Copyright (c) 2016 Markus Jung, Institute of Telematics,
//                                 Karlsruhe Institute of Technology
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "MatlabScheduler.h"
#include <cassert>
#include <errno.h>
#include <mclmcrrt.h>

Register_Class(MatlabScheduler);


MatlabScheduler::MatlabScheduler() {

}

MatlabScheduler::~MatlabScheduler() {

}

void MatlabScheduler::startMatlabRuntime() {
    if (!initialized) {
        // Initialize the MATLAB Runtime
        EV << "Initializing MATLAB Runtime" << endl;
        mclmcrInitialize();

        const char *args[] = { "-nodisplay", "-nosplash", "-nojvm" };

        // Set up the application state for the MATLAB Runtime instance created in the application.
        if (!mclInitializeApplication(args, 3)) {
            const char * const err = mclGetLastErrorMessage();

            EV_FATAL << "could not initialize the matlab application properly: "
                    << err << endl;
            EV << "could not initialize the matlab application properly: "
                    << err << endl;

            throw cRuntimeError("initializeApplication failed");
        }

        initialized = true;
    }
}

void MatlabScheduler::lifecycleEvent(SimulationLifecycleEventType eventType, cObject *details) {
    switch (eventType) {
    case LF_ON_SHUTDOWN:
        if (initialized) {
            // Release all state and resources used by the MATLAB Runtime for the application
            mclTerminateApplication();
            EV << "Terminating MATLAB Runtime" << endl;
        }

        initialized = false;
        break;
    default:
        break;
    }

    this->cSequentialScheduler::lifecycleEvent(eventType, details);
}
