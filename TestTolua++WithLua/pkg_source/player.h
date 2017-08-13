#ifndef PLAYER_H
#define PLAYER_H

#include "common_def.h"

//tolua_begin
class Player
{
//tolua_end
public:
    Player();
    Player(const AccountId &id, const std::string &name);
    ~Player();

public:
    AccountId GetPlayerId();//tolua_export
    std::string GetNickName();//tolua_export
    void SetNickName(const std::string &name);//tolua_export

protected:
    AccountId player_id;
    std::string nick_name;
//tolua_begin
};
//tolua_end

#endif
