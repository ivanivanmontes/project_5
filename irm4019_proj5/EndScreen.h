#include "Scene.h"

class EndScreen : public Scene {
public:
    int ENEMY_COUNT = 1;
    
    
    ~EndScreen();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
    
};
