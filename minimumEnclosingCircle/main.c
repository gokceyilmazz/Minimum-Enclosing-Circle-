#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



typedef struct{
  float xeks, yeks;
  float r;
} koordinat;



float mesafe_bul(float x1, float y1, float x2, float y2){
  float mesafe;
  mesafe = sqrt(pow(x1-x2, 2) + pow(y1 -y2, 2));
  return mesafe;
}


koordinat ucnoktasi_verilencember(float x1, float y1, float x2, float y2, float x3, float y3) {

    //GENEL ÇEMBER DENKLEMÝ=(x–a)^2 + (y–b)^2 = r2 , Merkez(a,b)
    //denklem1= x1*x1 + y1*y1 + 2*d*x1 + 2*e*y2 + f=0
    //denklem2= x2*x2 + y2*y2 + 2*d*x2 + 2*e*y2 + f=0
    //denklem3= x3*x3 + y3*y3 + 2*d*x3 + 2*e*y3 + f=0
    //denklem4= 2*d*x1= - x1*x1 - y1*y1 - 2*e*y2 + f
    //denklem5= f= - x1*x1 - y1*y1 -2*d*x1 -2*e*y1
    //denklem6= 2*e*y3= -x3*x3 - y3*y3 - 2*d*x3 -f
    //denklem1-denklem2=denklem7= x1*x1 + y1*y1 + 2*d*x1 + 2*e*y2 - x2*x2 - y2*y2 - 2*d*x2 - 2*e*y2
    //-->parantezleme yap. denklem7= 2*d*(x1-x2)=(x2*x2-x1*x1)+(y2*y2-y1*y1)+2*e*(y2-y1)
    //denklem8= 2*e*y3= - x3*x3 - y3*y3 - 2*d*x3 + x1*x1 +y1*y1 + 2*d*x1 + 2*e*y1

    //2*e = ((x1*x1 – x3*x3)*(x1 – x2) +(y1*y1 – y3*y3)*(x1 – x2) + (x2*x2 – x1*x1)*(x1 – x3)
    //       + (y2*y2 – y1*y1)*(x1 – x3) ) / (y3 – y1)*(x1 – x2) – (y2 – y1)*(x1 – x3)

    //2*d = ((x1*x1 – x3*x3)*(y1 – x2) +(y1*y1 – y3*y3)*(y1 – y2) + (x2*x2 – x1*x1)*(y1 – y3)
    //        + (y2*y2 – y1*y1)*(y1 – y3) ) / (y3 - y1)*(y1 – y2) – (x2 – x1)*(y1 – y3)



    float x12 = x1 - x2;
    float x13 = x1 - x3;

    float y12 = y1 - y2;
    float y13 = y1 - y3;

    float y31 = y3 - y1;
    float y21 = y2 - y1;

    float x31 = x3 - x1;
    float x21 = x2 - x1;

    float kx13 = pow(x1, 2) - pow(x3, 2);


    float ky13 = pow(y1, 2) - pow(y3, 2);

    float kx21 = pow(x2, 2) - pow(x1, 2);

    float ky21 = pow(y2, 2) - pow(y1, 2);

    float e = ((kx13)*(x12)+(ky13)*(x12)+(kx21) * (x13)+ (ky21) * (x13))/(2 * ((y31) * (x12) - (y21) * (x13)));

    double d = ((kx13) * (y12)+ (ky13) * (y12)+ (kx21) * (y13)+ (ky21) * (y13))/ (2 * ((x31) * (y12) - (x21) * (y13)));


    float f = -pow(x1, 2) - pow(y1, 2) - 2 * d * x1 - 2 * e * y1;


    float a = -d;
    float b = -e;
    float r = sqrt(pow(a,2)+pow(b,2)-f);



    koordinat cember;
    cember.xeks = a;
    cember.yeks = b;
    cember.r = r;
    return cember;


}


