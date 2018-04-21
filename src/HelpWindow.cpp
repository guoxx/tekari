#include "HelpWindow.h"

#include <nanogui/button.h>
#include <nanogui/entypo.h>
#include <nanogui/label.h>
#include <nanogui/layout.h>
#include <nanogui/opengl.h>
#include <nanogui/tabwidget.h>
#include <nanogui/vscrollpanel.h>
#include <nanogui/window.h>

using namespace nanogui;
using namespace std;

#ifdef __APPLE__
string HelpWindow::COMMAND = "Cmd";
#else
string HelpWindow::COMMAND = "Ctrl";
#endif

#ifdef __APPLE__
string HelpWindow::ALT = "Opt";
#else
string HelpWindow::ALT = "Alt";
#endif

HelpWindow::HelpWindow(Widget *parent, function<void()> closeCallback)
:   Window{ parent, "Help" }
,   m_CloseCallback{ closeCallback }
{
    setFixedWidth(600);
    auto closeButton = new Button{ buttonPanel(), "", ENTYPO_ICON_CROSS };
    closeButton->setCallback(m_CloseCallback);
    setLayout(new GroupLayout{});

    TabWidget* tabWidget = new TabWidget{ this };

    // Keybindings tab
    {
        Widget* shortcuts = tabWidget->createTab("Keybindings");
        shortcuts->setLayout(new GroupLayout{});

        m_ScrollPanel = new VScrollPanel{ shortcuts };
        auto scrollContent = new Widget{ m_ScrollPanel };
        scrollContent->setLayout(new GroupLayout{});
        m_ScrollPanel->setFixedHeight(500);

        auto addShortcutSection = [&scrollContent](const std::string& label) {
            new Label{ scrollContent, label, "sans-bold", 18 };
            auto section = new Widget{ scrollContent };
            section->setLayout(new BoxLayout{ Orientation::Vertical, Alignment::Fill, 0, 0 });
            return section;
        };

        auto addRow = [](Widget* current, string keys, string desc) {
            auto row = new Widget{ current };
            row->setLayout(new BoxLayout{ Orientation::Horizontal, Alignment::Fill, 0, 10 });
            auto descWidget = new Label{ row, desc, "sans" };
            descWidget->setFixedWidth(250);
            new Label{ row, keys, "sans-bold" };
        };

        auto moveControls = addShortcutSection("Move Controls");
        addRow(moveControls, "Left Drag", "Rotate Data Sample");
        addRow(moveControls, "Middle Drag", "Translate Data Sample");
        addRow(moveControls, "Scroll In / Out", "Zoom In / Out");
        addRow(moveControls, "C", "Snap To Selection Center");

        auto fileLoading = addShortcutSection("File Loading");
        addRow(fileLoading, COMMAND + "+O", "Open Data Sample");
        addRow(fileLoading, COMMAND + "+S", "Save Data in obj format");
        addRow(fileLoading, COMMAND + "+P", "Save Screenshot of Data");
        addRow(fileLoading, "Delete", "Close Selected Data Sample");

        auto viewOptions = addShortcutSection("View Options");
        addRow(viewOptions, "N", "Show/Hide Normal View");
        addRow(viewOptions, "L", "Show/Hide Logarithmic View");
        addRow(viewOptions, "P", "Show/Hide Path");
        addRow(viewOptions, "Shift + P", "Show/Hide All Points");
        addRow(viewOptions, "Shift + I", "Show/Hide Incident Angle");
        addRow(viewOptions, "G", "Show/Hide Grid");
        addRow(viewOptions, "A", "Show/Hide Center Points");
        addRow(viewOptions, "Shift+G", "Show/Hide Grid Degrees");
        addRow(viewOptions, "Shift+S", "Use/Un-use Shadows");
        addRow(viewOptions, "M", "Chose Color Map");
        addRow(viewOptions, "O / KP_5", "Enable/Disable Orthographic View");
        addRow(viewOptions, "KP_1 or Alt+1 / " + COMMAND + "+KP_1 or " + COMMAND + "+Alt+1", "Front / Back View");
        addRow(viewOptions, "KP_3 or Alt+3 / " + COMMAND + "+KP_3 or " + COMMAND + "+Alt+3", "Left / Right View");
        addRow(viewOptions, "KP_7 or Alt+7 / " + COMMAND + "+KP_7 or " + COMMAND + "+Alt+7", "Top / Bottom View");

        auto dataSelection = addShortcutSection("Data Sample Selection");
        addRow(dataSelection, "1...9", "Select N-th Data Sample");
        addRow(dataSelection, "Down or S / Up or W", "Select Next / Previous Data Sample");
        addRow(dataSelection, "Left Click", "Select Hovered Data Sample");

        auto dataEdition = addShortcutSection("Data Editing");
        addRow(dataEdition, "Right Drag", "Select Data Points In Region");
        addRow(dataEdition, "Shift + Right Drag", "Add Points In Region To Current Selection");
        addRow(dataEdition, "Alt + Right Drag", "Remove Points In Region To Current Selection");
        addRow(dataEdition, "Right Click or Escape", "Deselect All Points");

        auto ui = addShortcutSection("Interface");
        addRow(ui, "H", "Show Help (this Window)");
        addRow(ui, "Q", "Quit");
    }


    // About tab
    {
        Widget* about = tabWidget->createTab("About");
        about->setLayout(new GroupLayout{});

        auto addText = [](Widget* current, string text, string font = "sans", int fontSize = 18) {
            auto row = new Widget{ current };
            row->setLayout(new BoxLayout{ Orientation::Vertical, Alignment::Middle, 0, 10 });
            new Label{ row, text, font, fontSize };
        };

        auto addLibrary = [](Widget* current, string name, string license, string desc) {
            auto row = new Widget{ current };
            row->setLayout(new BoxLayout{ Orientation::Horizontal, Alignment::Fill, 5, 30 });
            auto leftColumn = new Widget{ row };
            leftColumn->setLayout(new BoxLayout{ Orientation::Vertical, Alignment::Maximum });
            leftColumn->setFixedWidth(130);

            new Label{ leftColumn, name, "sans-bold", 18 };
            new Label{ row, desc, "sans", 18 };
        };

        auto addSpacer = [](Widget* current, int space) {
            auto row = new Widget{ current };
            row->setHeight(space);
        };

        addSpacer(about, 15);

        addText(about, "BSDF Visualizer Tool", "sans-bold", 46);

        addSpacer(about, 60);

        addText(about, "This helper tool was developed by Benoit Ruiz and is released");
        addText(about, "under the BSD 3 - Clause License.");
        addText(about, "It was built directly or indirectly upon the following amazing third-party libraries.");

        addSpacer(about, 40);

        addLibrary(about, "Eigen", "", "C++ Template Library for Linear Algebra.");
        addLibrary(about, "Glad", "", "Multi-Language GL Loader-Generator.");
        addLibrary(about, "GLEW", "", "The OpenGL Extension Wrangler Library.");
        addLibrary(about, "GLFW", "", "OpenGL Desktop Development Library.");
        addLibrary(about, "NanoGUI", "", "Small Widget Library for OpenGL.");
        addLibrary(about, "NanoVG", "", "Small Vector Graphics Library.");
    }

    tabWidget->setActiveTab(0);
}

bool HelpWindow::keyboardEvent(int key, int scancode, int action, int modifiers) {
    if (Window::keyboardEvent(key, scancode, action, modifiers)) {
        return true;
    }

    if (key == GLFW_KEY_ESCAPE) {
        m_CloseCallback();
        return true;
    }

    return false;
}

void HelpWindow::performLayout(NVGcontext *ctx)
{
    nanogui::Window::performLayout(ctx);
    //m_ScrollPanel->setFixedHeight(mParent->height() / 2);
    center();
}