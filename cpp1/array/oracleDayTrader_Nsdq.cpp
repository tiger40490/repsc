#include <iostream>
#include <vector>

/* Requirement: https://bintanvictor.wordpress.com/2018/04/07/best-day-trading-play-in-hindsight-nasdaq/
Strategy: every time we see a downturn, we sell (every upturn, we buy). If the actions vector starts with a sell, then prepend with a buy at the first point. If the actions vector ends with a buy, then append a sell at the last point.
*/