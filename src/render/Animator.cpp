#include <render/Animator.hpp>

Animator::Animator(AnimatedModel* entity) {
	this->entity = entity;
}

void Animator::do_animation(Animation* animation) {
	this->animation_time = 0.0f;
	this->current_animation = animation;
}

void Animator::update() {
	if (current_animation == nullptr) {
		return;
	}

	increase_animation_time();
	std::map<std::string, glm::mat4> current_pose = calculate_current_animation_pose();
	apply_pose_to_joints(current_pose, entity->root_joint, glm::mat4());
}

void Animator::increase_animation_time(float dt) {
	this->animation_time += dt;
	if (this->animation_time > this->current_animation->get_length()) {
		this->animation_time -= this->current_animation->get_length();
	}
}

std::map<std::string, glm::mat4> Animator::calculate_current_animation_pose() {
	Keyframe[2] frames = get_previous_and_next_frames();
	float progression = calculate_progression(frames[0], frames[1]);
	return interpolate_poses(frames[0], frames[1], progression);
}

void Animator::apply_pose_to_joints(std::map<std::string, glm::mat4> current_pose, Joint* joint, glm::mat4 parent_transform) {
	glm::mat4 current_local_transform = current_pose[joint->name];
	glm::mat4 current_transform = parent_transform * current_local_transform;

	for (int i = 0; i < joint->children.size(); i ++) {
		apply_pose_to_joints(current_pose, joint->children[i], current_transform);
	}

	current_transform = current_transform * joint->inverse_bind_transform;
	joint->animated_transfrom = current_transform;
}

Keyframe* Animator::get_previous_and_next_frames() {
	std::vector<Keyframe*> all_frames = current_animation->get_key_frames();
	Keyframe* previous_frame = all_frames[0];
	Keyframe* next_frame = all_frames[0];
	for (int i = 1; i < all_frames.size(); i ++) {
		next_frame = all_frames[i];
		if (next_frame->get_time_stamp() > animation_time) {
			break;
		}
		previous_frame = all_frames[i];
	}

	return Keyframe[2] {previous_frame, next_frame};
}

float Animator::calculate_progression(Keyframe* previous_frame, Keyframe* next_frame) {
	float total_time = next_frame->get_time_stamp() - previous_frame->get_time_stamp();
	float current_time = animation_time - previous_frame->get_time_stamp();
	return current_time / total_time;
}

std::map<std::string, glm::mat4> Animator::interpolate_poses(Keyframe* previous_frame, Keyframe* next_frame, float progression) {
	std::map<std::string, glm::mat4> current_pose;
	std::map<std::string, JointTransform*> previous_keyframes = previous_frame->get_joint_keyframes();
	for (auto const& [key, val] : previous_keyframes) {
		JointTransform* previous_transform = val;
		JointTransform* next_transform = next_keyframes[key];
		JointTransform* current_transform = JointTransform.interpolate(previous_transform, next_transform, progression);
		current_pose[key] = current_transform->get_local_transform();
	}

	return current_pose;
}