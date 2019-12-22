// RatingManager header file

#pragma once
#ifndef RATINGMANAGER_H
#define RATINGMANAGER_H

class RatingManager {
private:
	std::vector<float> rating;
public:
	RatingManager();
	float getRating();
	void collectRating(float newRating);
};

#endif // !RATINGMANAGER_H
