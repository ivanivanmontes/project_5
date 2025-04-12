#include "Scene.h"

class LoseScreen : public Scene {
public:
    int ENEMY_COUNT = 1;
    
    
    ~LoseScreen();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
    
};
