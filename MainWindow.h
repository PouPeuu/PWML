#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

class MainWindow : public Gtk::Window {
	protected:
		void on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item);
		void on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item);

		Gtk::Box mainbox;
		Gtk::Paned paned;
		
		Gtk::Box modlist_box;
		Gtk::Label modlist_heading;
		Gtk::ScrolledWindow modlist_scrollwindow;
		Gtk::ListView modlist_view;

		Gtk::Box alltheshit_box;
		Gtk::Label mod_description;

		Glib::RefPtr<Gtk::StringList> modlist_names;
	public:
		MainWindow();
};

#endif