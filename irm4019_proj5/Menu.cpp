
#include "Menu.h"
#include "Utility.h"

#define LEVEL_WIDTH 15
#define LEVEL_HEIGHT 15

constexpr char SPRITESHEET_FILEPATH[] = "gangster.png",
           ENEMY_FILEPATH[]       = "opp.png",
PLATFORM_FILEPATH [] = "chest_closed.png",
FONT_FILEPATH[] = "font1.png";



GLuint g_font_texture_id_2;


unsigned int MENU_DATA[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};



Menu::~Menu()
{
    delete [] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
}

void Menu::initialise()
{
    m_game_state.next_scene_id = -1;
    
    
    
    GLuint map_texture_id = Utility::load_texture("Frame_6.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, MENU_DATA, map_texture_id, 1.0f, 4, 1);
    
    g_font_texture_id_2 = Utility::load_texture(FONT_FILEPATH);
    
    int player_walking_animation[4][4] =
    {
        { 1, 5, 9, 13 },
        { 3, 7, 11, 15 },
        { 2, 6, 10, 14 },
        { 0, 4, 8, 12 }
    };

    glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    
    GLuint player_texture_id = Utility::load_texture(SPRITESHEET_FILEPATH);
    
    
    m_game_state.player = new Entity(
        player_texture_id,         // texture id
        5.0f,                      // speed
        acceleration,              // acceleration
        5.0f,                      // jumping power
        player_walking_animation,  // animation index sets
        0.0f,                      // animation time
        4,                         // animation frame amount
        0,                         // current animation index
        4,                         // animation column amount
        4,                         // animation row amount
        1.0f,                      // width
        1.0f,                       // height
        PLAYER
    );
        
    m_game_state.player->set_position(glm::vec3(5.0f, 1.0f, 0.0f));
}

void Menu::update(float delta_time)
{

}

void Menu::render(ShaderProgram *program)
{
    m_game_state.map->render(program);
    Utility::draw_text(program, g_font_texture_id_2, "Welcome to my game", 0.35f, 0.025f, glm::vec3(1.5f, 3.5f, 0.0f));
    Utility::draw_text(program, g_font_texture_id_2, "Goal: collect $200", 0.35f, 0.025f, glm::vec3(1.5f, 3.0f, 0.0));
    Utility::draw_text(program, g_font_texture_id_2, "press return to open chests", 0.25f, 0.025f, glm::vec3(1.5f, 2.5f, 0.0f));
}
