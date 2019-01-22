#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

//quat from euler angles - work with that later?
//q = qyaw qpitch qroll where:  (NOTE ORDER MATTERS)
//qroll = [cos(y / 2), (sin(y / 2), 0, 0)]
//	qpitch = [cos(q / 2), (0, sin(q / 2), 0)]
//	qyaw = [cos(f / 2), (0, 0, sin(f / 2)]

class TransformComponent : public Component
{

	const float moveStepsize = 0.01f;		// 4.0f / 1024.0f; // 0.004f;  accurate binary value
	const float rotateStepsize = 0.005f;		// 1.0f / 128.0f;	// 0.001f;

public:
	glm::vec3 m_position;
	glm::quat m_orientation;
	glm::vec3 m_scale;

	void OnUpdate(float dt) override{}
	void OnMessage(const std::string m) override
	{
		// e.g.	if (m == "rotateLeft")

		if (m == "rotateLeft")
		{
			yaw(rotateStepsize);		// anti clockwise
		}
		if (m == "rotateRight")
		{
			yaw(-rotateStepsize);
		}

		if (m == "rotateUp")
		{
			pitch(-rotateStepsize);		// anti clockwise
		}
		if (m == "rotateDown")
		{
			pitch(rotateStepsize);
		}
		if (m == "moveForward")
		{
			glm::vec3 v = glm::vec3(0, 0, -moveStepsize);
			translate(m_orientation * v);
		}
		if (m == "moveBackward")
		{
			glm::vec3 v = glm::vec3(0, 0, moveStepsize);
			translate(m_orientation * v);
		}

		if (m == "moveUp")
		{
			glm::vec3 v = glm::vec3(0, moveStepsize, 0); //smaller amount here
			translate(m_orientation * v);
		}
		if (m == "moveDown")
		{
			glm::vec3 v = glm::vec3(0, -moveStepsize, 0);
			translate(m_orientation * v);
		}
		if (m == "reset")
		{
			m_position = glm::vec3(0, 0, 0);
			m_orientation = glm::quat(1, 0, 0, 0);
		}

	}

	TransformComponent() : m_position(0), m_orientation(1,0,0,0), m_scale(1.0f) {}
	TransformComponent(const glm::vec3& pos) : m_position(pos), m_orientation(1, 0, 0, 0), m_scale(1.0f) {}
	TransformComponent(const glm::vec3& pos, const glm::quat& orient) : m_position(pos), m_orientation(orient), m_scale(1.0f) {}
	TransformComponent(const glm::vec3& pos, const glm::quat& orient, const glm::vec3& scale) : m_position(pos), m_orientation(orient), m_scale(scale) {}

	const glm::vec3& position() const { return m_position; }
	const glm::quat& orientation() const { return m_orientation; }
	const glm::vec3& scale() const { return m_scale; }

	glm::mat4 getModelMatrix()
	{
		glm::mat4 transMatrix = glm::translate(glm::mat4(1.0f), m_position);
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);
		glm::mat4 rotMatrix = glm::mat4_cast(m_orientation);
		return transMatrix * rotMatrix * scaleMatrix;
	}

	void translate(const glm::vec3 &v) 
	{
		m_position += v; 
	}
	void translate(float x, float y, float z) { m_position += glm::vec3(x, y, z); }

	// this is not used in steves pitch roll yaw calls
	void rotate(float angle, const glm::vec3 &axis) 
	{ 
		m_orientation *= glm::angleAxis(angle, m_orientation * axis); 

	}
	void rotate(float angle, float x, float y, float z) { 
		// show lecture
#if 1
		glm::vec3 anglesBefore = glm::eulerAngles(m_orientation); //pitch yaw roll

		// look at this
		m_orientation *= glm::angleAxis(angle, glm::vec3(x, y, z)); // *m_orientation);  //order altered - put back - PC makes no odds

		glm::vec3 anglesAfter = glm::eulerAngles(m_orientation); //pitch yaw roll

#else
		// this is steve's implementation
		m_orientation *= glm::angleAxis(angle, glm::vec3(x, y, z) * m_orientation);  //order altered - put back - PC makes no odds
#endif

	}

	void scaleUp(const glm::vec3 &v) { m_scale += v; }
	void scaleUp(float x, float y, float z) { m_scale += glm::vec3(x, y, z); }

	void yaw(float angle) { rotate(angle, 0.0f, 1.0f, 0.0f); }
	void pitch(float angle) { rotate(angle, 1.0f, 0.0f, 0.0f); }
	void roll(float angle) { rotate(angle, 0.0f, 0.0f, 1.0f); }


	glm::vec3 getEulerAngles()
	{
		return glm::eulerAngles(m_orientation); //pitch yaw roll
	}
};