koordinat ikinokta_disarda(float noktalar[][2], int n, int ilknokta, int ikincinokta){
  koordinat ce;
  float icindemi;

  ce.xeks = (noktalar[ilknokta][0] + noktalar[ikincinokta][0]/2);
  ce.yeks = (noktalar[ilknokta][1] + noktalar[ikincinokta][1]/2);
  ce.r = (mesafe_bul(noktalar[ilknokta][0], noktalar[ilknokta][1],
                     noktalar[ikincinokta][0], noktalar[ikincinokta][1])/2);

  for(int i=0; i<n; i++){
    icindemi = pow(noktalar[i][0] - ce.xeks, 2) + pow(noktalar[i][1] - ce.yeks, 2) - pow(ce.r, 2);

    if(icindemi > 0) {
      ce = ucnoktasi_verilencember(noktalar[ilknokta][0], noktalar[ilknokta][1],
        noktalar[ikincinokta][0], noktalar[ikincinokta][1], noktalar[i][0], noktalar[i][1]);
    }
  }

  return ce;
}


koordinat teknokta_disarda(float noktalar[][2], int n1){
  koordinat ce;
  int j;
  float icindemi;


  ce.xeks = (noktalar[n1][0]+noktalar[0][0])/2;
  ce.yeks = (noktalar[n1][1]+noktalar[0][1])/2;
  ce.r = (mesafe_bul(noktalar[n1][0], noktalar[n1][1], noktalar[0][0], noktalar[0][1])/2);



  for(j=1; j<n1; j++){
    icindemi = pow(noktalar[j][0] - ce.xeks, 2) + pow(noktalar[j][1] - ce.yeks, 2) - pow(ce.r, 2);
    if(icindemi > 0){

      ce = ikinokta_disarda(noktalar, j, j, n1);
    }
  }

  return ce;

}


koordinat cember_bul(float noktalar[][2], int noktasayisi){
  koordinat ce;

  float icindemi;

  ce.xeks = (noktalar[1][0]+noktalar[0][0])/2;
  ce.yeks = (noktalar[1][1]+noktalar[0][1])/2;
  ce.r = (mesafe_bul(noktalar[0][0], noktalar[0][1], noktalar[1][0], noktalar[1][1])/2);



  for(int i=2; i<noktasayisi; i++){
    icindemi = pow(noktalar[i][0] - ce.xeks, 2) + pow(noktalar[i][1] - ce.yeks, 2) - pow(ce.r, 2);
    if(icindemi > 0){
      ce = teknokta_disarda(noktalar, i);
    }
  }

  return ce;
}



