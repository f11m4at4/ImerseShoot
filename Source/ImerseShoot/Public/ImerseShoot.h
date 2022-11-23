// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Shoot, Log, All);

#define CALLINFO (FString(__FUNCTION__) + TEXT(" : ") + FString::FromInt(__LINE__))
#define PRINT_CALLINFO() UE_LOG(Shoot, Warning, TEXT("%s"), *CALLINFO)

#define PRINTLOG(fmt, ...) UE_LOG(Shoot, Warning, TEXT("%s %s"), *CALLINFO, *FString::Printf(fmt, ##__VA_ARGS__))
