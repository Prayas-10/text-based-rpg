#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>

struct Location {
    std::string name;
    sf::Vector2f pos;
    sf::Color color;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 700), "Prativindhya Quest Map");

    sf::Font font;
    // Make sure you have a font file named "arial.ttf" in the same directory,
    // or change this path to a font available on your system.
    if (!font.loadFromFile("arial.ttf")) {
        return -1; // font not found
    }

    // Locations with approximate positions (scaled to window size)
    std::vector<Location> locations = {
        {"Gorkha",     {270, 100}, sf::Color::White},
        {"Nuwakot",    {400, 180}, sf::Color::White},
        {"Doti",       {90,  240}, sf::Color::White},
        {"Kantipur",   {450, 320}, sf::Color::Yellow},
        {"Kirtipur",   {410, 390}, sf::Color::Red},
        {"Patan",      {540, 360}, sf::Color::White},
        {"Bhadgaon",   {630, 340}, sf::Color::White},
        {"Makwanpur",  {490, 460}, sf::Color::White},
        {"Simraungad", {410, 560}, sf::Color::White},
        {"Gorakhpur",  {540, 630}, sf::Color::Cyan},
        {"Awadh",      {680, 660}, sf::Color::Cyan},
        {"Lhasa",      {680, 80},  sf::Color::Cyan}
    };

    // Quick lookup by name
    std::map<std::string, sf::Vector2f> posByName;
    for (auto& loc : locations) posByName[loc.name] = loc.pos;

    // Non-linear connections (edges)
    std::vector<std::pair<std::string, std::string>> edges = {
        {"Gorkha", "Nuwakot"},
        {"Gorkha", "Doti"},
        {"Nuwakot", "Lhasa"},
        {"Nuwakot", "Kantipur"},
        {"Doti", "Kantipur"},
        {"Kantipur", "Kirtipur"},
        {"Kantipur", "Patan"},
        {"Kantipur", "Makwanpur"},
        {"Patan", "Bhadgaon"},
        {"Patan", "Gorakhpur"},
        {"Bhadgaon", "Awadh"},
        {"Makwanpur", "Simraungad"},
        {"Simraungad", "Gorakhpur"},
        {"Gorakhpur", "Awadh"},
        {"Kirtipur", "Makwanpur"}
    };

    // Build edge lines
    std::vector<sf::Vertex> edgeLines;
    for (auto& e : edges) {
        sf::Vector2f a = posByName[e.first];
        sf::Vector2f b = posByName[e.second];
        edgeLines.push_back(sf::Vertex(a, sf::Color(150, 150, 150)));
        edgeLines.push_back(sf::Vertex(b, sf::Color(150, 150, 150)));
    }

    // Node circles
    std::vector<sf::CircleShape> nodes;
    for (auto& loc : locations) {
        sf::CircleShape circle(10.f);
        circle.setFillColor(loc.color);
        circle.setOrigin(10.f, 10.f);
        circle.setPosition(loc.pos);
        nodes.push_back(circle);
    }

    // Labels
    std::vector<sf::Text> labels;
    for (auto& loc : locations) {
        sf::Text text(loc.name, font, 16);
        text.setFillColor(sf::Color::White);
        text.setPosition(loc.pos.x + 12, loc.pos.y - 10);
        labels.push_back(text);
    }

    // Title
    sf::Text title("Quest for Prativindhya - 1813 BS", font, 24);
    title.setFillColor(sf::Color::White);
    title.setPosition(20, 20);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(20, 20, 30));

        // draw edges
        window.draw(edgeLines.data(), edgeLines.size(), sf::Lines);

        // draw nodes
        for (auto& n : nodes) window.draw(n);

        // draw labels
        for (auto& l : labels) window.draw(l);

        window.draw(title);

        window.display();
    }

    return 0;
}