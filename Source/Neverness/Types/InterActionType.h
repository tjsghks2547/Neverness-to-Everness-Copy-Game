#pragma once

#include "CoreMinimal.h"
#include "InterActionType.generated.h"

UENUM(BlueprintType)
enum class EInterActionType : uint8
{
	None UMETA(DisplayName = "None"),
	Dialog UMETA(DisplayName = "Dialog"),
	Chest UMETA(DisplayName = "Chest"),
	Item UMETA(DisplayName = "Item")


};