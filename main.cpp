#include "MainWindow.h"

int main(int argc, char *argv[]) {
	auto app = Gtk::Application::create("com.poupeuu.pwml");
	return app->make_window_and_run<MainWindow>(argc, argv);
}
