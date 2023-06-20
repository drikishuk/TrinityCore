#ifndef Battlenet_Friends_hpp__
#define Battlenet_Friends_hpp__

namespace Battlenet::Friends {
    struct FriendContainer5 final {

    };

    using PriorFriendID = BSN::Choice::Choice<1, Battlenet::Account::Id, Battlenet::Toon::Handle>;

    struct FriendshipUpdate5 final {
        struct Remove {

        };

        using Update = BSN::Choice::Choice<1, FriendContainer5, Remove>;
    };
}

#endif // Battlenet_Friends_hpp__
