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

#include "JDKSAvdeccMCU/World.hpp"
#include "JDKSAvdeccMCU/RawSocket.hpp"

namespace JDKSAvdeccMCU
{

class HandlerGroup;

///
/// \brief The Handler class
///
/// Abstract base class for classes that need to be notified
/// of time traversal and received PDU's
///
class Handler
{
  public:
    ///
    /// \brief ~Handler Virtual destructor
    ///
    virtual ~Handler();

    ///
    /// \brief tick Notification of time passage
    /// \param timestamp the current monotonic time in milleconds
    ///
    virtual void tick( jdksavdecc_timestamp_in_milliseconds timestamp );

    ///
    /// \brief receivedPDU Notification of received raw PDU.
    /// \param incoming_socket The socket that the frame was received on
    /// \param frame reference to received Frame object which is mutable
    /// \return true if the message was handled
    ///
    virtual bool receivedPDU( RawSocket *incoming_socket, Frame &frame );

    ///
    /// \brief addToHandlerGroup Register with HandlerGroup
    /// \param group HandlerGroup to add to
    ///
    virtual void addToHandlerGroup( HandlerGroup &group );
};
}
