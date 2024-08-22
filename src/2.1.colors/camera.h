# pragma once;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	Camera(const glm::vec3& cameraPosition, const glm::vec3& cameraTarget, const glm::vec3& upDirection);
	void move_front();
	void move_back();
	void move_right();
	void move_left();
	void move_down();
	void move_up();
	void set_speed(const float& speed);
	void change_direction(const float& deltaX, const float& deltaY);
	const glm::vec3& get_front_dir();
	const glm::vec3& get_camera_pos();
	const glm::mat4& get_look_at();

private:
	float speed = 0.05f;
	float yaw = 0, pitch = 0;

	glm::vec3 moveUpDirection;
	glm::vec3 moveRightDirection;
	glm::vec3 moveFrontDirection;

	glm::vec3 cameraPosition;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirecion;
	glm::vec3 upDirection;
	glm::vec3 rightDirection;
	glm::vec3 frontDirection;
};