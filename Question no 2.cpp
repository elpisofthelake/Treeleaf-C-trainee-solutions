#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

struct Vertex {
    int x, y, z;

    Vertex(int x, int y, int z) : x(x), y(y), z(z) {}
};

class Box {
private:
    std::vector<Vertex> vertices;

public:
    Box(const std::vector<Vertex>& vertices) : vertices(vertices) {}

    const std::vector<Vertex>& getVertices() const {
        return vertices;
    }

    void setVertices(const std::vector<Vertex>& newVertices) {
        vertices = newVertices;
    }
};

class Transformation {
public:
    static std::shared_ptr<Box> rotateAboutX(std::shared_ptr<Box> box, int angle_x) {
        double rad = angle_x * M_PI / 180.0;
        auto vertices = box->getVertices();
        for (auto& vertex : vertices) {
            int y_new = vertex.y * cos(rad) - vertex.z * sin(rad);
            int z_new = vertex.y * sin(rad) + vertex.z * cos(rad);
            vertex.y = y_new;
            vertex.z = z_new;
        }
        box->setVertices(vertices);
        return box;
    }

    static std::shared_ptr<Box> rotateAboutY(std::shared_ptr<Box> box, int angle_y) {
        double rad = angle_y * M_PI / 180.0;
        auto vertices = box->getVertices();
        for (auto& vertex : vertices) {
            int x_new = vertex.x * cos(rad) + vertex.z * sin(rad);
            int z_new = -vertex.x * sin(rad) + vertex.z * cos(rad);
            vertex.x = x_new;
            vertex.z = z_new;
        }
        box->setVertices(vertices);
        return box;
    }

    static std::shared_ptr<Box> rotateAboutZ(std::shared_ptr<Box> box, int angle_z) {
        double rad = angle_z * M_PI / 180.0;
        auto vertices = box->getVertices();
        for (auto& vertex : vertices) {
            int x_new = vertex.x * cos(rad) - vertex.y * sin(rad);
            int y_new = vertex.x * sin(rad) + vertex.y * cos(rad);
            vertex.x = x_new;
            vertex.y = y_new;
        }
        box->setVertices(vertices);
        return box;
    }

    static std::shared_ptr<Box> scale(std::shared_ptr<Box> box, double scale_factor) {
        auto vertices = box->getVertices();
        for (auto& vertex : vertices) {
            vertex.x = static_cast<int>(vertex.x * scale_factor);
            vertex.y = static_cast<int>(vertex.y * scale_factor);
            vertex.z = static_cast<int>(vertex.z * scale_factor);
        }
        box->setVertices(vertices);
        return box;
    }
};

int main() {
    std::vector<Vertex> vertices = {
        Vertex(1, 1, 1), Vertex(1, 1, -1), Vertex(1, -1, 1), Vertex(1, -1, -1),
        Vertex(-1, 1, 1), Vertex(-1, 1, -1), Vertex(-1, -1, 1), Vertex(-1, -1, -1)
    };

    auto box = std::make_shared<Box>(vertices);

    // Rotate about X axis by 45 degrees
    Transformation::rotateAboutX(box, 45);
    // Rotate about Y axis by 30 degrees
    Transformation::rotateAboutY(box, 30);
    // Rotate about Z axis by 60 degrees
    Transformation::rotateAboutZ(box, 60);
    // Scale by factor of 2
    Transformation::scale(box, 2.0);

    for (const auto& vertex : box->getVertices()) {
        std::cout << "(" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")\n";
    }

    return 0;
}
