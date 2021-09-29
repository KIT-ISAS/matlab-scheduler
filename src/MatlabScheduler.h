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

#ifndef MATLABSCHEDULER_H_
#define MATLABSCHEDULER_H_

#include <stdint.h>
#include <omnetpp.h>
#include <omnetpp/cobject.h>
#include <omnetpp/cscheduler.h>

using namespace omnetpp;

class MatlabScheduler : public cSequentialScheduler {

  public:
    MatlabScheduler();
    virtual ~MatlabScheduler();

    void startMatlabRuntime();

  protected:
    /**
     * A cISimulationLifecycleListener method.
     */
    virtual void lifecycleEvent(SimulationLifecycleEventType eventType, cObject *details) override;

  private:
    bool initialized = false;
};

#endif /* MATLABSCHEDULER_H_ */
