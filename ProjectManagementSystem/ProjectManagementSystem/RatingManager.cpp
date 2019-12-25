#include "RatingManager.h"
#include "UserClass.h"

RatingManager::RatingManager() {

	collectRating(0);

}
float RatingManager::getRating() {

	float count;
	int sum = 0;
	for (int i = 0; i < rating.size(); i++)
		sum += rating[i];
	count = (float)sum / (rating.size() - 1);
	if (rating.size() - 1 == 0)
		return 0.0;
	else
		return count;

}
void RatingManager::collectRating(float newRating) {

	rating.push_back(newRating);

}