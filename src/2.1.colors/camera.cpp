# include "camera.h"

Camera::Camera(const glm::vec3& cameraPosition, const glm::vec3& cameraTarget,const glm::vec3& upDirection){
	this->cameraPosition = cameraPosition;
	this->cameraTarget = cameraTarget;
	this->upDirection = upDirection;

	moveUpDirection = upDirection;

	cameraDirecion = cameraTarget - cameraPosition;
	rightDirection = glm::normalize(glm::cross(upDirection, -cameraDirecion));
	frontDirection = glm::cross(upDirection, rightDirection);

	moveFrontDirection = frontDirection;
	moveRightDirection = rightDirection;
}

void Camera::move_front(){
	cameraPosition += speed * moveFrontDirection;
}

void Camera::move_back(){
	cameraPosition -= speed * moveFrontDirection;
}

void Camera::move_right() {
	cameraPosition += speed * moveRightDirection;
}

void Camera::move_left(){
	cameraPosition -= speed * moveRightDirection;
}

void Camera::move_down(){
	cameraPosition -= speed * moveUpDirection;
}

void Camera::move_up(){
	cameraPosition += speed * moveUpDirection;
}

void Camera::set_speed(const float& speed){
	this->speed = speed;
}

void Camera::change_direction(const float& deltaX, const float& deltaY){
	yaw += deltaX;
	pitch += deltaY;
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;
	
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = -cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	frontDirection = cameraDirecion = glm::normalize(front);

	front.x = sin(glm::radians(yaw));
	front.y = 0.0f;
	front.z = -cos(glm::radians(yaw));
	moveFrontDirection = front;
	moveRightDirection = glm::cross(moveFrontDirection, moveUpDirection);


	glm::vec3 up;
	up.x = -sin(glm::radians(pitch)) * sin(glm::radians(yaw));
	up.y = cos(glm::radians(pitch));
	up.z = sin(glm::radians(pitch)) * cos(glm::radians(yaw));
	upDirection = up;

	rightDirection = glm::normalize(glm::cross(upDirection, -cameraDirecion));
}

const glm::vec3& Camera::get_front_dir(){
	return frontDirection;
}

const glm::vec3& Camera::get_camera_pos(){
	return cameraPosition;
}

const glm::mat4& Camera::get_look_at(){
	glm::mat4 trans = glm::mat4(1.0f);
	trans[3][0] = -cameraPosition.x;
	trans[3][1] = -cameraPosition.y;
	trans[3][2] = -cameraPosition.z;

	glm::mat4 rotation = glm::mat4(1.0f);
	rotation[0][0] = rightDirection.x;
	rotation[1][0] = rightDirection.y;
	rotation[2][0] = rightDirection.z;

	rotation[0][1] = upDirection.x;
	rotation[1][1] = upDirection.y;
	rotation[2][1] = upDirection.z;

	rotation[0][2] = -cameraDirecion.x;
	rotation[1][2] = -cameraDirecion.y;
	rotation[2][2] = -cameraDirecion.z;

	return rotation * trans;
}
