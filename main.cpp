#include <iostream>
#include "SFML/Audio.hpp"
#include "Player.hpp"
#include "Grid.hpp"
#include "Map.hpp"
#include "World.hpp"

void ComputeFrameRate(const double frameTime, double& rate, unsigned int& frames, unsigned int& frameRate){
    rate += frameTime;
    frames += 1;
    if(rate >= 1){
        rate = 0;
        frameRate = frames;
        frames = 0;
    }
}

const float gravity = 0.5f;

using namespace std;

int main()
{
    sf::RenderWindow App(sf::VideoMode(1024, 576, 32), "Beul's Project"/*, sf::Style::Fullscreen*/);
    App.SetPosition(100, 0);
    App.SetFramerateLimit(56);

    sf::View View(App.GetDefaultView());

    sf::Music Epic;
    Epic.OpenFromFile("resources/Epic.ogg");
    Epic.Play();
    Epic.SetVolume(0);

    sf::Image Heroimg;
    Heroimg.LoadFromFile("resources/Beul.png");
    sf::Image Hero2img;
    Hero2img.LoadFromFile("resources/Beul2.png");
    sf::Image Squareimg;
    Squareimg.LoadFromFile("resources/square.png");

    sf::Sprite Square;
    Square.SetImage(Squareimg);

    sf::Sprite Hero;
    Hero.SetImage(Heroimg);
    sf::Sprite Hero2;
    Hero2.SetImage(Hero2img);

    sf::Font font;
    font.LoadFromFile("resources/SRF2.ttf");


    Animation BeulIdle;

    BeulIdle.AddFrame(Frame(Hero, 0.5f));
    BeulIdle.AddFrame(Frame(Hero2, 0.5f));

    Player Beul;
    Beul.SetAnimation(BeulIdle);
    //Grid grid(App);
    Map map(2, App.GetHeight());
    World world(map, Beul);
    map.GenerateRandomElements();


    map.AddItem(ROCKETLAUNCHER, 10, 10);


    sf::Shape BeulLives = sf::Shape::Rectangle(5, 15, 96, 20, sf::Color::Green, 1.f, sf::Color::Blue);
    BeulLives.EnableFill(true);

    //Beul.Move();

    float musicTimelapse = 0;


    bool jump = false;
    bool hasUpCollided = false;


    sf::String frameRateString("", font, 18);
    frameRateString.SetColor(sf::Color::Yellow);
    double rate = 0;
    unsigned int frames = 0;
    unsigned int frameRate = 0;


    //map.GetCollisions();


    //cout << iCollisions.size() << " AABBs on the map you can collide with." << endl;
    cout << itemList.items.size() << " items in the Items List" << endl;

    //std::vector<TileAABB**> collisions = map.GetCollisions();
    map.ComputeCollisions();
    //cout << map.GetCollisions().size() << endl;

    sf::String Secret("GG", font, 18);
    Secret.SetPosition(100, 50);
    Secret.SetColor(sf::Color::Green);


    App.SetView(View);


    bool stop = false;
    sf::Event Event;


    while(stop == false){
        while(App.GetEvent(Event))
            if(App.GetInput().IsKeyDown(sf::Key::Escape))
                stop = true;

        if(App.GetInput().IsKeyDown(sf::Key::Q))
            Beul.SetXVelocity(-4);
        else if(App.GetInput().IsKeyDown(sf::Key::D))
            Beul.SetXVelocity(4);
        else
            Beul.SetXVelocity(0);


        int MouseX = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY()).x;
        int MouseY = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY()).y;


        //cout << MouseX << endl << MouseY << endl;
        if(App.GetInput().IsMouseButtonDown(sf::Mouse::Left)){
            Beul.UseWeapon(world, MouseX, MouseY);
        }
        Beul.Reload(App.GetFrameTime());

        if(App.GetInput().IsKeyDown(sf::Key::Space) && jump == false){
            jump = true;
            Beul.SetYVelocity(-10);
        }



        int nbrCollisions = 0;

        //for(unsigned int i=0; i<map.GetCollisions().size(); ++i){
        //for(unsigned int i=0; i<iCollisions.size(); ++i){
        for(unsigned int i=0; i<map.GetElements().size(); ++i){
            for(unsigned int j=0; j<map.GetElements()[i].size(); ++j){
            //TileAABB* t = dynamic_cast<TileAABB*>(map.GetElements()[iCollisions[i]][jCollisions[i]]);
            //auto t = map.GetElements()[i][j]->Clone();
            //auto t = ().Clone();
            //if(t->GetID() != SKY){
            //if((*(*(map.GetCollisions()[i]))).Collides()){
            if(map.GetTile(i, j)->Collides()){

                if(Beul.GetCollisionLimit()->WillCollision(*map.GetElements()[i][j])){
                    if(Beul.WillCollision(*map.GetElements()[i][j])){
                        Beul.Collide(*map.GetTile(i, j));
                        nbrCollisions += 1;
                    }
                }
                if(Beul.WillDownCollision(*map.GetElements()[i][j])){
                    jump = false;
                    /*if(Beul.YVelocity() > 15)
                        Beul--;*/
                }


                if(Beul.WillUpCollision(*map.GetElements()[i][j]))
                    hasUpCollided = true;


            }
            //}
            //}
        }
        }


        for(unsigned int k=0; k<world.missiles.size(); ++k){
            for(unsigned int i=0; i<map.GetElements().size(); ++i){
                for(unsigned int j=0; j<map.GetElements()[i].size(); ++j){
                    if(world.missiles[k]->WillCollision(*map.GetElements()[i][j]) && map.GetElements()[i][j]->Collides()){
                        //cout << iCollisions[i] << endl << jCollisions[i] << endl;
                        world.missiles[k]->onCollision(world, k, i, j);
                        //cout << "poney" << endl;
                    }
                }
            }
        }

        for(unsigned int i=0; i<map.GetItems().size(); ++i){
            if(Beul.WillCollision(*map.GetItems()[i])){
                map.GetItems()[i]->onGet(world);
                map.DeleteItem(i);
                //std::cout << map.GetItems()[i]->GetID() << std::endl;
            }
        }




        //cout << nbrCollisions << endl;

        musicTimelapse += App.GetFrameTime();

