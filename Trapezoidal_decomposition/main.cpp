#include "Application.h"
#include "dcel.h"
#include "trapezoidal_decomposition.h"


int main()
{
    frm::dcel::DCEL dcel{};

    frm::dcel::load_from_file("Dcel_1.dat", dcel);

    trapezoid_data_and_graph_root_t trapezoid_data_and_graph_root = generate_trapezoid_data_and_graph_root(dcel);

    size_t current_face = trapezoid_data_and_graph_root.first;

    frm::Application application{};

    application.set_on_event([&dcel, &current_face, &trapezoid_data_and_graph_root ](sf::Event current_event) noexcept
        {
            if (current_event.type == sf::Event::MouseButtonPressed)
            {
                int x = current_event.mouseButton.x;
                int y = current_event.mouseButton.y;

                current_face = get_face_index(trapezoid_data_and_graph_root, { static_cast<float>(x), static_cast<float>(y) });
            }
        });

    application.set_on_update([&dcel, &trapezoid_data_and_graph_root, &current_face](float dt, sf::RenderWindow & window) noexcept
        {
            trapezoid_data_and_graph_root = generate_trapezoid_data_and_graph_root(dcel);

            frm::dcel::draw(dcel, window);

            frm::dcel::spawn_ui(dcel, window, "Dcel_1.dat");

            if (current_face != trapezoid_data_and_graph_root.first)
            {
                float color[4] = { 0.f, 0.f, 1.f, 0.5f };
                frm::dcel::draw_face_highlighted(current_face, dcel, color, window);
            }
        });

    application.run();
}