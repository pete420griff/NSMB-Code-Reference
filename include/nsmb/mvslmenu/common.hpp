#pragma once
#include "nitro_if.hpp"


struct NicknameInfo
{
    u8 pad;
    u8 length;
    u16 chars[10];
};