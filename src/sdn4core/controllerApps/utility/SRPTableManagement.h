//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
// c Timo Haeckel, for HAW Hamburg
// 

#ifndef OPENFLOW_REALTIME_CONTROLLERAPPS_SRPTABLEMANAGEMENT_H_
#define OPENFLOW_REALTIME_CONTROLLERAPPS_SRPTABLEMANAGEMENT_H_


#include <sdn4core/controller/avb/SRP/OF_CTRL_SRPTable.h>

//STD
#include <unordered_map>
#include <vector>
//inet
#include "inet/linklayer/common/MACAddress.h"
//CoRE4INET
//AUTO_GENERATED MESSAGES
#include "core4inet/linklayer/ethernet/avb/SRPFrame_m.h"
//openflow
#include "openflow/openflow/controller/Switch_Info.h"

namespace SDN4CoRE {

/**
 * Information how to forward AVB messages.
 */
typedef struct SRPForwardingInfo {
    int inPort;
    inet::MACAddress dest;
    uint16_t vlanID;
    uint8_t srClass;
    uint64_t streamID;
    std::vector<int> outports;
} SRPForwardingInfo_t;

/**
 * SRPTableManagement manages the SRPTable operations for the controller.
 * It holds one SRP table per switch.
 *
 * @author Timo Haeckel, for HAW Hamburg
 */
class SRPTableManagement {
public:
    SRPTableManagement() {

    }
    virtual ~SRPTableManagement() {

    }

    /**
     * Register a talker for a switch and inport.
     * @param swinfo            The switch recieving the talker advertise.
     * @param arrivalPort       The ingress port at the receiving switch.
     * @param talkerAdvertise   The original talker advertise message recieved in the switch.
     * @return                  true if the talker table has been updated.
     */
    virtual bool registerTalker(ofp::Switch_Info* swinfo, int arrivalPort,
            CoRE4INET::TalkerAdvertise* talkerAdvertise);

    /**
     * Register a listener for a switch and inport.
     * @param swinfo            The switch recieving the listener ready.
     * @param arrivalPort       The ingress port at the receiving switch.
     * @param listenerReady     The original listener ready message recieved in the switch.
     * @return                  true if the listener table has been updated.
     */
    virtual bool registerListener(ofp::Switch_Info* swinfo, int arrivalPort,
            CoRE4INET::ListenerReady* listenerReady);

    /**
     * Provides a forwarding information for AVBFrames according to the SRPTable of a switch and a stream.
     * @param swinfo        The switch handling the frame
     * @param streamID      The stream to be forwarded.
     * @param vlan_id       The VLAN ID of the frame
     * @return              SRPForwardingInfo_t containing all information to create a match.
     */
    virtual SRPForwardingInfo_t* getForwardingInfoForStreamID(
            ofp::Switch_Info* swinfo, uint64_t streamID, uint16_t vlan_id);

    /**
     * @brief creates an XML string with the contents of the SRP Table.
     * This string can be used to fill the SRP Table with importFromXML.
     * @return  returns the XML string
     */
    std::string exportToXML();

    /**
     * @brief Imports entries from an XMLdocument.
     * The root element needs to be <srpTable>
     * @param swinfo    the switch to be updated
     * @param xml   the xml document to import from.
     * @return  true if it was updated.
     */
    bool importFromXML(ofp::Switch_Info* swinfo, cXMLElement* xml);

    /**
     * @brief Module representing the srpTable
     */
    std::unordered_map<ofp::Switch_Info*, OF_CTRL_SRPTable*> _srpTable;
private:
    /**
     * Checks if a table exists for the switch or creates a new one.
     * @param swinfo    The switch to create a table for.
     * @return          The table of the switch for convenience.
     */
    OF_CTRL_SRPTable* checkOrCreateTable(ofp::Switch_Info* swinfo);
    /**
     * checks if a table for the switch exists.
     * @param swinfo    The switch to check the table for.
     * @return          true if a table already exists.
     */
    bool tableExistsForSwitch(ofp::Switch_Info* swinfo);
};

} /*end namespace SDN4CoRE*/

#endif /* OPENFLOW_REALTIME_CONTROLLERAPPS_SRPTABLEMANAGEMENT_H_ */
