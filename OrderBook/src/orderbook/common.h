#pragma once

#include <utility>
#include <vector>

enum TICK_COLUMN { TC_TYPE, TC_SIDE, TC_QUANTITY, TC_PRICE, TC_ID, TC_TIMESTAMP };
#define TICK_COLUMN_SIZE 6


using PriceQuantity		= std::pair<int, int>;
using PriceQuantityVec	= std::vector < std::pair<int, int> >;
using BidAsk			= std::pair< PriceQuantityVec, PriceQuantityVec >;