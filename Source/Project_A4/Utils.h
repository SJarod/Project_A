#pragma once

// TIME
// get application time in seconds
#define GetTime() GetWorld()->GetTimeSeconds()

// get time since specified time stamp (x)
#define GetTimeSince(x) GetTime() - x


// COMPONENT
#define CreateComponent(componentType) CreateDefaultSubobject<componentType>(*FString(componentType::StaticClass()->GetName()))