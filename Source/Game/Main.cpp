#include "Game/SpaceGame.h"


int main(int argc, char* argv[]) {

    // Get current directory path
    std::cout << "Directory Operations:\n";
    std::cout << "Current directory: " << claw::file::GetCurrentDirectory() << "\n";

    // Set current directory path (current path + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    claw::file::SetCurrentDirectory("Assets");
    std::cout << "New directory: " << claw::file::GetCurrentDirectory() << "\n\n";

    //// Get filenames in the current directory
    //std::cout << "Files in Directory:\n";
    //auto filenames = claw::file::GetFilesInDirectory(claw::file::GetCurrentDirectory());
    //for (const auto& filename : filenames) {
    //    std::cout << filename << "\n";
    //}
    //std::cout << "\n";

    // load the json data from a file
    std::string buffer;
    claw::file::ReadTextFile("json.txt", buffer);
    // show the contents of the json file (debug)
    std::cout << buffer << std::endl;

    // create json document from the json file contents
    rapidjson::Document document;
    claw::json::Load("json.txt", document);

    // read the age data from the json
    int age;
    claw::json::Read(document, "age", age);
    // show the age data
    std::cout << age << std::endl;

    // read/show the data from the json file
    std::string name;
    float speed;
    bool isAwake;
    claw::vec2 position;
    claw::vec3 color;

    // read the json data
    JSON_READ(document, name);
    JSON_READ(document, age);
    JSON_READ(document, speed);
    JSON_READ(document, isAwake);
    JSON_READ(document, position);
    JSON_READ(document, color);

    // show the data
    std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
    std::cout << position.x << " " << position.y << std::endl;
    std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;

    //make pointers here
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();

    //initialize stuff here

	claw::GetEngine().Initialize();
	game->Initialize();

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<claw::Texture> texture = std::make_shared<claw::Texture>();
    texture->Load("tristonface.jpg", claw::GetEngine().GetRenderer());

    SDL_Event e;
    bool quit = false;
    float rotate = 0;

    // add sounds before the loop begins


    claw::GetEngine().GetAudio().addSound("bass.wav", "bass");
    claw::GetEngine().GetAudio().addSound("snare.wav", "snare");
    claw::GetEngine().GetAudio().addSound("clap.wav", "clap");
    claw::GetEngine().GetAudio().addSound("close-hat.wav", "close-hat");
    claw::GetEngine().GetAudio().addSound("open-hat.wav", "open-hat");
   
    claw::GetEngine().GetAudio().playSound("Wisteria");
    
    auto texture1 = claw::Resources().Get<claw::Texture>("tristonface.jpg", claw::GetEngine().GetRenderer());


    //MAIN LOOP
    while (!quit) {
        
		claw::GetEngine().Update();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            if (claw::GetEngine().GetInput().getKeyPressed(SDL_SCANCODE_ESCAPE)) {
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