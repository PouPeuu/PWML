#include "MainWindow.h"
#include "Mods.h"

int main(int argc, char *argv[]) {
	std::filesystem::current_path(Utils::get_executable_dir());
	
	auto app = Gtk::Application::create("com.poupeuu.pwml");
	return app->make_window_and_run<MainWindow>(argc, argv);
}
