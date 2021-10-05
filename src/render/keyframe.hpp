#pragma once

#include <render/jointTransform.hpp>

#include <map>
#include <string>

class Keyframe {
public:
	float time_stamp;
	std::map<std::string, JointTransform*> pose;

	Keyframe(float time_stamp, std::map<std::string, JointTransform*> joint_key_frames) {
		this->time_stamp = time_stamp;
		this->pose = joint_key_frames;
	}

	float get_time_stamp() {
		return this->time_stamp;
	}

	std::map<std::string, JointTransform*> get_joint_keyframes() {
		return this->pose;
	}
};