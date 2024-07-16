#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
//#include <gdk/x11/gdkx.h>

class MainWindow : public Gtk::Window {
	protected:
		void on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item);
		void on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item);

		Gtk::Box mainbox;
		Gtk::Box modlist_box;
		Gtk::Label modlist_heading;
		Gtk::ScrolledWindow modlist_scrollwindow;
		Gtk::ListView modlist_view;

		Glib::RefPtr<Gtk::StringList> modlist_names;
	public:
		MainWindow();
};

#endif