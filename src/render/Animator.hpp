#pragma once

#include <render/joint.hpp>
#include <render/keyframe.hpp>
#include <render/animation.hpp>
#include <render/jointTransform.hpp>

class AnimatedModel;

class Animator {
public:
	AnimatedModel* entity;

	Animation* current_animation;
	float animation_time;

	Animator(AnimatedModel* entity);

	void do_animation(Animation* animation);
	void update();
	void increase_animation_time(float dt);
	std::map<std::string, glm::mat4> calculate_current_animation_pose();
	void apply_pose_to_joints(std::map<std::string, glm::mat4> current_pose, Joint* joint, glm::mat4 parent_transform);
	Keyframe* get_previous_and_next_frames();
	float calculate_progression(Keyframe* previous_frame, Keyframe* next_frame);
	std::map<std::string, glm::mat4> interpolate_poses(Keyframe* previous_frame, Keyframe* next_frame, float progression);
};