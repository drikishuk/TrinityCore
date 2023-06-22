#ifndef Battlenet_Regulator_hpp__
#define Battlenet_Regulator_hpp__

#include "BSN/Choice.hpp"

namespace Battlenet::Regulator {
    using Cost = uint32;
    using CostRefundRate = uint32;

    enum class Enum {
        None = 0,
        LeakyBucket = 1
    };

    struct LeakyBucketParams final {
        Battlenet::Regulator::Cost Threshold = 0;
        Battlenet::Regulator::CostRefundRate Rate = 0;
    };

    namespace Info {
        struct None final { };

        struct LeakyBucket final {
            LeakyBucketParams Params = { };
        };
    }

    using Choice = BSN::Choice::Choice<Enum, 1, BSN::Choice::Of<Enum::None, Info::None>, BSN::Choice::Of<Enum::LeakyBucket, Info::LeakyBucket>>;
}

#endif // Battlenet_Regulator_hpp__
