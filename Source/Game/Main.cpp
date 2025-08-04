
#include <Core/Random.h>
#include <Renderer/Renderer.h>
#include <Math/Math.h>
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Core/Time.h>
#include <Input/InputSystem.h>
#include <Audio/AudioSystem.h>
#include <Renderer/Model.h>
#include <EngineGame/Actor.h>
#include "EngineGame/Scene.h"
#include "Game/Player.h" 
#include "Game/SpaceGame.h"
#include "Renderer/Font.h"
#include "Engine.h"
#include "Renderer/Text.h"
#include "Core/File.h"
#include "Renderer/ParticleSystem.h"

#include <memory>
#include <random>
#include <vector>

#include <iostream>



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
    std::cout << "getInt(): " << piMath::Random::getInt() << "\n";
    std::cout << "getInt(): " << piMath::Random::getInt() << "\n";
    std::cout << "getInt(10): " << piMath::Random::getInt(10) << "\n";
    std::cout << "getInt(10): " << piMath::Random::getInt(10) << "\n";
    std::cout << "getInt(5, 15): " << piMath::Random::getInt(5, 15) << "\n";
    std::cout << "getInt(5, 15): " << piMath::Random::getInt(5, 15) << "\n";
    std::cout << "getInt(-10, 10): " << piMath::Random::getInt(-10, 10) << "\n\n";

    // Test getReal() variants with float
    std::cout << "Float Functions:\n";
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "getReal<float>(): " << piMath::Random::getReal<float>() << "\n";
    std::cout << "getReal<float>(): " << piMath::Random::getReal<float>() << "\n";
    std::cout << "getReal<float>(5.0f): " << piMath::Random::getReal<float>(5.0f) << "\n";
    std::cout << "getReal<float>(2.5f, 7.5f): " << piMath::Random::getReal<float>(2.5f, 7.5f) << "\n";
    std::cout << "getReal<float>(-1.0f, 1.0f): " << piMath::Random::getReal<float>(-1.0f, 1.0f) << "\n\n";

    // Test getReal() variants with double
    std::cout << "Double Functions:\n";
    std::cout << std::setprecision(10);
    std::cout << "getReal<double>(): " << piMath::Random::getReal<double>() << "\n";
    std::cout << "getReal<double>(100.0): " << piMath::Random::getReal<double>(100.0) << "\n";
    std::cout << "getReal<double>(0.0, 2.0): " << piMath::Random::getReal<double>(0.0, 2.0) << "\n\n";

    // Test getBool()
    std::cout << "Boolean Functions:\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << "getBool(): " << std::boolalpha << piMath::Random::getBool() << "\n";
    }
    std::cout << "\n";

    //make pointers here
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();

    //initialize stuff here
    
	piMath::GetEngine().Initialize();
	game->Initialize();

    SDL_Event e;
    bool quit = false;

    // add sounds before the loop begins


	piMath::GetEngine().GetAudio().addSound("bass.wav", "bass");
    piMath::GetEngine().GetAudio().addSound("snare.wav", "snare");
    piMath::GetEngine().GetAudio().addSound("clap.wav", "clap");
    piMath::GetEngine().GetAudio().addSound("close-hat.wav", "close-hat");
    piMath::GetEngine().GetAudio().addSound("open-hat.wav", "open-hat");
    
    piMath::GetEngine().GetAudio().playSound("Wisteria");

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