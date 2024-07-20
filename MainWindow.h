#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

class MainWindow : public Gtk::Window {
	protected:
		void on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item);
		void on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item);
		void on_selection_changed(guint position, guint n_items);
		void on_apply_mods_clicked();

		void update_active_mods();

		Gtk::Box mainbox;
		Gtk::Paned paned;
		
		Gtk::Box modlist_box;
		Gtk::Label modlist_heading;
		Gtk::ScrolledWindow modlist_scrollwindow;
		Gtk::ListView modlist_view;

		Gtk::Box alltheshit_box;
		Gtk::Paned othershit_separator;
		Gtk::Box control_box;
		Gtk::ScrolledWindow mod_description_scrollwindow;
		Gtk::Label mod_description;

		Gtk::Button apply_mods_button;

		Glib::RefPtr<Gtk::StringList> modlist_names;
		Glib::RefPtr<Gtk::SingleSelection> selection_model;
	public:
		MainWindow();
};

#endif