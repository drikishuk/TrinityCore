#ifndef Battlenet_DatagramConnection_hpp__
#define Battlenet_DatagramConnection_hpp__

namespace Battlenet::DatagramConnection {
    namespace ArbitrationNotify {
        enum class Enum {
            NONE           = 0, // 0x0
            ATTEMPTBEGIN   = 1, // 0x1
            ATTEMPTTIMEOUT = 2, // 0x2
            PACKETRECEIVED = 3, // 0x3
            FAILED         = 4, // 0x4
            STUNUPDATE     = 5, // 0x5
            ADDRESSCHANGED = 6, // 0x6
        };
    }

    namespace NATType {
        enum class Enum {
            UNKNOWN      = 0,
            OPEN         = 1,
            NAT          = 2,
            SYMMETRICNAT = 3
        };
    }

    using ConnectionToken = uint8;
    using ConnectAttemptToken = uint8;

    using InstanceCode = BSN::FourCC;
}

#endif // Battlenet_DatagramConnection_hpp__
