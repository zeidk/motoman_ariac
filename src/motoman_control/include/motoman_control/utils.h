#ifndef UTILS_H
#define UTILS_H

#include <string>

	class utils
	{
	private:
		std::string gripper_control_host = "optimus.el.nist.gov";
		int gripper_control_port = 1234;
		std::string vision_system_host = "agility.el.nist.gov";
		int vision_system_port = 5002;

	public:
		std::string get_gripper_control_host(){return gripper_control_host;}
		int get_gripper_control_port(){return gripper_control_port;}
		std::string get_vision_system_host(){return vision_system_host;}
		int get_vision_system_port(){return vision_system_port;}
	};

#endif /* UTILS_H */