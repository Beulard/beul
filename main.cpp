#include <iostream>
#include "SFML/Audio.hpp"
#include "Player.hpp"
#include "Grid.hpp"
#include "Map.hpp"
#include "World.hpp"

const float ComputeFrameRate(const double frameTime){
    return 1/frameTime;
}

using namespace std;

int main()
{
    sf::RenderWindow App(sf::VideoMode(1280, 720, 32), "Beul's Project"/*, sf::Style::Fullscreen*/);
    App.SetPosition(-8, 0);
    App.SetFramerateLimit(60);

    sf::View View(App.GetDefaultView());

    sf::Music Epic;
    Epic.OpenFromFile("resources/Nyan.ogg");
    Epic.Play();
    Epic.SetVolume(100);

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
    Frame b1(Hero, 0.5f);
    Frame b2(Hero2, 0.5f);
    BeulIdle.AddFrame(b1);
    BeulIdle.AddFrame(b2);

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


    cout << tileList.size() << " tiles in the Tiles List." << endl;
    cout << itemList.size() << " items in the Items List." << endl;
    cout << missileList.size() << " missiles in the Missiles List." << endl;
    cout << frameList.size() << " frames in the Frames List." << endl;
    cout << animationList.size() << " animations in the Animations List." << endl;

    //map.ComputeCollisions();


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
            Beul.AccelerateLeft();
        else if(App.GetInput().IsKeyDown(sf::Key::D))
            Beul.AccelerateRight();
        else
            Beul.Decelerate();

        if(App.GetInput().IsKeyDown(sf::Key::L))
            App.SetFramerateLimit(5);


        int MouseX = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY()).x;
        int MouseY = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY()).y;


        //cout << MouseX << endl << MouseY << endl;
        if(App.GetInput().IsMouseButtonDown(sf::Mouse::Left))
            Beul.UseWeapon(world, MouseX, MouseY);
        Beul.Reload(App.GetFrameTime());


        if(App.GetInput().IsKeyDown(sf::Key::Space) && jump == false){
            jump = true;
            Beul.SetYAcceleration(-10.5f);
        }

        if(App.GetInput().IsKeyDown(sf::Key::R)){
            for(unsigned int i=0; i<map.GetElements().size(); ++i){
                for(unsigned int j=0; j<map.GetElements()[i].size(); ++j){
                    if(map.TileExists(i, j))
                        map.DeleteElement(i, j);
                }
            }
            map = Map(2, App.GetHeight());
            map.GenerateRandomElements();
            //map.ComputeCollisions();
        }




        int nbrCollisions = 0;

        //for(unsigned int i=0; i<map.GetCollisions().size(); ++i){
        //for(unsigned int i=0; i<iCollisions.size(); ++i){
        for(unsigned int i=0; i<map.GetElements().size(); ++i){
            for(unsigned int j=0; j<map.GetElements()[i].size(); ++j){
                //if(map.GetTile(i, j)->Collides()){
                    if(Beul.WillCollision(*map.GetTile(i, j))){
                        if(map.GetTile(i, j)->Collides()){
                            Beul.Collide(*map.GetTile(i, j));
                            nbrCollisions += 1;
                        }
                        map.GetElements()[i][j]->onCollision(world);
                    }
                    if(map.GetTile(i, j)->Collides()){
                        if(Beul.WillDownCollision(*map.GetTile(i, j)))
                            jump = false;



                        if(Beul.WillUpCollision(*map.GetTile(i, j)))
                            hasUpCollided = true;
                    }

                //}
            }
        }



        for(unsigned int i=0; i<map.GetElements().size(); ++i){
            for(unsigned int j=0; j<map.GetElements()[i].size(); ++j){
                for(unsigned int k=0; k<world.missiles.size(); ++k){
                    if(world.missiles[k]->Collision(*map.GetElements()[i][j])/* && map.GetElements()[i][j]->Collides()*/){
                        world.missiles[k]->onCollision(world, i, j, k);
                    }
                }
            }
        }


        for(unsigned int i=0; i<map.GetItems().size(); ++i){
            if(Beul.WillCollision(*map.GetItems()[i])){
                map.GetItems()[i]->onGet(world);
                map.DeleteItem(i);
            }
        }

        musicTimelapse += App.GetFrameTime();

//        if(musicTimelapse >= Epic.GetDuration() + 2){
//            Epic.Play();
//            musicTimelapse = 0;
//        }

        if(nbrCollisions == 0)
            jump = true;

        //cout << nbrCollisions << endl;

        if(jump == true)
            Beul.Fall();

        App.Clear(sf::Color(85, 85, 85));
        map.Draw(App);
        //grid.Draw(App);


        frameRateString.SetText(IntToString(ComputeFrameRate(App.GetFrameTime())));


        Beul.Move();

        if(jump == false)
            Beul.SetYAcceleration(0);


        if(hasUpCollided){
            Beul.SetYAcceleration(0);
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

        if(App.GetInput().IsKeyDown(sf::Key::X))
            App.Draw(Secret);
        App.Display();

        if(Beul.GetLives() == 0){
            stop = true;
            App.Close();
        }


        }


    return 0;
}
