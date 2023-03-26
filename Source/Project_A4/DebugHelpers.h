#pragma once

#include "DrawDebugHelpers.h"

// LOGGING
// print string
// use TEXT("", %)
#define DebugLogRed(sec, ...) GEngine->AddOnScreenDebugMessage(-1, sec, FColor::Red, FString::Printf(__VA_ARGS__))

// print fstring
#define DebugLogFString(sec, fstring) DebugLogRed(sec, TEXT("%s"), *FString(fstring))


// DRAWING
// draw line
#define DrawLinePersistentRed(start, end) DrawDebugLine(GetWorld(), start, end, FColor::Red, true)