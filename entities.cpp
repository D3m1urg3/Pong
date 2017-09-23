#include "entities.h"

// Entity
std::vector<Entity*> Entity::entities;

Entity::Entity(uint x, uint  y, const Entity_type& type)
    :_x(x),
    _y(y),
    _x_min(-1),
    _x_max(-1),
    _y_min(-1),
    _y_max(-1),
    sprite(nullptr),
    collider(nullptr),
    body(nullptr),
    mind(nullptr),
    _type(type),
    tag(nullptr)
{
    entities.push_back(this);
}

Entity::Entity(uint x, uint  y, const Entity_type& type, char* tag)
    :_x(x),
    _y(y),
    _x_min(-1),
    _x_max(-1),
    _y_min(-1),
    _y_max(-1),
    sprite(nullptr),
    collider(nullptr),
    body(nullptr),
    mind(nullptr),
    _type(type),
    tag(tag)
{
    entities.push_back(this);
}

Entity::~Entity()
{
    delete sprite;
    delete collider;
    delete body;
    delete mind;
    for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        if (*it == this)
        {
            entities.erase(it);
            break;
        }
    }
}

bool Entity::attach(AI* brain)
{
    if (brain != nullptr)
    {
        delete mind;
        mind = brain;
        return true;
    }
    return false;
}

bool Entity::attach(Body* bdy)
{
    if (bdy != nullptr)
    {
        delete body;
        body = bdy;
        return true;
    }
    return false;
}

bool Entity::attach(Sprite* sprt)
{
    if (sprt != nullptr)
    {
        delete sprite;
        sprite = sprt;
        return true;
    }
    return false;
}

bool Entity::attach(Collider* col)
{
    if (col != nullptr)
    {
        delete collider;
        collider = col;
        return true;
    }
    return false;
}

void Entity::set_position(uint x, uint y)
{
    _x = x; 
    _y = y;
    if (collider != nullptr)
    {
        collider->set_position(x, y);
    }
    if (body != nullptr)
    {
        body->set_position(x, y);
    }
}

void Entity::set_max_positions(int x_min, int x_max, int y_min, int y_max) 
{ 
    _x_min = x_min; 
    _x_max = x_max; 
    _y_min = y_min; 
    _y_max = y_max; 
}

void Entity::draw(Renderer* render, uint x, uint y)
{
    if (sprite != nullptr)
    {
        sprite->set_dst_rect(x, y, sprite->get_sprite_width(), sprite->get_sprite_height());
        sprite->draw(render);
    }
}

void Entity::draw(Renderer* render)
{
    if (sprite != nullptr)
    {
        sprite->set_dst_rect(_x, _y, sprite->get_sprite_width(), sprite->get_sprite_height());
        sprite->draw(render);
    }
}

bool Entity::is_valid_position(uint x, uint y)
{
    bool valid_x = true;
    if (_x_min >= 0 && _x_max >= 0)
    {
        valid_x = (_x_min <= x) && (x <= _x_max);
    }
    bool valid_y = true;
    if (_y_min >= 0 && _y_max >= 0)
    {
        valid_y = (_y_min <= y) && (y <= _y_max);
    }

    return (valid_x && valid_y);
}

void Entity::move()
{
    if (body != nullptr)
    {
        uint x_new = _x;
        uint y_new = _y;
        body->calculate_new_positions(x_new, y_new);
        if(is_valid_position(x_new, y_new))
        {
            body->move(_x,_y);
            if (collider != nullptr)
            {
                collider->set_position(_x, _y);
            }
        }
    }
}

Entity* Entity::search_for_entity(char* identifier)
{
    for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        Entity* entity = *it;
        if (entity != nullptr && entity->id() == identifier)
        {
            return entity;
        }
    }
    return nullptr;
}