//        if(musicTimelapse >= Epic.GetDuration() + 2){
//            Epic.Play();
//            musicTimelapse = 0;
//        }

        if(nbrCollisions == 0)
            jump = true;
        //cout << nbrCollisions << endl;

        if(jump == true)
            Beul.SetYVelocity(Beul.YVelocity() + gravity);

        App.Clear(sf::Color(85, 85, 85));
        map.Draw(App);
        //grid.Draw(App);

        ComputeFrameRate(App.GetFrameTime(), rate, frames, frameRate);
        frameRateString.SetText(IntToString(frameRate));


        Beul.Move();

        if(jump == false)
            Beul.SetYVelocity(0);


        if(hasUpCollided){
            Beul.SetYVelocity(0);
            hasUpCollided = false;
        }



        View.SetCenter(Beul.Left() + Beul.Width() / 2, App.GetDefaultView().GetCenter().y);
        if(View.GetRect().Left <= dynamic_cast<TileAABB*>(map.GetElements()[0][0])->Left())
            View = App.GetDefaultView();

        else if(View.GetRect().Right >= dynamic_cast<TileAABB*>(map.GetElements()[map.GetNbrColumns() - 1][0])->Right())
            View.SetCenter(dynamic_cast<TileAABB*>(map.GetElements()[map.GetNbrColumns() - 1][0])->Right() - App.GetDefaultView().GetHalfSize().x, App.GetDefaultView().GetCenter().y);

        BeulLives.SetPosition(App.ConvertCoords(5, 15, &View));
        BeulLives.SetPointPosition(1, Beul.GetLives()*32 + 5, 15);
        BeulLives.SetPointPosition(2, Beul.GetLives()*32 + 5, 20);

        Secret.Move(2, 0);
        Square.SetPosition(Beul.Left() - 25, Beul.Up() - 25);
        App.Draw(Square);
        Beul.Draw(App);
        frameRateString.SetPosition(App.ConvertCoords(5, 2, &View));
        App.Draw(frameRateString);
        App.Draw(BeulLives);

        world.Draw(App);

        //cout << Beul.GetWeaponID() << endl;

        if(App.GetInput().IsKeyDown(sf::Key::X))
            App.Draw(Secret);
        App.Display();
    }

    return 0;
}
