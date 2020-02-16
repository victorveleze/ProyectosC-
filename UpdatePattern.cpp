// UpdateMethod.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#define MAX_ENTITIES 5

class Entity
{
public:
    Entity()
    : m_x(0)
    , m_y(0)
    {}

    virtual ~Entity() {}
    virtual void update() = 0;

    double getX() const { return m_x; }
    double getY() const { return m_y; }

    void setX(double x) { m_x = x; }
    void setY(double y) { m_y = y; }

private:
    double m_x;
    double m_y;
};

class World
{
public:
    World()
    : m_numEntities(0)
    {}
    ~World() {}

    void gameLoop();
    void addEntity(Entity* entity)
    {
        m_entities[m_numEntities] = entity;
        m_numEntities++;
    }

private:
    Entity* m_entities[MAX_ENTITIES];
    int m_numEntities;
};

class Skeleton : public Entity
{
public:
    Skeleton(bool patrollingLeft)
    : m_patrollingLeft(patrollingLeft)
    {
        setX(m_patrollingLeft ? 100 : 0);
    }

    virtual void update()
    {
        if (m_patrollingLeft)
        {
            setX(getX() - 1);
            if (getX() == 0)
            {
                m_patrollingLeft = false;
                std::cout << "Patrolling right!" << std::endl;
            }
        }
        else
        {
            setX(getX() + 1);
            if (getX() == 100)
            {
                m_patrollingLeft = true;
                std::cout << "Patrolling left!" << std::endl;
            }
        }
    }
private:
    bool m_patrollingLeft;
};

class Statue : public Entity
{
public:
    Statue(int delay)
    : m_frames(0)
    , m_delay(delay)
    {}

    virtual void update()
    {
        if (++m_frames == m_delay)
        {
            shootingLight();
            m_frames = 0;
        }
    }

private:
    int m_frames;
    int m_delay;

    void shootingLight()
    {
        std::cout << "---- Lanzando rasho laser! ----" << std::endl;
    }
};


int main()
{
    std::cout << "Hello World!\n";
    World* myWorld = new World;
    Skeleton* skeleton1 = new Skeleton(false);
    Skeleton* skeleton2 = new Skeleton(true);
    Statue* statue = new Statue(60);

    myWorld->addEntity(skeleton1);
    myWorld->addEntity(skeleton2);
    myWorld->addEntity(statue);

    myWorld->gameLoop();
}

void World::gameLoop()
{
    while (true)
    {
        //Inputs()
        for (int i = 0; i < m_numEntities; i++)
        {
            m_entities[i]->update();
        }
        std::cin.get();
        //Physics()
        //Render()
    }
}