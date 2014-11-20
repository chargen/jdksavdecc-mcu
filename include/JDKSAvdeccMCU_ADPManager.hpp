/*
  Copyright (c) 2014, J.D. Koftinoff Software, Ltd.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

   3. Neither the name of J.D. Koftinoff Software, Ltd. nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

#include "JDKSAvdeccMCU_World.hpp"
#include "JDKSAvdeccMCU_RawSocket.hpp"
#include "JDKSAvdeccMCU_Helpers.hpp"
#include "JDKSAvdeccMCU_Frame.hpp"

#include "JDKSAvdeccMCU_Handler.hpp"

namespace JDKSAvdeccMCU
{

class ADPManager : public Handler
{
  public:
    /**
     * @brief ADPManager constructor
     *
     * @param net The RawSocket to use
     *
     * @param entity_id The Entity's entity_id - See IEEE Std 1722.1-2013 Clause
     * 6.2.1.8
     *
     * @param entity_model_id The Entity's entity_model_id - See IEEE Std
     * 1722.1-2013 Clause 6.2.1.9
     *
     * @param entity_capabilities The Entity's entity_capabilities - See IEEE
     * Std 1722.1-2013 Clause 6.2.1.10
     *
     * @param controller_capabilities The Entity's controller_capabilities - See
     * IEEE Std 1722.1-2013 Clause 6.2.1.15
     *
     * @param valid_time_in_seconds The valid_time for the announcements - See
     * IEEE Std 1722.1-2013 Clause 6.2.1.6
     *
     * @param talker_stream_sources The number of stream sources - See IEEE Std
     * 1722.1-2013 Clause 6.2.1.11
     *
     * @param talker_capabilites The talker capabilities - See IEEE Std
     * 1722.1-2013 Clause 6.2.1.12
     *
     * @param listener_stream_sinks The number of stream sinks - See IEEE Std
     * 1722.1-2013 Clause 6.2.1.13
     *
     * @param listener_capabilities The listener capabilities - See IEEE Std
     * 1722.1-2013 Clause 6.2.1.14
     */
    ADPManager( RawSocket &net,
                Eui64 const &entity_id,
                Eui64 const &entity_model_id,
                uint32_t entity_capabilities,
                uint32_t controller_capabilities,
                uint16_t valid_time_in_seconds,
                uint16_t talker_stream_sources = 0,
                uint16_t talker_capabilities = 0,
                uint16_t listener_stream_sinks = 0,
                uint16_t listener_capabilites = 0 );

    /**
     * @brief tick is called periodically and will call sendADP() when necessary
     * @param timestamp The current time in milliseconds
     */
    virtual void tick( jdksavdecc_timestamp_in_milliseconds timestamp );

    /**
     * @brief receivedPDU is called to handle any incoming ADPDU.
     * @param frame Reference to the incoming frame
     * @return true if handled
     */
    virtual bool receivedPDU( Frame &frame );

    /**
     * @brief receivedEntityAvailable is called when any ENTITY_AVAILABLE ADP
     * message is received. The default implementation does nothing.
     * @param header The parsed ADPDU common control header
     * @param frame The reference to the entire received ethernet frame
     */
    virtual void receivedEntityAvailable(
        jdksavdecc_adpdu_common_control_header const &header, Frame &frame )
    {
        (void)frame;
        (void)header;
    }

    /**
     * @brief receivedEntityDeparting is called when any ENTITY_DEPARTING ADP
     * message is received. The default implementation does nothing.
     * @param header The parsed ADPDU common control header
     * @param frame The reference to the entire received ethernet frame
     */
    virtual void receivedEntityDeparting(
        jdksavdecc_adpdu_common_control_header const &header, Frame &frame )
    {
        (void)frame;
        (void)header;
    }

    /**
     * @brief sendADP Formulates the next ADPDU ENTITY_AVAILABLE message and
     * sends it
     */
    void sendADP();

    /**
     * @brief getRawSocket gets the raw socket which is used
     * @return Reference to the RawSocket
     */
    RawSocket &getRawSocket() { return m_net; }

    /**
     * @brief getEntityID is called to get the AVDECC Entity's entity_id as
     * defined by IEEE Std 1722.1-2013 Clause 6.2.1.8
     * @return The Entity's entity_id as a Eui64
     */
    Eui64 const &getEntityID() const { return m_entity_id; }

    /**
     * @brief getEntityModelID is called to get the AVDECC Enity Model ID for
     * this entity as defined by IEEE Std 1722.1-2013 Clause 6.2.1.9
     * @return The Entity's entity_model_id as a Eui64
     */
    Eui64 const &getEntityModelID() const { return m_entity_model_id; }

    /**
     * @brief getEntityCapabilities is called to get the Entity's
     * entity_capabilities, as defined in IEEE Std 1722.1-2013 Clause 6.2.1.10
     * @return The 32 bit value
     */
    uint32_t getEntityCapabilities() const { return m_entity_capabilities; }

    /**
     * @brief getControllerCapabilities is called to get the Entity's
     * controller_capabilites, as defined in IEEE Std 1722.1-2013 Clause
     * 6.2.1.15
     * @return The 32 bit value
     */
    uint32_t getControllerCapabilities() const
    {
        return m_controller_capabilities;
    }

    /**
     * @brief getValidTimeInSeconds is called to get the Entity's valid_time, as
     * defined in IEEE Std 1722.1-2013 Clause 6.2.1.6
     * @return
     */
    uint16_t getValidTimeInSeconds() const { return m_valid_time_in_seconds; }

    /**
     * @brief getAvailableIndex is called to get the current available_index
     * value, as defined in IEEE Std 1722.1-2013 Clause 6.2.1.16
     * @return
     */
    uint32_t getAvailableIndex() const { return m_available_index; }

    void triggerSend();

    void setGPTPGrandMasterID( Eui64 const &new_gm );

  protected:
    RawSocket &m_net;
    Eui64 m_entity_id;
    Eui64 m_entity_model_id;
    uint32_t m_entity_capabilities;
    uint32_t m_controller_capabilities;
    uint16_t m_valid_time_in_seconds;
    uint16_t m_talker_stream_sources;
    uint16_t m_talker_capabilities;
    uint16_t m_listener_stream_sinks;
    uint16_t m_listener_capabilities;
    uint32_t m_available_index;
    jdksavdecc_timestamp_in_milliseconds m_last_send_time_in_millis;
    jdksavdecc_timestamp_in_milliseconds m_trigger_send_time;
    bool m_trigger_send;
    Eui64 m_gptp_grandmaster_id;
};
}
