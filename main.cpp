#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <stdio.h>


using namespace std;

int main()
{
    string directory;
    sf :: Image pic;
    sf :: Vector2u siz;//size of picture
    sf :: Vector2u res;//number if characters per row
    sf::Text aPic;
    unsigned int R;
    unsigned int G;
    unsigned int B;
    int pixBox;//number of pixels in a row of the character square
    int sharpSize;
    char ascii[]{'$','@','B','%','8','&','W','M','h','k','b','d','p','q','w','m','Z','O','0','Q','L','C','J','U','Y','X','z','c','v','u','n','x','r','j','f','t','/','|','(',')','1','{','}','[',']','?','-','_','+','~','<','>','i','!','l','I',';',':',',','^','`','.',' '};//all ascii characters
    int asciiSiz = sizeof(ascii)/sizeof(ascii[0]);

    cout<<"Give the directory of your .jpg image";
    cin>>directory;
    pic.loadFromFile(directory);
    siz = pic.getSize();

    cout<<endl<<"Give the resolution of the ascii picture(number of pixels per ascii character)";
    cin>>pixBox;
    res.x=siz.x/pixBox;
    res.y = siz.y/(2*pixBox);
    sf :: Color boxAvCol[res.x][res.y];
    sf :: Color Col;
    unsigned int rgbRange[res.x][res.y];//range of the color in an integer scale
    char asciiPic[res.x][res.y];//final array with the result
    string asciiStr;

    cout<<endl<<"Give the sharpness of the ascii picture(number of ascii characters)";
    cin>>sharpSize;
    char sharp[sharpSize];
    int numSharp=asciiSiz/sharpSize;//number of the characters in the ascii array substituted by one character

    for(int i = 0; i<res.y; i++){//getting colours of boxes
        for(int j=0; j<res.x; j++){
            R=0;
            G=0;
            B=0;
            for(int f=0; f<2*pixBox; f++){
                for(int g=0; g<pixBox; g++){
                    Col= pic.getPixel (pixBox*j+g,2*pixBox*i+f);
                    R+=Col.r*Col.r;
                    G+=Col.g*Col.g;
                    B+=Col.b*Col.b;
                }
            }
            boxAvCol[j][i].r = sqrt(R/(pixBox*(2*pixBox)))*0.2126;//box average color r with adjustment to the human eye sensitivity
            boxAvCol[j][i].g = sqrt(G/(pixBox*(2*pixBox)))*0.7152;//box average color g with adjustment to the human eye sensitivity
            boxAvCol[j][i].b = sqrt(B/(pixBox*(2*pixBox)))*0.0722;//box average color b with adjustment to the human eye sensitivity
            rgbRange[j][i]=((boxAvCol[j][i].r<<16)|(boxAvCol[j][i].g<<8)|(boxAvCol[j][i].b));
        }
    }
    for(int i = 0; i<res.y; i++){//setting picture with average colors
        for(int j=0; j<res.x; j++){
            for(int f=0; f<2*pixBox; f++){
                for(int g=0; g<pixBox; g++){
                    pic.setPixel(pixBox*j+g,2*pixBox*i+f,boxAvCol[j][i]);
                }
            }
        }
    }
    int numRGB= 16777216/sharpSize;//size of a single character shade

    for(int r=0; r<sharpSize; r++){
        sharp[r]=ascii[r*numSharp+numSharp/2-1];
    }
    for(int i=0; i<res.y; i++){
        for(int j=0; j<res.x; j++){
            for(int h=0; h<sharpSize; h++){
                if(rgbRange[j][i]>numRGB*h && rgbRange[j][i]<numRGB*(h+1)){
                    asciiPic[j][i]=sharp[h];
                    asciiStr+=asciiPic[j][i];
                    break;
                }
            }
        }
        asciiStr+="\n";
    }
    /*for(int j=0; j<res.y; j++){
            cout<<asciiStr<<endl;

    }*/
    sf::RenderWindow window(sf::VideoMode(5*res.x,10*res.y), "ASCII picture out");//create a window
    aPic.setString(asciiStr);
    aPic.setCharacterSize(8);
    sf::Font font;
    font.loadFromFile("fonts/consola.ttf");
    aPic.setFont(font);

    while (window.isOpen())
    {

       sf::Event event;
       while (window.pollEvent(event))
       {

           if (event.type == sf::Event::Closed)
               window.close();
       }

            window.clear();
            window.draw(aPic);
            window.display();

    }
    pic.saveToFile("Pictures/result.jpg");

    getchar();getchar();
    return 0;
}
//C:\Users\antek\Pictures\life.png
//C:\Users\antek\Pictures\istockphoto-908683668-170667a.jpg
//C:\Users\antek\Pictures\fgsa.jpg
//C:\Users\antek\Pictures\antek.jpg
//C:\Users\antek\Pictures\leonardo.jpg
//C:\Users\antek\Pictures\mona-lisa_1.jpeg
//C:\Users\antek\Pictures\901b198f2efb64287c76fd9243773a9d.jpg
//C:\Users\antek\Pictures\doga.jpg
//C:\Users\antek\Pictures\gf.jpg
