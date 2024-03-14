#include "app.h"
#include "parser.h"
#include "inferrer.h"

char *textbox1_content = NULL;
char *textbox2_content = NULL;

static void button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *textbox = GTK_WIDGET(user_data);

    // Get textbox content
    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(textbox));
    const char *text = gtk_entry_buffer_get_text(buffer);

    if (strcmp(gtk_button_get_label(button), "Find Animal") == 0)
    {
        if (textbox1_content)
            g_free(textbox1_content);
        textbox1_content = g_strdup(text);

        editFactsFile("facts.kbs", textbox1_content);
        FILE *factsFile = openFile("facts.kbs");
        FILE *rulesFile = openFile("rules.kbs");

        Rule *rules = ruleParser(rulesFile);
        Fact *facts = factParser(factsFile);

        char *value = ForwardChaining(facts, rules);

        //Set textbox2 content to value
        GtkEntryBuffer *buffer2 = gtk_entry_get_buffer(GTK_ENTRY(textbox));
        gtk_entry_buffer_set_text(buffer2, value, -1);

        fclose(factsFile);
        fclose(rulesFile);

        freeFacts(facts);
        freeRules(rules);
    }
    else if (strcmp(gtk_button_get_label(button), "Find Characs.") == 0)
    {
        if (textbox2_content)
            g_free(textbox2_content);
        textbox2_content = g_strdup(text);
        printf("%s\n", textbox2_content);
    }
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *textbox1, *textbox2;
    GtkWidget *button_find_animal, *button_find_chars;
    (void)user_data;

    window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "Akinator de Aldi");
    gtk_window_set_default_size(GTK_WINDOW(window), 310, 90);

    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);

    textbox1 = gtk_entry_new();
    textbox2 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), textbox2, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), textbox1, 0, 0, 1, 1);

    button_find_animal = gtk_button_new_with_label("Find Animal");
    gtk_grid_attach(GTK_GRID(grid), button_find_animal, 0, 1, 1, 1);
    g_signal_connect(button_find_animal, "clicked", G_CALLBACK(button_clicked), textbox1);

    button_find_chars = gtk_button_new_with_label("Find Characs.");
    gtk_grid_attach(GTK_GRID(grid), button_find_chars, 2, 1, 1, 1);
    g_signal_connect(button_find_chars, "clicked", G_CALLBACK(button_clicked), textbox2);

    gtk_widget_set_visible(window, true);
}

int main(void)
{
    GtkApplication *app;

    app = gtk_application_new("org.gtk.akinator_de_aldi", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    g_application_run(G_APPLICATION(app), 0, NULL);
    g_object_unref(app);

    return 0;
}