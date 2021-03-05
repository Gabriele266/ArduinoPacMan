#include "theme.h"

Theme::Theme()
{

}

bool Theme::loadTheme(){
    // Create the file object
    QFile input_file(file);

    // Try to open the file
    if(input_file.open(QIODevice::ReadOnly)){
        // Read the dom document
        QDomDocument document;
        document.setContent(&input_file);

        QDomElement root = document.documentElement();

        // Get the stylesheet element
        QDomElement stylesheet = root.firstChildElement("style");
        // Read the stylesheet contents
        style = stylesheet.attribute("content");

        // Get other informations
        QDomElement description = root.firstChildElement("description");
        setDescription(description.attribute("value"));

        // Get the name
        auto name = root.firstChildElement("name");
        setName(name.attribute("value"));

        auto err_col = root.firstChildElement("error_color");
        error_color = htmlToColor(err_col.attribute("rgb"));

        auto succ_col = root.firstChildElement("success_color");
        success_color = htmlToColor(succ_col.attribute("rgb"));

        auto norm_col = root.firstChildElement("normal_color");
        normal_text_color = htmlToColor(norm_col.attribute("rgb"));

        auto desc_col = root.firstChildElement("description_color");
        descriptions_color = htmlToColor(desc_col.attribute("rgb"));

        auto norm_back = root.firstChildElement("normal_backgroud_color");
        normal_background_color = htmlToColor(norm_back.attribute("rgb"));

        auto high_back = root.firstChildElement("highlight_background_color");
        highlight_background_color = htmlToColor(high_back.attribute("rgb"));

        auto high_text = root.firstChildElement("highlight_text_color");
        highlight_text_color = htmlToColor(high_text.attribute("rgb"));

        input_file.close();

        // Set status variable
        loaded = true;
        return true;
    }else{
        return false;
    }
}
