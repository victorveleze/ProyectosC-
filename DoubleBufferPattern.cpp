#include <iostream>

class Actor
{
public:
    Actor() : currentSlapped_(false){}

    virtual ~Actor() {}
    virtual void update() = 0;

    void swap() 
    { 
        currentSlapped_ = nextSlapped_;
        nextSlapped_ = false;
    }
    void slap() { nextSlapped_ = true; }
    bool wasSlapped() const { return currentSlapped_; }

private:
    bool currentSlapped_;
    bool nextSlapped_;
};

class Stage
{
public:
    void add(Actor* actor, int index) { actors_[index] = actor; }
    void update()
    {
        for (int i = 0; i < NUM_ACTORS; i++)
            actors_[i]->update();

        for (int i = 0; i < NUM_ACTORS; i++)
            actors_[i]->swap();
    }

private:
    static const int NUM_ACTORS = 3;
    Actor* actors_[NUM_ACTORS];
};

class Comedian : public Actor
{
public:
    void face(Actor* actor) { facing_ = actor; }
    virtual void update()
    {
        if (wasSlapped())
            facing_->slap();
    }
private:
    Actor* facing_;
};

int main()
{
    Comedian* Pedro = new Comedian;
    Comedian* Juan = new Comedian;
    Comedian* Pablo = new Comedian;

    Stage stageOne;
    stageOne.add(Pedro,0);
    stageOne.add(Juan,1);
    stageOne.add(Pablo,2);

    Pedro->face(Juan);
    Pedro->slap();

    Juan->face(Pablo);
    Juan->slap();

    stageOne.update();

    std::cout << Juan->wasSlapped() << std::endl;
    std::cout << Pedro->wasSlapped() << std::endl;

}

