#include "Game/SpaceGame.h"


int main(int argc, char* argv[]) {

    // Get current directory path
    std::cout << "Directory Operations:\n";
    std::cout << "Current directory: " << piMath::file::GetCurrentDirectory() << "\n";

    // Set current directory path (current path + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    piMath::file::SetCurrentDirectory("Assets");
    std::cout << "New directory: " << piMath::file::GetCurrentDirectory() << "\n\n";

    // Get filenames in the current directory
    std::cout << "Files in Directory:\n";
    auto filenames = piMath::file::GetFilesInDirectory(piMath::file::GetCurrentDirectory());
    for (const auto& filename : filenames) {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // Get filename (filename.extension) only
    if (!filenames.empty()) {
        std::cout << "Path Analysis:\n";
        std::string filename = piMath::file::GetFilename(filenames[0]);
        std::cout << "Filename only: " << filename << "\n";

        // Get extension only
        std::string ext = piMath::file::GetExtension(filenames[0]);
        std::cout << "Extension: " << ext << "\n\n";
    }

    // Read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    bool success = piMath::file::ReadTextFile("test.txt", str);
    if (success) {
        std::cout << "Contents of test.txt:\n";
        std::cout << str << "\n";
    }
    else {
        std::cout << "Failed to read test.txt\n";
    }

    std::cout << "Integer Functions:\n";

    //make pointers here
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();

    //initialize stuff here
    
	piMath::GetEngine().Initialize();
	game->Initialize();

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<piMath::Texture> texture = std::make_shared<piMath::Texture>();
    texture->Load("tristonface.jpg", piMath::GetEngine().GetRenderer());

    SDL_Event e;
    bool quit = false;
    float rotate = 0;

    // add sounds before the loop begins


	piMath::GetEngine().GetAudio().addSound("bass.wav", "bass");
    piMath::GetEngine().GetAudio().addSound("snare.wav", "snare");
    piMath::GetEngine().GetAudio().addSound("clap.wav", "clap");
    piMath::GetEngine().GetAudio().addSound("close-hat.wav", "close-hat");
    piMath::GetEngine().GetAudio().addSound("open-hat.wav", "open-hat");
   
    piMath::GetEngine().GetAudio().playSound("Wisteria");
    
    auto texture1 = piMath::Resources().Get<piMath::Texture>("tristonface.jpg", piMath::GetEngine().GetRenderer());


    //MAIN LOOP
    while (!quit) {
        
		piMath::GetEngine().Update();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            if (piMath::GetEngine().GetInput().getKeyPressed(SDL_SCANCODE_ESCAPE)) {
                quit = true;
            }
        }
        
        // draw stuff
        piMath::GetEngine().GetRenderer().SetColor(0.0f, 0.0f, 0.0f); // Set background color to black
        piMath::GetEngine().GetRenderer().Clear();
        game->Update(piMath::GetEngine().GetTime().GetDeltaTime());
		game->Draw(piMath::GetEngine().GetRenderer());        
       
        piMath::GetEngine().GetRenderer().Present();
    }

	game->Shutdown();
    game.release();
    piMath::GetEngine().Shutdown();
    return 0;
}