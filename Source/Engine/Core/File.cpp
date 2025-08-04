#include "File.h"



namespace piMath::file {
    std::string GetCurrentDirectory() {
        std::error_code ec;
        auto path = std::filesystem::current_path(ec);
        return ec ? std::string{} : path.string();
    }

    bool SetCurrentDirectory(const std::string& path) {
        std::error_code ec;
        std::filesystem::current_path(path, ec);
        return !ec;
    }

    std::string GetExtension(const std::string& path) {
        std::filesystem::path p(path);
        return p.extension().string();
    }

    std::string GetFilename(const std::string& path) {
        std::filesystem::path p(path);
        return p.filename().string();
    }

    bool Exists(const std::string& path) {
        std::error_code ec;
        bool result = std::filesystem::exists(path, ec);

        return !ec && result;
    }

    std::vector<std::string> GetFilesInDirectory(const std::string& path) {
        std::vector<std::string> files;
        std::error_code ec;

        auto iter = std::filesystem::directory_iterator(path, ec);
        if (ec) return files; // return empty vector on error

        for (const auto& entry : iter) {
            if (entry.is_regular_file(ec) && !ec) {
                files.push_back(entry.path().string());
            }
        }

        return files;
    }

    std::vector<std::string> GetDirectoriesIn(const std::string& path) {
        std::vector<std::string> directories;
        std::error_code ec;

        auto iter = std::filesystem::directory_iterator(path, ec);
        if (ec) return directories; // return empty vector on error

        for (const auto& entry : iter) {
            if (entry.is_directory(ec) && !ec) {
                directories.push_back(entry.path().string());
            }
        }

        return directories;
    }

    bool ReadTextFile(const std::string& path, std::string& content) {
        std::ifstream file(path);
        if (!file.is_open()) {
            return false;
        }

        // read entire file into string
        std::stringstream buffer;
        // look at link on how-to read entire file into stringstream and convert buffer to string 
        buffer << file.rdbuf();
        content = buffer.str();

            return true;
    }

    bool WriteTextFile(const std::string& path, const std::string& content, bool append) {
        std::ios::openmode mode = append ? std::ios::app : std::ios::out;
        std::ofstream file(path, mode);
        if (!file.is_open()) {
            return false;
        }

        file << content;

            return true;
    }
}
