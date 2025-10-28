#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const int roadWidth = 1800;
const int roadsegmentLength = 180;
const int roadcount = 2000;

struct Road {
	float x, y, z;
	float X, Y, Z;

	Road(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
		void project(int camX, int camY, int camZ) {
			float scale = 1.0f / (z - camZ);
			X = (1 + scale * (x - camX)) * WINDOW_WIDTH / 2;
			Y = (1 - scale * (y - camY)) * WINDOW_HEIGHT / 2;
			Z = scale * roadWidth * WINDOW_WIDTH / 2;
		
	}
};

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

	std::vector<Road> roads;
	for (int i = 0; i < roadcount; ++i) {
		Road r(0, 0, (i+1) * roadsegmentLength);
		roads.push_back(r);
	}


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear(Color::Black);
		// Game rendering and logic would go here
		/*DrawTrape(window, Color::White, WINDOW_WIDTH / 2, 500, 200, WINDOW_WIDTH / 2
			, 300, 100);*/

		for (int i = 0; i < 600; ++i) {
			Road& now = roads[i];
			now.project(0, 1600, 0);

			if (!i) {
				continue;
			}
			Road& prev = roads[i-1];
			Color grass = (i / 3) % 2 ? Color(16, 210, 16) : Color(0, 199, 0);
			Color edge = (i / 3) % 2 ? Color(0, 0, 0) : Color(255, 255, 255);
			Color road = (i/3) % 2 ? Color(105, 105, 105) : Color(101, 101, 101);
			DrawTrape(window, grass,
				prev.X, prev.Y, WINDOW_WIDTH,
				now.X, now.Y, WINDOW_WIDTH);
			DrawTrape(window, edge,
				prev.X, prev.Y, prev.Z * 1.3,
				now.X, now.Y, now.Z * 1.3);
			DrawTrape(window, road,
				prev.X, prev.Y, prev.Z,
				now.X, now.Y, now.Z);
			
		}
		
		window.display();
	}

	return 0;
}