// Player
Player::Player(Texture* spritesheet, Controls* ctrl, uint x, uint y, uint v_x, uint v_y)
    :Entity(x,y, PLAYER, "player"),
    paddle_vel_x(v_x),
    paddle_vel_y(v_y)
{
    set_max_positions(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);

    attach(new Sprite(spritesheet, paddle_sprite_x, paddle_sprite_y, paddle_sprite_w, paddle_sprite_h));
    attach(new Body( player_init_x +  paddle_sprite_w/2, player_init_y +  paddle_sprite_w/2, 0, 0 )); // Center of the entity
    attach(new Box_collider(player_init_x, player_init_y, paddle_sprite_w, paddle_sprite_h));

    if (ctrl != nullptr)
    {
        control = ctrl;
    }
}

Player::~Player()
{}

void Player::update()
{
    switch (*control)
    {
    case NONE:
        body->set_velocity(0, 0);
        break;
    case UP:
        body->set_velocity(paddle_vel_x, -1*paddle_vel_y);
        break;
    case DOWN:
        body->set_velocity(paddle_vel_x, paddle_vel_y);
        break;
    }
    move();
}

// Opponent
Opponent::Opponent(Texture* spritesheet, uint x, uint y, uint v_x, uint v_y)
    :Entity(x,y, OPPONENT, "opponent"),
    paddle_vel_x(v_x),
    paddle_vel_y(v_y)
{
    set_max_positions(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    attach(new Sprite(spritesheet, paddle_sprite_x, paddle_sprite_y, paddle_sprite_w, paddle_sprite_h));
    attach(new Body( opponent_init_x +  paddle_sprite_w/2, opponent_init_y +  paddle_sprite_w/2, 0, 0 )); // Center of the entity
    attach(new Box_collider(opponent_init_x, opponent_init_y, paddle_sprite_w, paddle_sprite_h));

    Entity* ball = search_for_entity("ball");
    attach(new AI(body, ball));
}

Opponent::~Opponent()
{}

void Opponent::update()
{
    if (mind != nullptr)
    {
        mind->act();
        move();
    }
}

// Ball
Ball::Ball(Texture* spritesheet, uint x, uint y, uint v_x, uint v_y, Sound* paddle, Sound* edge, Sound* score)
    :Entity(x,y, BALL, "ball"),
    ball_init_pos_x(x),
    ball_init_pos_y(y),
    ball_init_vel_x(v_x),
    ball_init_vel_y(v_y),
    paddle_beep(paddle),
    edge_beep(edge),
    score_beep(score)
{
    if (spritesheet != nullptr)
    {
        attach(new Sprite(spritesheet, ball_sprite_x, ball_sprite_y, ball_sprite_w, ball_sprite_h));
        attach(new Body( ball_init_x +  ball_sprite_w/2, ball_init_y +  ball_sprite_w/2, 0, 0 )); // Center of the entity
        attach(new Box_collider(ball_init_x, ball_init_y, ball_sprite_w, ball_sprite_h));
        body->set_velocity(ball_init_vel_x, ball_init_vel_y);
    }
}

Ball::~Ball()
{}

void Ball::update()
{
    int ball_vel_x = body->get_velocity_x();
    int ball_vel_y = body->get_velocity_y();

    std::vector<Entity*>::iterator it;
    for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        Entity* other = *it;
        if (this->collider->is_colliding_with(other->collider))
        {
            switch (other->type())
            {
            case PLAYER:
                // Physics
                body->set_velocity(-1 * ball_vel_x, ball_vel_y);

                // Sound
                if (paddle_beep != nullptr)
                {
                    paddle_beep->play();
                }
                break;
            case OPPONENT:
                // Physics
                body->set_velocity(-1 * ball_vel_x, ball_vel_y);

                // Sound
                if (paddle_beep != nullptr)
                {
                    paddle_beep->play();
                }
                break;
            case BORDER:
                Border* border = static_cast<Border*>(other);
                switch (border->position())
                {
                case TOP:
                    // Physics
                    body->set_velocity(ball_vel_x, -1 * ball_vel_y);

                    // Sound
                    if (edge_beep != nullptr)
                    {
                        edge_beep->play();
                    }
                    break;
                case BOTTOM:
                    // Physics
                    body->set_velocity(ball_vel_x, -1 * ball_vel_y);

                    // Sound
                    if (edge_beep != nullptr)
                    {
                        edge_beep->play();
                    }
                    break;
                case LEFT:
                {
                    // Physics
                    set_position(ball_init_pos_x, ball_init_pos_y);
                    body->set_velocity( random_sign() * ball_init_vel_x, random_sign() * ball_init_vel_y );

                    // Score
                    Scoreboard* opponent_scoreboard = static_cast<Scoreboard*>(search_for_entity("opponent_board"));
                    if (opponent_scoreboard != nullptr)
                    {
                        opponent_scoreboard->raise();
                    }

                    // Sound
                    if (score_beep != nullptr)
                    {
                        score_beep->play();
                    }

                }
                    break;
                case RIGHT:
                {
                    // Physics
                    set_position(ball_init_pos_x, ball_init_pos_y);
                    body->set_velocity( random_sign() * ball_init_vel_x, random_sign() * ball_init_vel_y );

                    // Score
                    Scoreboard* player_scoreboard = static_cast<Scoreboard*>(search_for_entity("player_board"));
                    if (player_scoreboard != nullptr)
                    {
                        player_scoreboard->raise();
                    }

                    //Sound
                    if (score_beep != nullptr)
                    {
                        score_beep->play();
                    }

                }
                    break;
                }
                break;
            }
        }
    }
    move();
}

