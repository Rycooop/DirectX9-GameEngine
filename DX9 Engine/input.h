#ifndef INPUT_CLASS
#define INPUT_CLASS


//Will be expanding to take mouse input

class EngineInput
{
public:
	EngineInput();

	bool Initialize();
	bool Cleanup();

	void keyDown(unsigned int key);
	void keyUp(unsigned int key);

	bool isKeyDown(unsigned int key);

private:
	int isActive;
	bool m_keys[256];
};

#endif