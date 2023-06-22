#ifndef Battlenet_Client_Chat_hpp__
#define Battlenet_Client_Chat_hpp__

#include "Battlenet/Client/Defines.hpp"
#include "Battlenet/Chat.hpp"

namespace Battlenet::Client::Chat {
    struct Whisper { }; // 'Whsp'

    struct WhisperSend final : Whisper {
        Battlenet::Client::Defines::PlayerTarget Target;
        Battlenet::Chat::Line Body;
    };

    struct WhisperRecv final : Whisper {
        Battlenet::Toon::FullName Sender;
        Battlenet::Chat::Line Body;
    };

    struct WhisperEcho { }; // 'WhEc'

    struct WhisperEchoSend final : WhisperEcho {
        Battlenet::Client::Defines::PlayerTarget Target;
        Battlenet::Chat::Line Body;
    };

    struct WhisperEchoRecv final : WhisperEcho {
        Battlenet::Toon::FullName Sender;
        Battlenet::Chat::Line Body;
    };

    struct WhisperUndeliverable final { // 'WUnd'
        Battlenet::Client::Defines::PlayerTarget Target;
        Battlenet::Error::Code Reason;
    };

    struct GameDataRecv final { // 'GdRv'
        Battlenet::Client::Defines::PlayerTarget Sender;
        Battlenet::Chat::GameData Body;
    };

    struct GameDataSendRequest final { // 'GdSq'

    };

    struct GameDataSendResponse final { // 'GdSr'
        Battlenet::Token Token;
        Battlenet::Error::Code Result;
    };

    struct JoinRequest2 final { // 'CJoi'
        Battlenet::Token Token;
        Battlenet::Conference::LocatorKey::Choice Key;
    };

    struct JoinNotify2 final { // 'CJoi'
        BSN::Optional<Battlenet::Token> Token;
        Battlenet::Chat::JoinNotifyResult2 Result;
    };

    struct InviteFailed final { // 'InvF'
        Battlenet::Chat::ClientChannelIndex ChannelIndex;
        Battlenet::Token Token;
        Battlenet::Error::Code Reason;
    };

    struct InviteNotify final { // 'InvN'
        Battlenet::Chat::ClientChannelIndex ChannelIndex;
        Battlenet::PresenceId InviterPresence;
        Battlenet::Chat::ChannelType2::Enum ChannelType;
    };

    struct InviteCanceled final { // 'InvC'
        Battlenet::Chat::ClientChannelIndex ChannelIndex;
        Battlenet::Error::Code Reason;
    };

    struct MembershipChangeNotify final { // 'CMem'
        bool EndOfInitial;
        Battlenet::Chat::ClientChannelIndex ChannelIndex;
        Battlenet::Chat::MembershipChangeList Changes;
    };

    struct Message { }; // 'CMsg'

    struct MessageRecv final : Message {
        Battlenet::Chat::ClientChannelIndex ChannelIndex;
        Battlenet::Chat::MemberHandle MemberHandle;
        Battlenet::Chat::Line Body;
    };

    struct MessageUndeliverable final { // 'CUnd'
        Battlenet::Chat::ClientChannelIndex ChannelIndex;
        Battlenet::Error::Code Reason;
    };

    struct MessageBlocked final { // 'MsBl'
        Battlenet::Chat::ClientChannelIndex ChannelIndex;
        Battlenet::Chat::MemberHandle MemberHandle;
    };

    struct DatagramConnectionUpdate final { // 'CDgm'
        Battlenet::Client::Defines::PlayerTarget Target;
        Battlenet::Chat::DatagramConnectionInfo Info;
    };

    struct SystemMessage final { // 'CSys'
        Battlenet::Chat::SystemMessage Message;
    };

    struct CategoryDescriptions final { // 'Dsc1'
        Battlenet::Conference::CategoryDescriptionList List;
        bool IsLast;
    };

    struct ConferenceDescriptions final { // 'Dsc2'
        Battlenet::Conference::FullConferenceDescriptionList List;
        bool IsLast;
    };

    struct ConferenceMemberCounts final { // 'Cnts'
        Battlenet::Conference::MembershipInfoList List;
        bool IsLast;
        BSN::Optional<Battlenet::Time::Seconds> Time;
    };

    struct ModifyChannelListResponse2 final { // 'MLRs'
        Battlenet::Token Token;

        struct Result {
            enum class Enum {
                Success = 0,
                Failure = 1
            };

            using Success = Battlenet::Time::Seconds;
            using Failure = Battlenet::Error::Code;

            using Choice = BSN::Choice::Choice<Enum, 1, BSN::Choice::Of<Enum::Success, Success>, BSN::Choice::Of<Enum::Failure, Failure>>;
        };

        Result::Choice Result;
    };

    struct ConfigChanged final { // 'CnfC'
        Battlenet::Chat::ClientChannelIndex ChannelIndex;
        Battlenet::Conference::ConferenceConfiguration Config;
    };

    struct GetMemberCount { }; // 'MCnt'

    struct GetMemberCountResponse final : GetMemberCount { // 'MCnt'
        Battlenet::Conference::PrivateName Name;
        Battlenet::Conference::MembershipCount Count;
    };
}

#endif // Battlenet_Client_Chat_hpp__
