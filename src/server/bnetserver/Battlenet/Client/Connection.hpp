#ifndef Battlenet_Client_Connection_hpp__
#define Battlenet_Client_Connection_hpp__

#include "Battlenet/Regulator.hpp"

namespace Battlenet::Client::Connection {
    struct Nul final { }; // 'Nul'

    struct Boom final { // 'Boom'
        Battlenet::Error::Code Error = 0;
    };

    struct RegulatorUpdate final { // 'RgUp'
        Battlenet::Regulator::Info::Choice Info = { };
    };

    struct ServerVersion final { // 'SVer'
        Battlenet::Server::Version Version = { };
    };

    struct STUNServers final { // 'Stun'
        Battlenet::Client::AddressPort Server[2] = { };
    };

    struct EnableEncryption final { }; // 'EEnc'

    struct LogoutRequest final { }; // 'LOut'

    struct DisconnectRequest final { // 'DDis'
        Battlenet::Error::Code Error = 0;
        Battlenet::Time::Tick Time = 0;
    };

    struct SecurityBreachReport final { // 'BRpt'
        int32 BreachCode = 0;
        int32 CheckValue = 0;
    };

    namespace ClosingReason {
        enum class Enum : uint8 {
            PACKET_TOO_LARGE          = 1,
            PACKET_CORRUPT            = 2,
            PACKET_INVALID            = 3,
            PACKET_INCORRECT          = 4,
            HEADER_CORRUPT            = 5,
            HEADER_IGNORED            = 6,
            HEADER_INCORRECT          = 7,
            PACKET_REJECTED           = 8,
            CHANNEL_UNHANDLED         = 9,
            COMMAND_UNHANDLED         = 10,
            COMMAND_BAD_PERMISSIONS   = 11,
            DIRECT_CALL               = 12,
            TIMEOUT                   = 13,
        };
    }

    using PacketData = BSN::Blob<128, 8>;

    struct ConnectionClosing final { // 'ClCn'
        BSN::Optional<Battlenet::Header> Header;
        Battlenet::Client::Connection::ClosingReason::Enum ClosingReason;
        Battlenet::Client::Connection::PacketData BadData;
        Battlenet::PacketInfoList Packets;
        Battlenet::Time::Tick Now;
    };
}

#endif // Battlenet_Client_Connection_hpp__
