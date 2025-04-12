/**
* Author: Ivan Reynoso Montes
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 15
#define LEVEL_HEIGHT 8

constexpr char SPRITESHEET_FILEPATH[] = "Frame_5.png",
           ENEMY_FILEPATH[]       = "troppa.png",
FONT_FILEPATH[] = "font1.png";



GLuint g_font_texture_id_1;


unsigned int LEVELA_DATA[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
    2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0,
};

LevelA::~LevelA()
{
    delete [] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelA::initialise()
{
    m_game_state.next_scene_id = -1;
    
    
    
    GLuint map_texture_id = Utility::load_texture("Frame_6.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, map_texture_id, 1.0f, 4, 1);
    
    g_font_texture_id_1 = Utility::load_texture(FONT_FILEPATH);
    
    int player_walking_animation[4][4] =
    {
        { 1, 5, 9, 13 },
        { 3, 7, 11, 15 },
        { 2, 6, 10, 14 },
        { 0, 4, 8, 12 }
    };

    glm::vec3 acceleration = glm::vec3(0.0f, -4.81f, 0.0f);
    
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
        
    m_game_state.player->set_position(glm::vec3(1.0f, -5.0f, 0.0f));

    m_game_state.player->set_jumping_power(3.0f);
    
    GLuint enemy_texture_id = Utility::load_texture(ENEMY_FILEPATH);

    m_game_state.enemies = new Entity[ENEMY_COUNT];

    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i] =  Entity(enemy_texture_id, 0.0f, 1.0f, 1.0f, ENEMY, WALKER, IDLE);
    }


    m_game_state.enemies[0].set_position(glm::vec3(5.0f, -5.0f, 0.0f));
    m_game_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[0].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    
    

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_game_state.bgm = Mix_LoadMUS("VeLDA.mp3");
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(20.0f);
    
    m_game_state.jump_sfx = Mix_LoadWAV("duermes.wav");
    m_game_state.walk_sfx = Mix_LoadWAV("capo.wav");
    m_game_state.die_sfx = Mix_LoadWAV("feid.wav");
}

void LevelA::update(float delta_time)
{
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);
    for (int i = 0; i < ENEMY_COUNT; i++) {
        glm::vec3 res = m_game_state.enemies[i].get_position();
        if (res.y >= 0.0) {
            check = !check;
        } else if (res.y <= -5.05) {
            check = !check;
        }
        if (check) {
            res += new_pos;
        } else {
            res -= new_pos;
        }
        m_game_state.enemies[i].set_position(res);
        m_game_state.enemies[i].update(delta_time, m_game_state.enemies, m_game_state.player, 1, m_game_state.map);
    }
    
    
    bool end = m_game_state.player->get_collided_top() || m_game_state.player->get_collided_right() || m_game_state.player->get_collided_left();
    if (end) {
        Mix_PlayChannel(-1,  m_game_state.die_sfx, 0);
        LIVES -= 1;
        m_game_state.player->set_position(glm::vec3(1.0f,0.0f,0.0f));
    }
    

    if (m_game_state.player->get_position().y < -10.0f && m_game_state.player->get_position().x >= 12.0f) m_game_state.next_scene_id = 2;
    else if (m_game_state.player->get_position().y < -10.0f && m_game_state.player->get_position().x < 12.0f) {
        m_game_state.player->set_position(glm::vec3(1.0f,0.0f,0.0f));
    }
    
    
}

void LevelA::render(ShaderProgram *program)
{
    m_game_state.map->render(program);
    m_game_state.player->render(program);
    for (int i = 0; i < ENEMY_COUNT; i++)    m_game_state.enemies[i].render(program);

    
    
    Utility::draw_text(program, g_font_texture_id_1, "lives: " + std::to_string(LIVES), 0.35f, 0.05f, m_game_state.player->get_position());
    Utility::draw_text(program, g_font_texture_id_1, "Next Level", 0.35f, 0.05f, glm::vec3(12.0f, -4.0f, 0.0f));
    Utility::draw_text(program, g_font_texture_id_1, "VVV", 0.35f, 0.05f, glm::vec3(12.0f, -5.0f, 0.0f));
}
