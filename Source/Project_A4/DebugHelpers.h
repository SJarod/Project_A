#pragma once

#include "DrawDebugHelpers.h"

// print string
// use TEXT("", %)
#define DebugLogRed(sec, ...) GEngine->AddOnScreenDebugMessage(-1, sec, FColor::Red, FString::Printf(__VA_ARGS__))

// draw line
#define DrawLinePersistentRed(start, end) DrawDebugLine(GetWorld(), start, end, FColor::Red, true)