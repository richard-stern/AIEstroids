#ifndef BASE_STATE_H
#define BASE_STATE_H

class StateMachine;
class Renderer2D;

class BaseState {
public:
	/// Constructor
	BaseState() {}
	/// Destructor
	~BaseState() {}

	/// This will be called when the state is entered
	void virtual Enter() = 0;
	/// This will be called each frame
	void virtual Update(float deltaTime, StateMachine* stateMachine) = 0;
	/// This will draw all the graphics for the menu
	void virtual Draw(Renderer2D* renderer) = 0;
	/// This will be called when the state is exited
	void virtual Exit() = 0;
};

#endif // BASE_STATE_H