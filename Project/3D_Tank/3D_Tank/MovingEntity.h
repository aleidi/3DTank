#pragma once

#include <cassert>

#include "Vector3.h"
#include "BaseGameEntity.h"

class MovingEntity : public BaseGameEntity {
public:
	MovingEntity(Vector3 position,
		double radius,
		Vector3 velocity,
		double max_speed,
		Vector3 heading,
		double mass,
		Vector3 scale,
		double turn_rate,
		double max_force) :BaseGameEntity(BaseGameEntity::getNextValidID()),
		m_vHeading(heading),
		m_vVelocity(velocity),
		m_dMass(mass),
		//m_vSide(m_vHeading.Perp()),
		m_dMaxSpeed(max_speed),
		m_dMaxTurnRate(turn_rate),
		m_dMaxForce(max_force)
	{
		m_vPosition = position;
		m_dBoundingRadius = radius;
		m_vScale = scale;
	}

	virtual ~MovingEntity(){}

	//accessors
	Vector3  Velocity()const { return m_vVelocity; }
	void      SetVelocity(const Vector3& NewVel) { m_vVelocity = NewVel; }

	double    Mass()const { return m_dMass; }

	Vector3  Side()const { return m_vSide; }

	double    MaxSpeed()const { return m_dMaxSpeed; }
	void      SetMaxSpeed(double new_speed) { m_dMaxSpeed = new_speed; }

	double    MaxForce()const { return m_dMaxForce; }
	void      SetMaxForce(double mf) { m_dMaxForce = mf; }
	/*
	bool      IsSpeedMaxedOut()const { return m_dMaxSpeed * m_dMaxSpeed >= m_vVelocity.LengthSq(); }
	double    Speed()const { return m_vVelocity.Length(); }
	double    SpeedSq()const { return m_vVelocity.LengthSq(); }
	*/
	Vector3  Heading()const { return m_vHeading; }
	void      SetHeading(Vector3 new_heading);
	bool      RotateHeadingToFacePosition(Vector3 target);

	double    MaxTurnRate()const { return m_dMaxTurnRate; }
	void      SetMaxTurnRate(double val) { m_dMaxTurnRate = val; }

protected:
	Vector3 m_vVelocity;
	Vector3 m_vHeading; // a normalized vector pointing in the direction the entity is heading
	Vector3 m_vSide; // a vector perpendicular to the heading vector

	double m_dMass;
	double m_dMaxSpeed;
	double m_dMaxForce;
	double m_dMaxTurnRate;
};



/*
//--------------------------- RotateHeadingToFacePosition ---------------------
//
//  given a target position, this method rotates the entity's heading and
//  side vectors by an amount not greater than m_dMaxTurnRate until it
//  directly faces the target.
//
//  returns true when the heading is facing in the desired direction
//-----------------------------------------------------------------------------
inline bool MovingEntity::RotateHeadingToFacePosition(Vector3 target)
{
	// Vector3 toTarget = Vec2DNormalize(target - m_vPosition);

	// double dot = m_vHeading.Dot(toTarget);

	//some compilers lose acurracy so the value is clamped to ensure it
	//remains valid for the acos
	// Clamp(dot, -1, 1);

	//first determine the angle between the heading vector and the target
	double angle = acos(dot);

	//return true if the player is facing the target
	if (angle < 0.00001) return true;

	//clamp the amount to turn to the max turn rate
	if (angle > m_dMaxTurnRate) angle = m_dMaxTurnRate;

	//The next few lines use a rotation matrix to rotate the player's heading
	//vector accordingly
	C2DMatrix RotationMatrix;

	//notice how the direction of rotation has to be determined when creating
	//the rotation matrix
	RotationMatrix.Rotate(angle * m_vHeading.Sign(toTarget));
	RotationMatrix.TransformVector2Ds(m_vHeading);
	RotationMatrix.TransformVector2Ds(m_vVelocity);

	//finally recreate m_vSide
	m_vSide = m_vHeading.Perp();

	return false;
}


//------------------------- SetHeading ----------------------------------------
//
//  first checks that the given heading is not a vector of zero length. If the
//  new heading is valid this fumction sets the entity's heading and side 
//  vectors accordingly
//-----------------------------------------------------------------------------
inline void MovingEntity::SetHeading(Vector2D new_heading)
{
	assert((new_heading.LengthSq() - 1.0) < 0.00001);

	m_vHeading = new_heading;

	//the side vector must always be perpendicular to the heading
	m_vSide = m_vHeading.Perp();
}
*/