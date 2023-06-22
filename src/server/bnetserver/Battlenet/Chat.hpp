#ifndef Battlenet_Chat_hpp__
#define Battlenet_Chat_hpp__

#include "Battlenet/Client.hpp"
#include "Battlenet/DatagramConnection.hpp"

namespace Battlenet::Chat {
    using Name = BSN::String<32, 7, 3>;
    using GameData = BSN::String<4095, 14>;

    using ClientChannelIndex = uint8;
    using ShardId = uint32;

    using MemberHandle = uint32;

    namespace ChatChannelType2 {
        enum class Enum {
            UNKNOWN = 0,
            NAMED   = 1,
            CONVO   = 2,
            PARTY   = 3,
            PUBLIC  = 4,
            CLUB    = 5,
        };
    };

    namespace MembershipChange {
        struct LeaveChannel final {
            Battlenet::Chat::MemberHandle MemberHandle;
            Battlenet::Error::Code Reason = 0;
        };

        struct JoinChannel final {
            Battlenet::Chat::MemberHandle MemberHandle;
            Battlenet::Presence::Id Id;
            // ... more
        };
    }

    struct DatagramConnectionInfo final {
        Battlenet::DatagramConnection::InstanceCode Instance;
        Battlenet::DatagramConnection::NATType::Enum NatType;
        Battlenet::Client::AddressPort AddressPort;
        Battlenet::Client::AddressPort BoundAddressPort;
        Battlenet::DatagramConnection::ArbitrationNotify::Enum ArbitrationNotify;
        Battlenet::DatagramConnection::ConnectionToken Token;
        Battlenet::DatagramConnection::ConnectAttemptToken ConnectAttemptToken;
    };

    struct SystemMessage final {
        Battlenet::Error::Code Body = 0;
        uint32 Argument = 0;
    };

    struct FullName final {
        Battlenet::Lease::Id Id;
        Battlenet::Lease::Name Name;
        BSN::Optional<ShardId> Shard;
    };

    using ClientChannelList = BSN::Array<FullName, 31, 5>;
}

#endif // Battlenet_Chat_hpp__
