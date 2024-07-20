#include "MainWindow.h"
#include "Mods.h"
#include <iostream>
#include <string>

MainWindow::MainWindow()
:   mainbox(Gtk::Orientation::HORIZONTAL),
    modlist_box(Gtk::Orientation::VERTICAL),
    alltheshit_box(Gtk::Orientation::VERTICAL),
    control_box(Gtk::Orientation::HORIZONTAL),
    apply_mods_button("Apply"),
    modlist_heading("<b>Mods:</b>", Gtk::Align::START),
    paned(Gtk::Orientation::HORIZONTAL),
    othershit_separator(Gtk::Orientation::VERTICAL),
    mod_description("Home Page") {

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

    othershit_separator.set_position((h/6)*5);
    
    mod_description.set_use_markup();
    mod_description.set_wrap();
    mod_description.set_halign(Gtk::Align::START);
    mod_description.set_valign(Gtk::Align::START);
    mod_description.set_expand();
    
    mod_description_scrollwindow.set_child(mod_description);
    mod_description_scrollwindow.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
    mod_description_scrollwindow.set_expand();

    alltheshit_box.set_margin(10);
    alltheshit_box.append(othershit_separator);
    
    apply_mods_button.set_expand();
    apply_mods_button.set_margin(10);
    apply_mods_button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_apply_mods_clicked));
    control_box.append(apply_mods_button);

    othershit_separator.set_start_child(mod_description_scrollwindow);
    othershit_separator.set_end_child(control_box);

    modlist_heading.set_use_markup();
    modlist_box.set_margin(10);
    modlist_box.append(modlist_heading);

    modlist_scrollwindow.set_child(modlist_view);
    modlist_scrollwindow.set_policy(Gtk::PolicyType::NEVER, Gtk::PolicyType::AUTOMATIC);
    modlist_scrollwindow.set_expand();

    modlist_box.append(modlist_scrollwindow);
    
    std::vector<Glib::ustring> modnames;
    for (Mod mod : Mods::mods) {
        modnames.push_back(mod.get_name());
    }
    modlist_names = Gtk::StringList::create(modnames);

    selection_model = Gtk::SingleSelection::create(modlist_names);
    selection_model->signal_selection_changed().connect(sigc::mem_fun(*this, &MainWindow::on_selection_changed));
    selection_model->set_autoselect(false);
    selection_model->set_can_unselect(true);
    selection_model->set_selected(GTK_INVALID_LIST_POSITION);
    modlist_view.set_model(selection_model);
    modlist_view.set_expand();
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
    auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
    box->set_expand();
    auto checkbutton = Gtk::make_managed<Gtk::CheckButton>("");
    auto label = Gtk::make_managed<Gtk::Label>("", Gtk::Align::START);
    label->set_ellipsize(Pango::EllipsizeMode::END);

    box->append(*checkbutton);
    box->append(*label);
    
    list_item->set_child(*box);
}

void MainWindow::on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item) {
    auto pos = list_item->get_position();
    if (pos == GTK_INVALID_LIST_POSITION)
        return;
    auto box = dynamic_cast<Gtk::Box*>(list_item->get_child());
    if (!box)
        return;
    auto label = dynamic_cast<Gtk::Label*>(box->get_children()[1]);
    label->set_text(" " + modlist_names->get_string(pos));
    if (Mods::get_mod(pos).get_id() == "vanilla") {
        auto checkbutton = dynamic_cast<Gtk::CheckButton*>(box->get_children()[0]);
        checkbutton->set_active();
    }
}

void MainWindow::on_selection_changed(guint position, guint n_items) {
    guint selected = selection_model->get_selected();
    if (selected != GTK_INVALID_LIST_POSITION){
        mod_description.set_text(Mods::mods[selected].get_long_description());
        mod_description.set_use_markup();
    }
}

void MainWindow::update_active_mods() {
    for (guint pos = 0; pos < modlist_names->get_n_items(); ++pos) {
        auto list_item = modlist_view.get_children()[pos];
        if (!list_item)
            continue;
        auto box = dynamic_cast<Gtk::Box*>(list_item->get_children()[0]);
        if (!box)
            continue;
        auto checkbutton = dynamic_cast<Gtk::CheckButton*>(box->get_children()[0]);
        if (checkbutton){
            bool active = checkbutton->get_active();
            Mods::set_mod_active(pos, active);
        }
    }
}

void MainWindow::on_apply_mods_clicked() {
    update_active_mods();
    Mods::apply_mods();
}