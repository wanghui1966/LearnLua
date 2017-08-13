#include "player.h"

Player::Player() : player_id(0)
{

}

Player::Player(const AccountId &id, const std::string &name) : player_id(id), nick_name(name)
{
    
}

Player::~Player()
{
    player_id = 0;
}

AccountId Player::GetPlayerId()
{
    return player_id;
}

std::string Player::GetNickName()
{
    return nick_name;
}

void Player::SetNickName(const std::string &name)
{
    nick_name = name;
}