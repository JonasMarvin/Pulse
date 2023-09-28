#include "pch.h"

#include "Pulse/Modules/Input/Platform/Windows/WindowsInputModuleImpl.h"

#include "Pulse/Modules/ModuleManager.h"
#include "Pulse/Events/Events.h"
#include "Pulse/Modules/Window/WindowModule.h"

namespace Pulse::Modules::Windows {

	void WindowsInputModuleImpl::Initialize() {
		window_ = static_cast<GLFWwindow*>(ModuleManager::GetInstance().GetModule<WindowModule>()->GetNativeWindow());

		glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			Events::Input::KeyEvent->Trigger(static_cast<Input::KeyCode>(key), static_cast<Input::InputAction>(action));
		});

		glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
			Events::Input::MouseEvent->Trigger(static_cast<Input::MouseCode>(button), static_cast<Input::InputAction>(action));
		});

		glfwSetScrollCallback(window_, [](GLFWwindow* window, double xOffset, double yOffset) {
			Events::Input::ScrollEvent->Trigger(xOffset, yOffset);
		});

		glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xPos, double yPos) {
			Events::Input::MouseMovedEvent->Trigger(xPos, yPos);
		});

		glfwSetCharCallback(window_, [](GLFWwindow* window, unsigned int character) {
			Events::Input::CharEvent->Trigger(character);
		});
	}

	void WindowsInputModuleImpl::Shutdown() {
		glfwSetKeyCallback(window_, nullptr);
		glfwSetMouseButtonCallback(window_, nullptr);
		glfwSetScrollCallback(window_, nullptr);
		glfwSetCursorPosCallback(window_, nullptr);
		glfwSetCharCallback(window_, nullptr);
	}

	bool WindowsInputModuleImpl::IsKeyPressed(const Pulse::Input::KeyCode keyCode) {
		return glfwGetKey(window_, static_cast<int32_t>(keyCode)) == GLFW_PRESS;
	}

	bool WindowsInputModuleImpl::IsMouseButtonPressed(const Pulse::Input::MouseCode mouseCode) {
		return glfwGetMouseButton(window_, static_cast<int32_t>(mouseCode)) == GLFW_PRESS;
	}

	float WindowsInputModuleImpl::GetMouseX() {
		return GetMousePosition().first;
	}

	float WindowsInputModuleImpl::GetMouseY() {
		return GetMousePosition().second;
	}

	std::pair<float, float> WindowsInputModuleImpl::GetMousePosition() {
		double mouseX, mouseY;
		glfwGetCursorPos(window_, &mouseX, &mouseY);
		return std::pair<float, float>(static_cast<float>(mouseX), static_cast<float>(mouseY));
	}

	bool WindowsInputModuleImpl::IsGamepadConnected(Pulse::Input::JoystickCode joystickCode) {
		return glfwJoystickIsGamepad(static_cast<int32_t>(joystickCode));
	}

	bool WindowsInputModuleImpl::IsGamepadButtonPressed(Pulse::Input::GamepadButtonCode gamepadButtonCode, Pulse::Input::JoystickCode joystickCode) {
		if (glfwGetGamepadState(static_cast<int32_t>(joystickCode), &gamepadStates_[static_cast<uint32_t>(joystickCode)])) {
			return gamepadStates_[static_cast<uint32_t>(joystickCode)].buttons[static_cast<int32_t>(gamepadButtonCode)] == GLFW_PRESS;
		}
		return false;
	}

	bool WindowsInputModuleImpl::GetGamepadRightAxis(float& x, float& y, Pulse::Input::JoystickCode joystickCode) {
		if (glfwGetGamepadState(static_cast<int32_t>(joystickCode), &gamepadStates_[static_cast<uint32_t>(joystickCode)])) {
			x = gamepadStates_[static_cast<uint32_t>(joystickCode)].axes[static_cast<uint32_t>(Pulse::Input::GamepadAxisCode::RightX)];
			y = gamepadStates_[static_cast<uint32_t>(joystickCode)].axes[static_cast<uint32_t>(Pulse::Input::GamepadAxisCode::RightY)];
			return true;
		}
		return false;
	}

	bool WindowsInputModuleImpl::GetGamepadRightAxisX(float& x, Pulse::Input::JoystickCode joystickCode) {
		if (glfwGetGamepadState(static_cast<int32_t>(joystickCode), &gamepadStates_[static_cast<uint32_t>(joystickCode)])) {
			x = gamepadStates_[static_cast<uint32_t>(joystickCode)].axes[static_cast<uint32_t>(Pulse::Input::GamepadAxisCode::RightX)];
			return true;
		}
		return false;
	}

	bool WindowsInputModuleImpl::GetGamepadRightAxisY(float& y, Pulse::Input::JoystickCode joystickCode) {
		if (glfwGetGamepadState(static_cast<int32_t>(joystickCode), &gamepadStates_[static_cast<uint32_t>(joystickCode)])) {
			y = gamepadStates_[static_cast<uint32_t>(joystickCode)].axes[static_cast<uint32_t>(Pulse::Input::GamepadAxisCode::RightY)];
			return true;
		}
		return false;
	}

	bool WindowsInputModuleImpl::GetGamepadLeftAxis(float& x, float& y, Pulse::Input::JoystickCode joystickCode) {
		if (glfwGetGamepadState(static_cast<int32_t>(joystickCode), &gamepadStates_[static_cast<uint32_t>(joystickCode)])) {
			x = gamepadStates_[static_cast<uint32_t>(joystickCode)].axes[static_cast<uint32_t>(Pulse::Input::GamepadAxisCode::LeftX)];
			y = gamepadStates_[static_cast<uint32_t>(joystickCode)].axes[static_cast<uint32_t>(Pulse::Input::GamepadAxisCode::LeftY)];
			return true;
		}
		return false;
	}

	bool WindowsInputModuleImpl::GetGamepadLeftAxisX(float& x, Pulse::Input::JoystickCode joystickCode) {
		if (glfwGetGamepadState(static_cast<int32_t>(joystickCode), &gamepadStates_[static_cast<uint32_t>(joystickCode)])) {
			x = gamepadStates_[static_cast<uint32_t>(joystickCode)].axes[static_cast<uint32_t>(Pulse::Input::GamepadAxisCode::LeftX)];
			return true;
		}
		return false;
	}

	bool WindowsInputModuleImpl::GetGamepadLeftAxisY(float& y, Pulse::Input::JoystickCode joystickCode) {
		if (glfwGetGamepadState(static_cast<int32_t>(joystickCode), &gamepadStates_[static_cast<uint32_t>(joystickCode)])) {
			y = gamepadStates_[static_cast<uint32_t>(joystickCode)].axes[static_cast<uint32_t>(Pulse::Input::GamepadAxisCode::LeftY)];
			return true;
		}
		return false;
	}

	bool WindowsInputModuleImpl::GetGamepadRightTrigger(float& value, Pulse::Input::JoystickCode joystickCode) {
		if (glfwGetGamepadState(static_cast<int32_t>(joystickCode), &gamepadStates_[static_cast<uint32_t>(joystickCode)])) {
			value = gamepadStates_[static_cast<uint32_t>(joystickCode)].axes[static_cast<uint32_t>(Pulse::Input::GamepadAxisCode::RightTrigger)];
			return true;
		}
		return false;
	}

	bool WindowsInputModuleImpl::GetGamepadLeftTrigger(float& value, Pulse::Input::JoystickCode joystickCode) {
		if (glfwGetGamepadState(static_cast<int32_t>(joystickCode), &gamepadStates_[static_cast<uint32_t>(joystickCode)])) {
			value = gamepadStates_[static_cast<uint32_t>(joystickCode)].axes[static_cast<uint32_t>(Pulse::Input::GamepadAxisCode::LeftTrigger)];
			return true;
		}
		return false;
	}

} // namespace Pulse::Modules::Windows