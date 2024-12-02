#pragma once

#include "resource.h"
#include "map.h"
#include "object.h"
#include <memory>

std::unique_ptr<Map_Area>map_area;
std::unique_ptr<OBject>object;

bool gameStarted = false; // 게임 시작 여부
HWND hStartButton;       // 시작 버튼 핸들
bool pause = false;