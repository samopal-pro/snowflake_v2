                                           /**
 * Цвето-динамическая снежинка на WS2812
 * Copyright (С) 2015 А.Шихарбеев
 * Проект
 * http://samopal.pro/ws2812-5
 * Число светодиодов в луче меняется от 5 до 8 переменной ray_pixel 
 */

#include <Adafruit_NeoPixel.h>

uint32_t buff[48];
uint8_t  mode[]  { 0,1,2,3,0,1,2,3,0,1,2,3,0,1 };

// Пин на который цепляются светодиоды
#define PIN 3
// Число лучей
int ray_number = 8;
// Число пикселей в луче
int ray_pixel  = 8;



int max_br     = ray_pixel*2;
int step_br    = 256/ray_pixel;

int TM = 50, DX = 2;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(ray_pixel*ray_number, PIN, NEO_GRB + NEO_KHZ800);

//NeoPixelBus strip = NeoPixelBus(48, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
// Скорость и глубина эффекта исходя из числа пикселей в луче   
  if( ray_pixel >= 8 ){
    TM = 40;
    DX = 2;
  }
  else if( ray_pixel > 6 ){
    TM = 55;
    DX = 2;
  }
  else {
    TM = 70;
    DX = 3;
  }
  
  strip.begin();
  strip.show(); 
}

void loop() {
   for( int i=0; i<14; i++ ){
       for( int j=0; j<6; j++){
          Mode1(TM,j,i);
          delay(100);
//          Mode1(70,j,i);
//          delay(300);
       } 
   }
}

/*
 * Эффект от центра
 */
void Mode1(uint16_t wait, uint8_t pair, uint8_t dir){
   for( int i1=0; i1<ray_pixel; i1++ ){
    
      for( int i2=0; i2<ray_pixel; i2++ ){
          SetStarColor1(ray_pixel-i2, 0, pair, dir);
      }

      SetStarColor1(ray_pixel-i1,15, pair, dir);
      for( int i2=0; i2<i1; i2++ ){
          SetStarColor1(ray_pixel-i2, 16-(i1-i2)*DX, pair, dir);
      }
     
      strip.show();
      delay(wait);
   }
   for( int i1=0; i1<ray_pixel; i1++ ){
      for( int i2=0; i2<ray_pixel; i2++ ){
         int c = 16-(i1-(i2-8))*2;
         if( c < 0 )c = 0;
         SetStarColor1(ray_pixel-i2,c, pair, dir);
      }

      strip.show();
      delay(wait);
   }
}


/**
 * Разгорание одного пиксела на каждом луче 
 */
void SetStarColor1( uint8_t n, uint8_t br, uint8_t pair, uint8_t dir ){
   if( n > ray_pixel )return;
   if( br > 15 )br=15;
   uint8_t r=0, g=0, b=0;
   if( br < 8 ){
      switch( pair ){
        case 0 :
        case 3 :
           r = br*32;
           break;
        case 1 :
        case 4 :
           g = br*32;
           break;
        case 2 :
        case 5 :
           b = br*32;
           break;
      }
   }
   else {
      switch( pair ){
         case 0 :
            r = 255;
            g = (br-8)*32;
            break;
         case 1 :
            g = 255;
            b = (br-8)*32;
            break;
         case 2 :
            b = 255;
            r = (br-8)*32;
            break;
         case 3 :
            r = 255;
            b = (br-8)*32;
            break;
         case 4 :
            g = 255;
            r = (br-8)*32;
            break;
         case 5 :
            b = 255;
            g = (br-8)*32;
            break;
      }
   }
   switch( dir ){
       case 1:
          for( int i=0; i<ray_number; i++ )strip.setPixelColor((ray_pixel-n)+i*ray_pixel, strip.Color(r,g,b)); 
          break;   
       case 2:
          for( int i=0; i<ray_number; i++ )
             if( i%2 )strip.setPixelColor(n-1+i*ray_pixel, strip.Color(r,g,b)); 
             else strip.setPixelColor((ray_pixel-n)+i*ray_pixel, strip.Color(r,g,b));
          break;    
       case 3:
          for( int i=0; i<ray_number; i++ )
             if( i%2 )strip.setPixelColor((ray_pixel-n)+i*ray_pixel, strip.Color(r,g,b));
             else strip.setPixelColor(n-1+i*ray_pixel, strip.Color(r,g,b)); 
          break;    
       case 4:
          for( int i=0; i<3; i++ )strip.setPixelColor(n-1+i*ray_pixel, strip.Color(r,g,b));    
          for( int i=3; i<ray_number; i++ )strip.setPixelColor((ray_pixel-n)+i*ray_pixel, strip.Color(r,g,b)); 
          break;   
       case 5:
          for( int i=0; i<1; i++ )strip.setPixelColor((ray_pixel-n)+i*ray_pixel, strip.Color(r,g,b));    
          for( int i=1; i<4; i++ )strip.setPixelColor(n-1+i*ray_pixel, strip.Color(r,g,b)); 
          for( int i=4; i<ray_number; i++ )strip.setPixelColor((ray_pixel-n)+i*ray_pixel, strip.Color(r,g,b));    
          break;   
       case 6:
          for( int i=0; i<2; i++ )strip.setPixelColor((ray_pixel-n)+i*ray_pixel, strip.Color(r,g,b));    
          for( int i=2; i<5; i++ )strip.setPixelColor(n-1+i*ray_pixel, strip.Color(r,g,b)); 
          for( int i=5; i<ray_number; i++ )strip.setPixelColor((ray_pixel-n)+i*ray_pixel, strip.Color(r,g,b));    
          break;   
       case 7:
          for( int i=0; i<3; i++ )strip.setPixelColor((ray_pixel-n)+i*ray_pixel, strip.Color(r,g,b));    
          for( int i=3; i<ray_number; i++ )strip.setPixelColor(n-1+i*ray_pixel, strip.Color(r,g,b)); 
          break;   
       case 8:
          for( int i=0; i<1; i++ )strip.setPixelColor(n-1+i*ray_pixel, strip.Color(r,g,b));    
          for( int i=1; i<4; i++ )strip.setPixelColor((ray_pixel-n)+i*ray_pixel, strip.Color(r,g,b)); 
          for( int i=4; i<ray_number; i++ )strip.setPixelColor(n-1+i*ray_pixel, strip.Color(r,g,b));    
          break;   
       case 9:
          for( int i=0; i<2; i++ )strip.setPixelColor(n-1+i*ray_pixel, strip.Color(r,g,b));    
          for( int i=2; i<5; i++ )strip.setPixelColor((ray_pixel-n)+i*ray_pixel, strip.Color(r,g,b)); 
          for( int i=5; i<ray_number; i++ )strip.setPixelColor(n-1+i*ray_pixel, strip.Color(r,g,b));    
          break;   
       default:
          for( int i=0; i<ray_number; i++ )strip.setPixelColor(n-1+i*ray_pixel, strip.Color(r,g,b));    
      }
 
}


