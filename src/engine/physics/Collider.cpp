#include <src/engine/render/SolidMarchingSquares.hpp>
#include <glm/detail/func_matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <src/engine/util/KeyHandler.hpp>
#include <src/engine/Entity.hpp>
#include "Collider.hpp"
#include "RectangleCollider.hpp"
#include "GridCollider.hpp"
#include "PolygonCollider.hpp"
#include "MarchingSquaresCollider.hpp"

using std::vector;

const int Collider::LOW_ITERATIONS = 3, Collider::HIGH_ITERATIONS = 20;

std::pair<double, double> Collider::intersection(RectangleCollider &a, glm::mat4 &mA, RectangleCollider &b, glm::mat4 &mB)
{
	double aCoords[4][2], bCoords[4][2];
	a.getCoordinates(mA, aCoords);
	b.getCoordinates(mB, bCoords);

	double axes[4][2] = {
			{aCoords[0][0] - aCoords[1][0], aCoords[0][1] - aCoords[1][1]},
			{aCoords[1][0] - aCoords[2][0], aCoords[1][1] - aCoords[2][1]},
			{bCoords[0][0] - bCoords[1][0], bCoords[0][1] - bCoords[1][1]},
			{bCoords[1][0] - bCoords[2][0], bCoords[1][1] - bCoords[2][1]}
	};

	return intersection(aCoords, 4, bCoords, 4, axes, 4);
}

std::pair<double, double> Collider::intersection(RectangleCollider &a, glm::mat4 &mA, GridCollider &b, glm::mat4 &mB)
{
	std::pair<double, double> intersect;

	glm::mat4 adjust = glm::inverse(mB) * mA;
	glm::vec4 aBB = a.boundingBox(adjust);
	int minX = std::max(0, (int) ((aBB.x - b.startX) / b.cellWidth));
	int maxX = std::min(b.nx - 1, (int) ((aBB.z - b.startX) / b.cellWidth));
	int minY = std::max(0, (int) ((aBB.y - b.startY) / b.cellHeight));
	int maxY = std::min(b.ny - 1, (int) ((aBB.w - b.startX) / b.cellHeight));

	glm::mat4 correctedMatrix = mA;
	for(int i = minX; i <= maxX; i++) for(int j = minY; j <= maxY; j++) if(b.map[i][j])
			{
				RectangleCollider currentCollider(b.startX + b.cellWidth * i,
												  b.startY + b.cellHeight * j,
												  b.cellWidth, b.cellHeight);
				auto curIntersection = intersection(a, correctedMatrix, currentCollider, mB);
				intersect.first += curIntersection.first;
				intersect.second += curIntersection.second;
				correctedMatrix = glm::translate(glm::mat4(),
												 glm::vec3((float) curIntersection.first,
														   (float) curIntersection.second,
														   0.0f))
								  * correctedMatrix;
			}

	return intersect;
}

std::pair<double, double> Collider::intersection(Collider &a, glm::mat4 &mA, Collider &b, glm::mat4 &mB)
{
	glm::vec4 aBox = a.boundingBox(mA), bBox = b.boundingBox(mB);
	if(aBox.x > bBox.z || aBox.z < bBox.x || aBox.y > bBox.w || aBox.w < bBox.y) return std::make_pair(0.0, 0.0);

	if(a.getClassID() == RectangleCollider::CLASS_ID && b.getClassID() == RectangleCollider::CLASS_ID)
	{
		return intersection(static_cast<RectangleCollider &>(a), mA, static_cast<RectangleCollider &>(b), mB);
	}

	if(a.getClassID() == RectangleCollider::CLASS_ID && b.getClassID() == GridCollider::CLASS_ID)
	{
		return intersection(static_cast<RectangleCollider &>(a), mA, static_cast<GridCollider &>(b), mB);
	}

	if(a.getClassID() == RectangleCollider::CLASS_ID && b.getClassID() == PolygonCollider::CLASS_ID)
	{
		return intersection(static_cast<RectangleCollider &>(a), mA, static_cast<PolygonCollider &>(b), mB);
	}

	if(a.getClassID() == PolygonCollider::CLASS_ID && b.getClassID() == RectangleCollider::CLASS_ID)
	{
		return intersection(static_cast<PolygonCollider &>(a), mA, static_cast<RectangleCollider &>(b), mB);
	}

	if(a.getClassID() == PolygonCollider::CLASS_ID && b.getClassID() == PolygonCollider::CLASS_ID)
	{
		return intersection(static_cast<PolygonCollider &>(a), mA, static_cast<PolygonCollider &>(b), mB);
	}

	if(a.getClassID() == RectangleCollider::CLASS_ID && b.getClassID() == MarchingSquaresCollider::CLASS_ID)
	{
		return intersection(static_cast<RectangleCollider &>(a), mA, static_cast<MarchingSquaresCollider &>(b), mB);
	}

	if(a.getClassID() == PolygonCollider::CLASS_ID && b.getClassID() == MarchingSquaresCollider::CLASS_ID)
	{
		return intersection(static_cast<PolygonCollider &>(a), mA, static_cast<MarchingSquaresCollider &>(b), mB);
	}

	return std::make_pair(0.0, 0.0);
}

