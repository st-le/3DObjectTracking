#include <filesystem/filesystem.h>
#include <m3t/generator.h>
#include <m3t/tracker.h>


int main(int argc, char* argv[]) {

    const std::filesystem::path configfile_path{
        "../../data/rooster/config.yaml"};

    std::shared_ptr<m3t::Tracker> tracker_ptr;
    if (!GenerateConfiguredTracker(configfile_path, &tracker_ptr)) 
    {
        std::cout << "Tracker configure not generated" << std::endl;
        return -1;
    }
    if (!tracker_ptr->SetUp()) 
    {
        std::cout << "Tracker not set up" << std::endl;
        return -1;
    }

    // Search required bodies
    std::shared_ptr<m3t::Body> rooster_body_ptr{};
    for (const auto& body_ptr: tracker_ptr->body_ptrs()) {
        if (body_ptr->name() == "rooster") rooster_body_ptr = body_ptr;
    }
    if (!rooster_body_ptr) {
        std::cout << "Body not found" << std::endl;
        return -1;
    }

    // Setup and run tracker
    if (!tracker_ptr->SetUp()) 
    {
        std::cout << "Tracker not set up" << std::endl;
        return -1;
    }
    if (!tracker_ptr->RunTrackerProcess(true, false)) {
        std::cout << "Tracker not run" << std::endl;
        return 0;
    }
    return 0;
}