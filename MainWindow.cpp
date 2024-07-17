#include "MainWindow.h"
#include <iostream>
#include <string>
#include <fstream>

/* using namespace std;

string read_file(string path) {
    string line;
    string text;
    ifstream file(path);

    while(getline(file, line)) {
        text += line;
    }

    file.close();
    return text;
} */

MainWindow::MainWindow()
:   mainbox(Gtk::Orientation::HORIZONTAL),
    modlist_box(Gtk::Orientation::VERTICAL),
    alltheshit_box(Gtk::Orientation::VERTICAL),
    modlist_heading("<b>Mods:</b>", Gtk::Align::START),
    paned(Gtk::Orientation::HORIZONTAL),
    mod_description("Lärp") {

    int w, h;
    w = 800;
    h = 600;
    
    set_title("Primitive Wings Mod Loader");
    set_default_size(w, h);

    auto css_provider = Gtk::CssProvider::create();
    css_provider->load_from_path("style.css");

    Gtk::StyleProvider::add_provider_for_display(get_display(), css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    set_child(mainbox);

    mainbox.append(paned);
    paned.set_start_child(modlist_box);
    paned.set_end_child(alltheshit_box);
    paned.set_position(w/3);
    
    mod_description.set_use_markup();
    mod_description.set_wrap();
    mod_description.set_halign(Gtk::Align::START);
    
    alltheshit_box.set_margin(10);
    alltheshit_box.append(mod_description);

    modlist_heading.set_use_markup();
    modlist_box.set_margin(10);
    modlist_box.append(modlist_heading);
    modlist_scrollwindow.set_child(modlist_view);

    modlist_scrollwindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    modlist_scrollwindow.set_expand();

    modlist_box.append(modlist_scrollwindow);
    
    modlist_names = Gtk::StringList::create({"bestmod", "Jurt's epic mod", "Heketiitus' vomit inducingly bad mod", "Industrialcrap"});

    auto selection_model = Gtk::SingleSelection::create(modlist_names);
    selection_model->set_autoselect(false);
    selection_model->set_can_unselect(true);
    modlist_view.set_model(selection_model);
    modlist_view.add_css_class("data-table");
    modlist_view.add_css_class("modlist-view-frame");

    auto factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(
        sigc::mem_fun(*this, &MainWindow::on_setup_label));
    factory->signal_bind().connect(
        sigc::mem_fun(*this, &MainWindow::on_bind_name));
    modlist_view.set_factory(factory);
}

void MainWindow::on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item) {
    list_item->set_child(*Gtk::make_managed<Gtk::Label>("", Gtk::Align::START));
}

void MainWindow::on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item) {
    auto pos = list_item->get_position();
    if (pos == GTK_INVALID_LIST_POSITION)
        return;
    auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
    if (!label)
        return;
    label->set_text(modlist_names->get_string(pos));
}