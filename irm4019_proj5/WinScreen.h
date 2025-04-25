#include "Scene.h"

class WinScreen : public Scene {
public:
    int ENEMY_COUNT = 1;
    int CHEST_COUNT = 4;
    bool check = true;
    glm::vec3 new_pos = (glm::vec3(0.0f,0.05f,0.0f));
    
    ~WinScreen();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
