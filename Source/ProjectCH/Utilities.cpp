#include "Utilities.h"

FVector VectorUtils::Truncate(FVector vector, float maximum) {
	float i = maximum / vector.Size();
	i = i < 1.0f ? i : 1.0f;
	return vector * i;
}