std::pair<double, double> Collider::intersection(Entity &a, Entity &b)
{
	return intersection(a.getCollider(), a.getTransform().getMatrix(), b.getCollider(), b.getTransform().getMatrix());
};

std::pair<double, double> Collider::intersection(RectangleCollider &a, glm::mat4 &mA, PolygonCollider &b, glm::mat4 &mB)
{
	int nb = b.points.size();
	double aCoords[4][2], bCoords[nb][2];
	a.getCoordinates(mA, aCoords);
	b.getCoordinates(mB, bCoords);

	double axes[nb + 2][2];
	axes[0][0] = {aCoords[0][0] - aCoords[1][0]};
	axes[0][1] = {aCoords[0][1] - aCoords[1][1]};
	axes[1][0] = {aCoords[1][0] - aCoords[2][0]};
	axes[1][1] = {aCoords[1][1] - aCoords[2][1]};

	for(int i = 0; i < nb - 1; i++)
	{
		axes[i + 2][0] = {bCoords[i][1] - bCoords[i + 1][1]};
		axes[i + 2][1] = {bCoords[i + 1][0] - bCoords[i][0]};
	}

	axes[nb + 1][0] = {bCoords[nb - 1][1] - bCoords[0][1]};
	axes[nb + 1][1] = {bCoords[0][0] - bCoords[nb - 1][0]};

	return intersection(aCoords, 4, bCoords, nb, axes, nb + 2);
}

std::pair<double, double> Collider::intersection(PolygonCollider &a, glm::mat4 &mA, RectangleCollider &b, glm::mat4 &mB)
{
	auto intersect = intersection(b, mB, a, mA);
	return std::make_pair(-intersect.first, -intersect.second);
}

std::pair<double, double> Collider::intersection(PolygonCollider &a, glm::mat4 &mA, PolygonCollider &b, glm::mat4 &mB)
{
	int na = a.points.size(), nb = b.points.size();
	double aCoords[na][2], bCoords[nb][2];
	a.getCoordinates(mA, aCoords);
	b.getCoordinates(mB, bCoords);

	double axes[na + nb][2];
	for(int i = 0; i < na - 1; i++)
	{
		axes[i][0] = {aCoords[i][1] - aCoords[i + 1][1]};
		axes[i][1] = {aCoords[i + 1][0] - aCoords[i][0]};
	}
	for(int i = 0; i < nb - 1; i++)
	{
		axes[i + na][0] = {bCoords[i][1] - bCoords[i + 1][1]};
		axes[i + na][1] = {bCoords[i + 1][0] - bCoords[i][0]};
	}
	axes[na - 1][0] = {aCoords[nb - 1][1] - aCoords[0][1]};
	axes[na - 1][1] = {aCoords[0][0] - aCoords[nb - 1][0]};
	axes[na + nb - 1][0] = {bCoords[nb - 1][1] - bCoords[0][1]};
	axes[na + nb - 1][1] = {bCoords[0][0] - bCoords[nb - 1][0]};

	return intersection(aCoords, na, bCoords, nb, axes, na + nb);
}

