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

#ifndef __OPENFLOW_RTSDNCONNECTIONGATEWAY_H_
#define __OPENFLOW_RTSDNCONNECTIONGATEWAY_H_


//CoRE4INET
#include "core4inet/applications/AS6802/CTApplicationBase.h"
#include <omnetpp.h>

using namespace omnetpp;

namespace ofp{

/**
 * Gateway between Ports and Switching Application.
 * @author Timo Häckel
 */
class RTSDNConnectionGateway : public virtual CoRE4INET::CTApplicationBase
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);


  private:
    /**
     * Buffer for outgoing AVB traffic.
     */
    cModule *_avbOutCTC = nullptr;
    /**
     * Buffer for outgoing BE traffic
     */
    cModule *_beBuffer = nullptr;

    /**
     * The index of this port.
     */
    int _portNo;
    /**
     * The number of ports on this switch
     */
    int _portCount;

    /**
     * @brief Handles outgoing messages and forwards them to the correct output module.
     * @param msg the message to forward.
     */
    void handleOutMessage(omnetpp::cMessage* msg);

    /**
     * @brief Handles messages for the switching engine and forwards them to the upperLayer module.
     * @param msg
     */
    void handleSwitchMessage(omnetpp::cMessage* msg);

    /**
     * Checks if the incoming message is an SRP message.
     * @param msg the message to check
     * @return true if SRP message.
     */
    bool isSRPMessage(omnetpp::cMessage* msg);

    /**
     * @brief handles SRP Messages and forwards them to the correct module.
     * @param msg srp message to forward.
     */
    void handleSRPMessage(omnetpp::cMessage* msg);
};

} /** end namespace ofp **/

#endif