// Border
Border::Border(Edge_position pos, uint screen_w, uint screen_h)
    :Entity(0, 0, BORDER),
    _position(pos)
{
    attach(new Edge_collider(pos, screen_w, screen_h));
}

Border::~Border()
{
    delete collider;
}

// Scoreboard
Scoreboard::Scoreboard(Texture* spritesheet, uint x, uint y, char* board_id)
    :score(0),
    Entity(x, y, SCOREBOARD, board_id)
{
    SDL_Rect numbers_specs[10] =
    {   // {x,y,w,h}
        {4, 3, 16, 32},   //0
        {23, 3, 4, 32},   //1
        {30, 3, 16, 32},  //2
        {49, 3, 16, 32},  //3
        {68, 3, 16, 32},  //4
        {87, 3, 16, 32},  //5
        {106, 3, 16, 32}, //6
        {125, 3, 16, 32}, //7
        {144, 3, 16, 32}, //8
        {163, 3, 16, 32}, //9
    };

    for (int i = 0; i < 10; ++i)
    {
        numbers[i] = new Sprite(spritesheet, numbers_specs[i].x, numbers_specs[i].y, numbers_specs[i].w, numbers_specs[i].h);
        numbers[i]->set_dst_rect(x, y, numbers_specs[i].w, numbers_specs[i].h);
    }
}

Scoreboard::~Scoreboard()
{
    for (int i = 0; i < 10; ++i)
    {
        delete numbers[i];
    }
}

void Scoreboard::draw(Renderer* render)
{
    if (score < 10)
    {
        numbers[score]->draw(render);
    }
}

// AI
AI::AI(Body* body, Entity* ball)
    :mybody(body),
    ball(ball)
{}

void AI::act()
{
    bool do_something = (rand() % 100 <= 20);
    int ball_position_error = rand() % 4 - 2;

    if (do_something && ball != nullptr && mybody != nullptr)
    {
        int ball_y = ball->get_y() + ball_position_error;
        if (ball_y < mybody->get_y())
        {
            mybody->set_velocity(0, -4);
        }
        else if (ball_y > mybody->get_y())
        {
            mybody->set_velocity(0, 4);
        }
        else
        {
            mybody->set_velocity(0, 0);
        }
    }
}