std::pair<double, double> Collider::intersection(double (*a)[2], int na,
												 double (*b)[2], int nb,
												 double (*axes)[2], int axesLength)
{
	double smallestLength = INFINITY;
	std::pair<double, double> smallestIntersection;

	for(int i = 0; i < axesLength; i++)
	{
		double length = std::sqrt(axes[i][0] * axes[i][0] + axes[i][1] * axes[i][1]);
		double axisX = axes[i][0] / length, axisY = axes[i][1] / length;
		double aMin = INFINITY, aMax = -INFINITY, bMin = INFINITY, bMax = -INFINITY;

		for(int j = 0; j < na; j++)
		{
			double aVal = axisX * a[j][0] + axisY * a[j][1];
			aMin = std::min(aMin, aVal);
			aMax = std::max(aMax, aVal);
		}

		for(int j = 0; j < nb; j++)
		{
			double bVal = axisX * b[j][0] + axisY * b[j][1];
			bMin = std::min(bMin, bVal);
			bMax = std::max(bMax, bVal);
		}

		if(aMin > bMax || aMax < bMin) return std::make_pair(0.0, 0.0);
		double length1 = aMax - bMin, length2 = bMax - aMin;
		if(length1 < smallestLength && length1 < length2)
		{
			smallestLength = length1;
			length1 = -length1;
			smallestIntersection.first = axisX * length1;
			smallestIntersection.second = axisY * length1;
		}
		else if(length2 < smallestLength)
		{
			smallestLength = length2;
			smallestIntersection.first = axisX * length2;
			smallestIntersection.second = axisY * length2;
		}
	}

	return smallestIntersection;
}

std::pair<double, double> Collider::intersection(RectangleCollider &a, glm::mat4 &mA, MarchingSquaresCollider &b, glm::mat4 &mB)
{
	std::pair<double, double> intersect;

	glm::mat4 adjust = glm::inverse(mB) * mA;
	glm::vec4 aBB = a.boundingBox(adjust);
	int minX = std::max(0, (int) ((aBB.x - b.startX) / b.cellWidth));
	int maxX = std::min(b.nx - 1, (int) ((aBB.z - b.startX) / b.cellWidth));
	int minY = std::max(0, (int) ((aBB.y - b.startY) / b.cellHeight));
	int maxY = std::min(b.ny - 1, (int) ((aBB.w - b.startX) / b.cellHeight));

	glm::mat4 correctedMatrix = mA;
	for(int i = minX; i <= maxX; i++) for(int j = minY; j <= maxY; j++) if(b.map[i][j])
			{
				vector<std::pair<float, float>> points;
				vector<std::pair<double, double>> &originalPoints = SolidMarchingSquares::partCoordinates[b.map[i][j]];

				if(originalPoints.size() == 6)
				{
					for(int k = 0; k < 3; k++)
					{
						points.push_back(std::make_pair((float) (b.startX + b.cellWidth * (originalPoints[k].first + i)),
														(float) (b.startY + b.cellHeight * (originalPoints[k].second + j))));
					}
					PolygonCollider firstCollider(points);
					auto firstIntersection = intersection(a, correctedMatrix, firstCollider, mB);
					intersect.first += firstIntersection.first;
					intersect.second += firstIntersection.second;
					correctedMatrix = glm::translate(glm::mat4(),
													 glm::vec3((float) firstIntersection.first,
															   (float) firstIntersection.second,
															   0.0f))
									  * correctedMatrix;

					points.clear();
					for(int k = 3; k < 6; k++)
					{
						points.push_back(std::make_pair((float) (b.startX + b.cellWidth * (originalPoints[k].first + i)),
														(float) (b.startY + b.cellHeight * (originalPoints[k].second + j))));
					}
					PolygonCollider secondCollider(points);
					auto secondIntersection = intersection(a, correctedMatrix, secondCollider, mB);
					intersect.first += secondIntersection.first;
					intersect.second += secondIntersection.second;
					correctedMatrix = glm::translate(glm::mat4(),
													 glm::vec3((float) secondIntersection.first,
															   (float) secondIntersection.second,
															   0.0f))
									  * correctedMatrix;
				}
				else
				{
					for(int k = 0; k < originalPoints.size(); k++)
					{
						points.push_back(std::make_pair((float) (b.startX + b.cellWidth * (originalPoints[k].first + i)),
														(float) (b.startY + b.cellHeight * (originalPoints[k].second + j))));
					}
					PolygonCollider currentCollider(points);
					auto curIntersection = intersection(a, correctedMatrix, currentCollider, mB);
					intersect.first += curIntersection.first;
					intersect.second += curIntersection.second;
					correctedMatrix = glm::translate(glm::mat4(),
													 glm::vec3((float) curIntersection.first,
															   (float) curIntersection.second,
															   0.0f))
									  * correctedMatrix;
				}
			}

	return intersect;
}

