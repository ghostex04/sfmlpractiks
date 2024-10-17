#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>

using namespace std;
using namespace sf;
class figure {
public:
    vector<Vector2f> points;

    void addPoint(float x, float y) {
        points.push_back(Vector2f(x, y));
    }
};
    void read_draw(const string& name, figure& LinesStrips, RenderWindow& window) {
        ifstream file(name);
        if (!file.is_open()) {
            cout << "ошибка файла" << endl;
            return;
        }

        cout << "файл открыт" << endl;
        float x1, y1, x2, y2;
        float lastX, lastY;

        float minX = numeric_limits<float>::max(); // Инициализируем минимальное значение X максимально возможным
        float maxX = numeric_limits<float>::min(); // Инициализируем максимальное значение X минимально возможным
        float minY = numeric_limits<float>::max();
        float maxY = numeric_limits<float>::min();

        // Находим минимальное и максимальное значения X и Y
        while (file >> x1 >> y1) {
            minX = min(minX, x1);
            maxX = max(maxX, x1);
            minY = min(minY, y1);
            maxY = max(maxY, y1);
        }
        file.close();

        file.open(name);

            cout << "файл открыт" << endl;
          
            Vector2u windowSize = window.getSize();
            float centerX = windowSize.x / 3.5f;
            float centerY = windowSize.y / 1.3f;
            float scale_x = (windowSize.x * 0.5) / (maxX - minX);
            float scale_y = (windowSize.y * 0.5) / (maxY - minY);
            
            if (file >> x1 >> y1) {
                
                x1 = centerX + ((x1 - minX) * scale_x);
                y1 = centerY + ((y1 - minY) * -scale_y);
                lastX = x1;
                lastY = y1;

            }
            LinesStrips.addPoint(lastX, lastY);
            while (file >> x2 >> y2) {
                x2 = centerX + ((x2- minX) * scale_x);
                y2 = centerY + ((y2-minY) * -scale_y);
                cout << x2 << "  " << y2 << endl;
                LinesStrips.addPoint(x2, y2);
                
            }
            LinesStrips.addPoint(lastX, lastY);
            LinesStrips.addPoint(x2, y2);
           
           
        
        file.close();
        
    }




int main() {
    setlocale(LC_ALL, "RU");

    figure LinesStrips;
    RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    read_draw("name.txt", LinesStrips, window);

    
   
   
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

       
        VertexArray line(LinesStrip, LinesStrips.points.size());
        for (size_t i = 0; i < LinesStrips.points.size(); ++i) {
            line[i].position = LinesStrips.points[i];
        }
        window.draw(line);
        window.display();
    }

    return 0;
}




