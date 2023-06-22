#ifndef Protocol_Client_Friends_hpp__
#define Protocol_Client_Friends_hpp__

#include "Common.h"

namespace Battlenet::Client::Friends {
    struct FriendsListNotify5 {
        BSN::Array<Battlenet::Friends::FriendshipUpdate5, 64, 7> Friends;
        BSN::Optional<bool> IsEndOfList;
    };
}

#endif // Protocol_Client_Friends_hpp__
