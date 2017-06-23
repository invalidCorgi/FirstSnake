#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

sf::Texture text_load(std::string name)
{
    sf::Texture tekstura;
    tekstura.loadFromFile(name);
    return tekstura;
}

void przesun(int x, int y, int poz_weza[][2], int rozm_weza)
{
    for(int i=rozm_weza-1; i>0; i--)
    {
        poz_weza[i][0]=poz_weza[i-1][0];
        poz_weza[i][1]=poz_weza[i-1][1];
    }
    poz_weza[0][0]+=x;
    poz_weza[0][1]+=y;
}

bool sprawdz(int x, int y, int poz_weza[][2], int rozm_weza, bool kon = false)
{
    if(kon==false)
    {
        for(int i=rozm_weza-1; i>=0; i--)
            if(poz_weza[i][0]==x && poz_weza[i][1]==y)
                return false;
    }
    else
    {
        for(int i=rozm_weza-1; i>0; i--)
            if(poz_weza[i][0]==x && poz_weza[i][1]==y)
                return false;
    }
    return true;
}


int main()
{
    sf::RenderWindow okno( sf::VideoMode( 800, 600, 32 ), "Snake - Wojciech Regulski");

    okno.setFramerateLimit(60);

    /*sf::Texture tekstura;
    if(!tekstura.loadFromFile("wonszgrzyb.png"))
        return 404;*/

    sf::Texture tekstura=text_load("wonszgrzyb.png");
    sf::Texture tekstura3=text_load("japkomario.png");
    sf::Texture tekstura5=text_load("zlyslimak.png");
    sf::Texture tekstura6=text_load("kotwica.png");

    sf::Sprite obrazek;
    obrazek.setTexture(tekstura);

    obrazek.setPosition(160,0);

    /*sf::Texture tekstura3;
    if(!tekstura3.loadFromFile("japkomario.png"))
        return 404;*/



    sf::Sprite japko;
    japko.setTexture(tekstura3);

    /*sf::Texture tekstura5;
    if(!tekstura5.loadFromFile("zlyslimak.png"))
        return 404;*/

    sf::Sprite slimak;
    slimak.setTexture(tekstura5);

    /*sf::Texture tekstura6;
    if(!tekstura6.loadFromFile("kotwica.png"))
        return 404;*/

    sf::Sprite zwalniacz;
    zwalniacz.setTexture(tekstura6);

    srand(time(0));

    int poz_x_jap;
    int poz_y_jap;
    int poz_x_sli;
    int poz_y_sli;
    int poz_x_zwa;
    int poz_y_zwa;
    int rozm_weza=3;

    int predkosc=0;

    int poprz_predkosc=0;
    bool Slimak=0;

    int ost_poz_x;
    int ost_poz_y;

    int poz_weza[80][2];
    poz_weza[0][0]=160;
    poz_weza[0][1]=0;
    poz_weza[1][0]=80;
    poz_weza[1][1]=0;
    poz_weza[2][0]=0;
    poz_weza[2][1]=0;

    do
    {
          poz_x_jap=(std::rand()%10)*80;
          poz_y_jap=(std::rand()%8)*75;
    }while(!sprawdz(poz_x_jap, poz_y_jap, poz_weza, rozm_weza));

    japko.setPosition(poz_x_jap,poz_y_jap);

    do
    {
          poz_x_sli=(std::rand()%10)*80;
          poz_y_sli=(std::rand()%8)*75;
    }while( (!sprawdz(poz_x_sli, poz_y_sli, poz_weza, rozm_weza)) || ( poz_x_jap==poz_x_sli && poz_y_jap==poz_y_sli ) );

    slimak.setPosition(poz_x_sli,poz_y_sli);

    sf::Texture tekstura2;
    if(!tekstura2.loadFromFile("koniec.png"))
        return 404;

    sf::Sprite koniec;
    koniec.setTexture(tekstura2);

    sf::Clock stoper;

    bool left=0;
    bool up=0;
    bool right=1;
    bool down=0;
    bool Koniec=0;
    bool Zwa=0;

    std::string poprz="right";

    while( okno.isOpen() )
    {
        okno.clear();
        sf::Event event;
        while( okno.pollEvent( event ) )
        {
            if( event.type == sf::Event::Closed )
                 okno.close();
            if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape )
                 okno.close();
            if( event.type == sf::Event::TextEntered && event.text.unicode == 8 ) //8 w utf-32 to backspace
                 okno.close();
            if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && poprz!="left" )
            {
                left=0;
                right=1;
                up=0;
                down=0;
            }
            if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && poprz!="right" )
            {

                left=1;
                right=0;
                up=0;
                down=0;
            }
            if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && poprz!="down" )
            {

                left=0;
                right=0;
                up=1;
                down=0;
            }
            if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && poprz!="up" )
            {

                left=0;
                right=0;
                up=0;
                down=1;
            }
        }
        if(stoper.getElapsedTime().asMilliseconds()>=(350-(predkosc*8)))
        {
            stoper.restart();
            ost_poz_x=poz_weza[rozm_weza-1][0];
            ost_poz_y=poz_weza[rozm_weza-1][1];
            if(left==1 && poprz!="right")
                {przesun(-80,0,poz_weza,rozm_weza); poprz="left";}
            if(right==1 && poprz!="left")
                {przesun(80,0,poz_weza,rozm_weza); poprz="right";}
            if(up==1 && poprz!="down")
                {przesun(0,-75,poz_weza,rozm_weza); poprz="up";}
            if(down==1 && poprz!="up")
                {przesun(0,75,poz_weza,rozm_weza); poprz="down";}
        }

        if(obrazek.getPosition().x==japko.getPosition().x && obrazek.getPosition().y==japko.getPosition().y)
        {
            if(Slimak==1){predkosc=poprz_predkosc; Slimak=0;}
            predkosc++;
            poz_weza[rozm_weza][0]=ost_poz_x;
            poz_weza[rozm_weza][1]=ost_poz_y;
            rozm_weza++;
            if(rozm_weza<80)
            do
            {
                poz_x_jap=(std::rand()%10)*80;
                poz_y_jap=(std::rand()%8)*75;
            }while( (!sprawdz(poz_x_jap, poz_y_jap, poz_weza, rozm_weza)) || ( poz_x_jap==poz_x_sli && poz_y_jap==poz_y_sli ) || ( poz_x_jap==poz_x_zwa && poz_y_jap==poz_y_zwa ) );

            japko.setPosition(poz_x_jap,poz_y_jap);
        }

        okno.draw(japko);

        if( (obrazek.getPosition().x==slimak.getPosition().x && obrazek.getPosition().y==slimak.getPosition().y) && rozm_weza < 69 )
        {
            predkosc+=5;
            if(Slimak==0)poprz_predkosc=predkosc;
            Slimak=1;
            rozm_weza--;
            do
            {
                poz_x_sli=(std::rand()%10)*80;
                poz_y_sli=(std::rand()%8)*75;
            }while( (!sprawdz(poz_x_sli, poz_y_sli, poz_weza, rozm_weza)) || ( poz_x_jap==poz_x_sli && poz_y_jap==poz_y_sli ) || ( poz_x_zwa==poz_x_sli && poz_y_zwa==poz_y_sli ) );

            slimak.setPosition(poz_x_sli,poz_y_sli);
        }

        if(rozm_weza < 69)okno.draw(slimak);

        if(rozm_weza==69)slimak.setPosition(-200,-200);

        if(predkosc%5==0 && Zwa==0 && predkosc!=0 && rozm_weza < 69)
        {
            Zwa=1;
            do
            {
                poz_x_zwa=(std::rand()%10)*80;
                poz_y_zwa=(std::rand()%8)*75;
            }while( (!sprawdz(poz_x_zwa, poz_y_zwa, poz_weza, rozm_weza)) || ( poz_x_zwa==poz_x_sli && poz_y_zwa==poz_y_sli ) || ( poz_x_zwa==poz_x_jap && poz_y_zwa==poz_y_jap ));

            zwalniacz.setPosition(poz_x_zwa,poz_y_zwa);

        }

        if(Zwa==1 && rozm_weza < 69)okno.draw(zwalniacz);

        if(obrazek.getPosition().x==zwalniacz.getPosition().x && obrazek.getPosition().y==zwalniacz.getPosition().y)
            {predkosc-=4; Zwa=0; zwalniacz.setPosition(-100,-100);}

        for(int i=rozm_weza-1; i>=0; i--)
        {
            obrazek.setPosition(poz_weza[i][0],poz_weza[i][1]);
            okno.draw(obrazek);
        }

        if(!sprawdz(poz_weza[0][0], poz_weza[0][1], poz_weza, rozm_weza, true))
            Koniec=1;

        if(rozm_weza==0)
            Koniec=1;

        //if(obrazek.getPosition().x<0 || obrazek.getPosition().x>750 ||
           //obrazek.getPosition().y<0 || obrazek.getPosition().y>550 )
           //Koniec=1;
        if(Slimak==0)
        {
            if(poz_weza[0][0]==800)poz_weza[0][0]=0;
            if(poz_weza[0][0]==-80)poz_weza[0][0]=720;
            if(poz_weza[0][1]==600)poz_weza[0][1]=0;
            if(poz_weza[0][1]==-75)poz_weza[0][1]=525;
        }

        if(Slimak==1)
        {
            if(poz_weza[0][0]==800)Koniec=1;
            if(poz_weza[0][0]==-80)Koniec=1;
            if(poz_weza[0][1]==600)Koniec=1;
            if(poz_weza[0][1]==-75)Koniec=1;
        }

        if(Koniec==1)okno.draw(koniec);

        if(rozm_weza==79)
        {
            sf::Texture tekstura4;
            tekstura4.loadFromFile("wygryw.png");

            sf::Sprite wygryw;
            wygryw.setTexture(tekstura4);
            okno.draw(wygryw);
        }

        okno.display();
    } //while
    return 0;
}
