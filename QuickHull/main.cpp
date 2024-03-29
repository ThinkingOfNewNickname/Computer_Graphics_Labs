#include "Application.h"
#include "quick_hull.h"

#include "imgui/imgui.h"


int main()
{
    frm::vvve::VVVE vvve{};

    frm::vvve::load_from_file("Vvse_1.dat", vvve);

    frm::Application application{};

    application.set_on_update([&vvve](float dt, sf::RenderWindow & window) noexcept
        {
            frm::vvve::draw(vvve, window);

            bool is_dirty_vvve = false;

            is_dirty_vvve |= frm::vvve::spawn_ui(vvve, window, "Vvse_1.dat");

            if (ImGui::Begin("QuickHull"))
            {
                if (ImGui::Button("Run"))
                {
                    quick_hull(vvve);
                }
            }
            ImGui::End();
        });

    application.run();
}