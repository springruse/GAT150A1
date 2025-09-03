#include "Game/SpaceGame.h"
#include "Platformer/PlatformerGame.h"
int main(int argc, char* argv[]) {

    // Get current directory path
    std::cout << "Directory Operations:\n";
    std::cout << "Current directory: " << claw::file::GetCurrentDirectory() << "\n";

    // Set current directory path (current path + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    claw::file::SetCurrentDirectory("Assets/Platformer");
    std::cout << "New directory: " << claw::file::GetCurrentDirectory() << "\n\n";

    //make pointers here
    std::unique_ptr<PlatformerGame> game = std::make_unique<PlatformerGame>();

    //initialize stuff here

	claw::GetEngine().Initialize();
	game->Initialize();


    SDL_Event e;
    bool quit = false;
    float rotate = 0;

    // add sounds before the loop begins

    // claw::GetEngine().GetAudio().playSound("Wisteria");
    
    //auto texture1 = claw::Resources().Get<claw::Texture>("tristonface.jpg", claw::GetEngine().GetRenderer());


    //MAIN LOOP
    while (!quit) {
        
		claw::GetEngine().Update();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            if (claw::GetEngine().GetInput().getKeyPressed(SDL_SCANCODE_P)) {
                quit = true;
            }
        }
        
        // draw stuff
        claw::GetEngine().GetRenderer().SetColor(0.0f, 0.0f, 0.0f); // Set background color to black
        claw::GetEngine().GetRenderer().Clear();
        game->Update(claw::GetEngine().GetTime().GetDeltaTime());
		game->Draw(claw::GetEngine().GetRenderer());        
       
        claw::GetEngine().GetRenderer().Present();
    }

	game->Shutdown();
    game.release();
    claw::GetEngine().Shutdown();
    return 0;
}