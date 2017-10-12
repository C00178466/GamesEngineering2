#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <list>

using namespace std;

//Command Interface
class Command {
public:
	virtual ~Command() {}
	virtual void execute() = 0;

protected:
	Command() {}
};

//concrete classes
class JumpCommand : public Command
{
public:
	virtual void execute() { cout << "Jump" << endl; }
};

class FireCommand : public Command
{
public:
	virtual void execute() { cout << "Fire" << endl; }
};

class SwitchGunCommand : public Command
{
	virtual void execute() { cout << "Switch Gun" << endl; }
};

class CrouchCommand : public Command
{
	virtual void execute() { cout << "Crouch" << endl; }
};

class InputHandler
{
public:
	void handleInput(SDL_Event &event);
private:
	Command* buttonX_ = new JumpCommand();
	Command* buttonY_ = new FireCommand();
	Command* buttonA_ = new CrouchCommand();
	Command* buttonB_ = new SwitchGunCommand();
};

void InputHandler::handleInput(SDL_Event &event)
{
	if (event.key.keysym.sym == SDLK_x) buttonX_->execute();
	else if (event.key.keysym.sym == SDLK_y) buttonY_->execute();
	else if (event.key.keysym.sym == SDLK_a) buttonA_->execute();
	else if (event.key.keysym.sym == SDLK_b) buttonB_->execute();
}

class MacroCommand : public Command
{
public:
	MacroCommand() {}
	virtual ~MacroCommand() {}
	virtual void add(Command*);
	virtual void remove(Command*);
	virtual void execute();

	virtual void undo();
	virtual void redo();

private:
	list<Command*>* commands;
	list<Command*>* prevCommands;
};

void MacroCommand::execute()
{
	list<Command*>::iterator i;

	for (i = commands->begin(); i != commands->end(); i++)
	{
		Command *c = *i; //dereference iter so that c can see the command at i
		c->execute();
	}
}

void MacroCommand::add(Command* c) //adds command to the macro
{
	//commands->append(c);
	commands->push_back(c);
}

void MacroCommand::remove(Command* c) //removes command from the macro
{
	commands->remove(c);
}

void MacroCommand::undo()
{
	list<Command*>::iterator i = commands->begin();
	prevCommands->push_back(*i); //put the first element in commands into the prevCommands list

	commands->remove(*i);

	cout << endl;
	cout << "undo" << endl;
	cout << commands << endl;
}

void MacroCommand::redo()
{
	list<Command*>::iterator i = prevCommands->begin();
	commands->push_back(*i);

	prevCommands->remove(*i);

	cout << endl;
	cout << "redo" << endl;
	cout << commands << endl;
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("Lab 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 300, SDL_WINDOW_SHOWN);
	InputHandler* input = new InputHandler;
	MacroCommand* mac = new MacroCommand;
	bool isRunning = true;

	while (isRunning)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}

			switch (event.type)
			{
			case SDL_KEYDOWN:
				input->handleInput(event);

				if (event.key.keysym.sym == SDLK_u) //undo command
				{
					mac->undo();
				}
				if (event.key.keysym.sym == SDLK_r) //redo command
				{
					mac->redo();
				}
			}
		}
	}

	SDL_Quit();
	return 0;
	
}