int main(void){

int noktasayisi;
printf("Kac nokta girdiniz:");
scanf("%d",&noktasayisi);


FILE *dosya;
dosya =fopen("girilennoktalar.txt","r");
float noktalar[1000][2];
int i=0;
int j=0;
koordinat ce;
float sayi;
char eks[50];
char x,*nokta;
if(dosya!=NULL){

    while(!feof(dosya)){
        x=fgetc(dosya);
        eks[i]=x;
        i++;
    }
}

nokta=strtok(eks,",");
sayi=atof(nokta);
noktalar[0][0]=sayi;

for(i=0 ; i<noktasayisi ; i++){
nokta=strtok(NULL,"\n");
sayi=atof(nokta);
noktalar[i][1]=sayi;


if(i!=noktasayisi){

nokta=strtok(NULL,",");
sayi=atof(nokta);
noktalar[i+1][0]=sayi;
}
}


    ALLEGRO_DISPLAY *display;
     if(!al_init()){
        al_show_native_message_box(display,NULL,NULL,"HATA",NULL,NULL);
    }

    display = al_create_display(1000,1000);
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    al_set_window_position(display,200,50);
    al_set_window_title(display,"Minimum Enclosing Circle - 1.Proje");


    if(!display){
        al_show_native_message_box(display,"Hata",NULL,"Ekran bulunamadi",NULL,ALLEGRO_WINDOWED);
    }

al_init_primitives_addon();

al_init();



for(int j=0;j<=1000;j+=20){
float tempJ =(float)j;
al_draw_line(0,tempJ,1000,tempJ,al_map_rgb(50,50,50),1);
al_draw_line(tempJ,1000,tempJ,0,al_map_rgb(50,50,50),1);
}
al_draw_line(0,500,1000,500,al_map_rgb(255,255,255),4);
al_draw_line(500,0,500,1000,al_map_rgb(255,255,255),4);



ALLEGRO_COLOR a = al_map_rgb(0,255,0);
   al_init_font_addon();
   al_init_ttf_addon();

   ALLEGRO_FONT *font =al_load_font("arial.ttf",12,NULL);
   al_draw_text(font,a,490,485,ALLEGRO_ALIGN_CENTRE,"0");


char d[2];
int s=1;
int k=0;
while(1){
   al_draw_text(font,a,515+k,505,0, itoa( s, d, 10 ) );
   k=k+20;
   s++;
   if(k==440)
    break;
}

char q[2];
int w=1;
int e=475;
while(1){
   al_draw_text(font,a,505,e,ALLEGRO_ALIGN_LEFT, itoa( w, q, 10 ) );
   e=e-20;
   w++;
   if(e==15)
    break;
}

char c[2];
int v= -1;
int b=473;
while(1){
   al_draw_text(font,a,b,505,0, itoa( v, c, 10 ) );
   b=b-20;
   v--;
   if(b==13)
    break;
}

char n[2];
int m= -1;
int f=515;
while(1){
   al_draw_text(font,a,505,f,ALLEGRO_ALIGN_LEFT, itoa( m, n, 10 ) );
   f=f+20;
   m--;
   if(f==995)
    break;
}



for(i=0; i<noktasayisi ; i++){


al_draw_filled_circle(500+20*noktalar[i][0],500-20*noktalar[i][1],2,al_map_rgb(255,0,255));


}

 ce = cember_bul(noktalar, noktasayisi);
 printf(" Merkez noktasi= (%f, %f), Yaricap= %f\n", ce.xeks, ce.yeks, ce.r);

al_draw_circle(500+20*ce.xeks,500-20*ce.yeks,20*ce.r,al_map_rgb(250,50,150),1);

al_draw_filled_circle(500+20*ce.xeks,500-20*ce.yeks,2,al_map_rgb(100,255,0));

al_draw_line(500+20*ce.xeks,500-20*ce.yeks,500+20*(ce.r+ce.xeks),500-20*ce.yeks,al_map_rgb(255,255,255),2);

//Spline:
    float t = 0.0;
    i=0;
     int p0, p1, p2, p3;
   while (i != noktasayisi-1) {

       p0 = i % noktasayisi;
       p1 = (i+1) % noktasayisi;
       p2 = (i + 2) % noktasayisi;
       p3 = (i + 3) % noktasayisi;

       if (t > 1) {
           i++;
           t = 0;
       }

       float q1 = -pow(t,3) + 2.0f * pow(t,2) - t;
       float q2 = 3.0f * pow(t,3) - 5.0f * pow(t,2) + 2.0f;
       float q3 = -3.0f * pow(t,3) + 4.0f * pow(t,2) + t;
       float q4 = pow(t,3) - pow(t,2);

       float tx = 0.5f * (noktalar[p0][0] * q1 + noktalar[p1][0] * q2 + noktalar[p2][0] * q3  + noktalar[p3][0] * q4);
       float ty = 0.5f * (noktalar[p0][1] * q1 + noktalar[p1][1] * q2 + noktalar[p2][1] * q3 + noktalar[p3][1] * q4);

       al_draw_pixel(tx*20+500, -ty*20+500, al_map_rgb(255, 255, 0));

       t += 0.001;

   }

al_flip_display();
system("pause");

    fclose(dosya);
    return 0;
}


