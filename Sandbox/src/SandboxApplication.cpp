#include <Pulse.h>

 class Sandbox : public Pulse::Application {
 public:
	 Sandbox() {
		
	 }

	 ~Sandbox() {
		 
	 }
 };

Pulse::Application* Pulse::CreateApplication() {
	return new Sandbox();
}