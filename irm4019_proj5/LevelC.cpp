/**
* Author: Ivan Reynoso Montes
* Assignment: Rise of the AI
* Date due: 2025-04-05, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "LevelC.h"
#include "Utility.h"

#define LEVEL_WIDTH 15
#define LEVEL_HEIGHT 15

constexpr char SPRITESHEET_FILEPATH[] = "gangster.png",
           ENEMY_FILEPATH[]       = "opp.png",
PLATFORM_FILEPATH[] = "chest_closed.png",
FONT_FILEPATH[] = "font1.png";



GLuint g_font_texture_id_8;


unsigned int LEVELC_DATA[] =
{
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};


LevelC::~LevelC()
{
    delete [] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeChunk(m_game_state.jump_sfx);
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelC::initialise()
{
    m_game_state.next_scene_id = 4;
    
    
    
    GLuint map_texture_id = Utility::load_texture("tiles.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELC_DATA, map_texture_id, 1.0f, 4, 1);
    
    g_font_texture_id_8 = Utility::load_texture(FONT_FILEPATH);
    
    int player_walking_animation[4][4] =
    {
        { 1, 5, 9, 13 },
        { 3, 7, 11, 15 },
        { 2, 6, 10, 14 },
        { 0, 4, 8, 12 }
    };

    glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    
    GLuint player_texture_id = Utility::load_texture(SPRITESHEET_FILEPATH);
    
    /// new platform

    
    
    
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
        
    m_game_state.player->set_position(glm::vec3(5.0f, -4.0f, 0.0f));

//    m_game_state.player->set_jumping_power(3.0f);
    
    GLuint enemy_texture_id = Utility::load_texture(ENEMY_FILEPATH);
    
    GLuint platform_texture_id = Utility::load_texture(PLATFORM_FILEPATH);

    m_game_state.enemies = new Entity[ENEMY_COUNT];
    
    m_game_state.platforms = new Entity[CHEST_COUNT];
    
    for (int i = 0; i < CHEST_COUNT; i++) {
        m_game_state.platforms[i] = Entity(platform_texture_id, 0.0f, 1.0f, 1.0f, PLATFORM);
    }

    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i] =  Entity(enemy_texture_id, 0.0f, 1.0f, 1.0f, ENEMY, GUARD, WALKING);
    }

    m_game_state.platforms[0].set_position(glm::vec3(10.0f, -9.0f, 0.0f));
    m_game_state.platforms[1].set_position(glm::vec3(10.0f, -5.0f, 0.0f));
    m_game_state.platforms[2].set_position(glm::vec3(2.0f, -5.0f, 0.0f));
    m_game_state.platforms[3].set_position(glm::vec3(2.0f, -9.0f, 0.0f));

    int start = 5.0f;
    
    for (int i = 0; i < ENEMY_COUNT; i++) {
        m_game_state.enemies[i].set_position(glm::vec3(start + i, -9.0f, 0.0f));
        m_game_state.enemies[i].set_movement(glm::vec3(0.0f));
        m_game_state.enemies[i].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    }
    
   
    
    
    
    

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_game_state.bgm = Mix_LoadMUS("GAVILAN.mp3");
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(20.0f);
    
    m_game_state.jump_sfx = Mix_LoadWAV("ahem.wav");
    m_game_state.walk_sfx = Mix_LoadWAV("capo.wav");
    m_game_state.die_sfx = Mix_LoadWAV("money.wav");
}

void LevelC::update(float delta_time)
{
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);
    for (int i = 0; i < ENEMY_COUNT; i++) {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, m_game_state.player, 1, m_game_state.map);
        
    }
    
    for (int i = 0; i < CHEST_COUNT; i++) {
        m_game_state.platforms[i].update(delta_time, m_game_state.player, m_game_state.player, 1, m_game_state.map);
        
    }
    
    for (int i = 0; i < ENEMY_COUNT; i++) {
            glm::vec3 res = m_game_state.enemies[i].get_position();
            if (res.y >= -2.0) {
                
                check = !check;
            } else if (res.y <= -12.05) {
                Mix_PlayChannel(-1, m_game_state.jump_sfx, 0);
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
    
    
    for (int i = 0; i < CHEST_COUNT; i++) {
        if (m_game_state.platforms[i].check_collision(m_game_state.player)) {
            /// if on the chest, pick it up
            m_game_state.player->set_chest(true);
            m_game_state.player->set_collide_obj(&m_game_state.platforms[i]);
            break;
        }
        else {
            m_game_state.player->set_chest(false);
        }
    }
    
    if (m_game_state.player->get_return()) {
        /// if they pressed "return"
        /// check if the player is on a chest
        if (m_game_state.player->get_chest()) {
            std::cout << m_game_state.player->get_collide_obj()->get_position().x << m_game_state.player->get_collide_obj()->get_position().y << std::endl;
            
            m_game_state.player->add_cash(50);
            GLuint platform_texture_id = Utility::load_texture("chest_open.png");
            Entity *res = m_game_state.player->get_collide_obj();
            res->set_texture_id(platform_texture_id);
            Mix_PlayChannel(-1, m_game_state.die_sfx, 0);
            m_game_state.player->set_return(false);
            
            
        }
        else {
            m_game_state.player->set_return(false);
        }
    }
    
    std::cout << m_game_state.player->get_position().x << " " << m_game_state.player->get_position().y << std::endl;
    
}

void LevelC::render(ShaderProgram *program)
{
    m_game_state.map->render(program);
    m_game_state.player->render(program);
    for (int i = 0; i < ENEMY_COUNT; i++)    m_game_state.enemies[i].render(program);
    for (int i = 0; i < CHEST_COUNT; i++)   m_game_state.platforms[i].render(program);
    
    glm::vec3 res = m_game_state.player->get_position();
//    res.x -= 8.0f;
//    res.y += 6.0f;
    res.x -= 4.5f;
    res.y += 3.0f;
    Utility::draw_text(program, g_font_texture_id_8, "cash: $" + std::to_string(m_game_state.player->get_cash()), 0.35f, 0.05f, res);
    
    Utility::draw_text(program, g_font_texture_id_8, "Level 3", 0.35f, 0.05f, glm::vec3(res.x + 6.0f, res.y, res.z));
}