std::pair<double, double> Collider::intersection(PolygonCollider &a, glm::mat4 &mA, MarchingSquaresCollider &b, glm::mat4 &mB)
{
	std::pair<double, double> intersect;

	glm::mat4 adjust = glm::inverse(mB) * mA;
	glm::vec4 aBB = a.boundingBox(adjust);
	int minX = std::max(0, (int) ((aBB.x - b.startX) / b.cellWidth));
	int maxX = std::min(b.nx - 1, (int) ((aBB.z - b.startX) / b.cellWidth));
	int minY = std::max(0, (int) ((aBB.y - b.startY) / b.cellHeight));
	int maxY = std::min(b.ny - 1, (int) ((aBB.w - b.startX) / b.cellHeight));

	glm::mat4 correctedMatrix = mA;
	for(int i = minX; i <= maxX; i++) for(int j = minY; j <= maxY; j++) if(b.map[i][j])
			{
				vector<std::pair<float, float>> points;
				vector<std::pair<double, double>> &originalPoints = SolidMarchingSquares::partCoordinates[b.map[i][j]];

				if(originalPoints.size() == 6)
				{
					for(int k = 0; k < 3; k++)
					{
						points.push_back(std::make_pair((float) (b.startX + b.cellWidth * (originalPoints[k].first + i)),
														(float) (b.startY + b.cellHeight * (originalPoints[k].second + j))));
					}
					PolygonCollider firstCollider(points);
					auto firstIntersection = intersection(a, correctedMatrix, firstCollider, mB);
					intersect.first += firstIntersection.first;
					intersect.second += firstIntersection.second;
					correctedMatrix = glm::translate(glm::mat4(),
													 glm::vec3((float) firstIntersection.first,
															   (float) firstIntersection.second,
															   0.0f))
									  * correctedMatrix;

					points.clear();
					for(int k = 3; k < 6; k++)
					{
						points.push_back(std::make_pair((float) (b.startX + b.cellWidth * (originalPoints[k].first + i)),
														(float) (b.startY + b.cellHeight * (originalPoints[k].second + j))));
					}
					PolygonCollider secondCollider(points);
					auto secondIntersection = intersection(a, correctedMatrix, secondCollider, mB);
					intersect.first += secondIntersection.first;
					intersect.second += secondIntersection.second;
					correctedMatrix = glm::translate(glm::mat4(),
													 glm::vec3((float) secondIntersection.first,
															   (float) secondIntersection.second,
															   0.0f))
									  * correctedMatrix;
				}
				else
				{
					for(int k = 0; k < originalPoints.size(); k++)
					{
						points.push_back(std::make_pair((float) (b.startX + b.cellWidth * (originalPoints[k].first + i)),
														(float) (b.startY + b.cellHeight * (originalPoints[k].second + j))));
					}
					PolygonCollider currentCollider(points);
					auto curIntersection = intersection(a, correctedMatrix, currentCollider, mB);
					intersect.first += curIntersection.first;
					intersect.second += curIntersection.second;
					correctedMatrix = glm::translate(glm::mat4(),
													 glm::vec3((float) curIntersection.first,
															   (float) curIntersection.second,
															   0.0f))
									  * correctedMatrix;
				}
			}

	return intersect;
}
