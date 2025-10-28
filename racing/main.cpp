#include <SFML/Graphics.hpp>
using namespace sf;
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

void DrawTrape(RenderWindow& window, Color c, int x1, int y1,
	int w1, int x2, int y2, int w2) {
	ConvexShape polygon(4);
	polygon.setFillColor(c);
	polygon.setPoint(0, Vector2f(x1-w1, y1));
	polygon.setPoint(1, Vector2f(x2 - w2, y2));
	polygon.setPoint(2, Vector2f(x2 + w2, y2));
	polygon.setPoint(3, Vector2f(x1 + w1, y1));
	window.draw(polygon);
}

int main() {
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Racing Game");
	window.setFramerateLimit(60);
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color::Black);
		// Game rendering and logic would go here
		DrawTrape(window, Color::White, WINDOW_WIDTH / 2, 500, 200, WINDOW_WIDTH / 2
			, 300, 100);
		window.display();
	}

	return 0;
}