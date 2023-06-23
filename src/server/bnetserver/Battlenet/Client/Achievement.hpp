#ifndef Battlenet_Client_Achievement_hpp__
#define Battlenet_Client_Achievement_hpp__

#include "Battlenet/Achievement.hpp"
#include "Battlenet/Profile.hpp"

namespace Battlenet::Client::Achievement {
    struct Data final {
        Battlenet::Profile::RecordAddress Address;
        Battlenet::Achievement::DataSegment Segment;
    };

    struct CriteriaFlush { };

    struct CriteriaFlushResponse final : CriteriaFlush {
        Battlenet::Token FlushToken;
        Battlenet::Error::Code Code;
    };

    struct AchievementHandleUpdate final {
        Battlenet::Achievement::ProgramHandleAggregation Info;
    };

    struct ChangeTrophyCaseResult final {
        Battlenet::Token Token;
        Battlenet::Error::Code Result;
    };

    struct ListenRequest final {
        Battlenet::Profile::RecordAddress Address;
        Battlenet::Achievement::ListenMode::Enum Mode;
        Battlenet::Achievement::ListenScope::Enum Scope;
    };

    struct CriteriaFlushRequest final : CriteriaFlush {
        Battlenet::Token FlushToken;
        Battlenet::Profile::RecordAddress Address;
        BSN::Array<Battlenet::Achievement::CriteriaUpdateRecord, 64, 7> Deltas;
    };
}

#endif // Battlenet_Client_Achievement_hpp__
